/**
 ******************************************************************************
 * @file     ui_screen.c
 * @brief    Implementation of the base screen container.
 *
 * @details  This module defines the base screen type used as the root widget
 *           of every displayed view.
 * 
 *           A screen manages its child widgets, handles focus navigation,
 *           routes UI events to widgets, and propagates drawing and layout
 *           updates through the entire widget tree.
 * 
 *           All application screens inherit from this structure.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 Krzysztof Szczepanik.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "ui_screen.h"
#include <stddef.h>
#include "ui_theme.h"
#include "ui_direction.h"
#include "lcd.h"



// ================= HELPER FUNCTIONS ================

static void ui_screen_blur(ui_widget_t* widget) {
	// If the widget has children -> blur them recursively:
	if (widget->get_widgets) {
		ui_widget_t* child_widgets[16];
		uint8_t child_widgets_count = widget->get_widgets(widget, child_widgets);

		for (uint8_t i = 0; i < child_widgets_count; i++) {
			ui_screen_blur(child_widgets[i]);
		}
	} else {
		if (widget->focusable) {
			ui_widget_blur(widget);
		}
	}
}



// =================== CONSTRUCTOR ===================

void ui_screen_init(ui_screen_t* screen) {

	// ========== BASE WIDGET ===========

	ui_widget_init(&screen->base, 0, 0, LCD_WIDTH, LCD_HEIGHT,
			ui_screen_draw,
			ui_screen_update_layout,
			NULL,
			NULL,
			NULL,
			ui_screen_get_widgets);


	// ============= FIELDS ==============
	
	// Widgets:
    screen->widgets_count = 0;

	// Focused widget index:
    screen->focused_widget_index = 0;

	// Virtual functions:
    screen->update_data = NULL;
}



// ==================== FUNCTIONS ====================

void ui_screen_add_widget(ui_screen_t* screen, ui_widget_t* widget) {
	if (screen->widgets_count >= UI_SCREEN_MAX_WIDGETS) { return; }

	screen->widgets[screen->widgets_count++] = widget;
	widget->parent = &screen->base;
	screen->base.invalidated = true;
	ui_screen_update_layout(&screen->base);
}

void ui_screen_add_widgets(ui_screen_t* screen, ui_widget_t** widgets, uint8_t count) {
	for (uint8_t i = 0; i < count; i++) {
		if (screen->widgets_count >= UI_SCREEN_MAX_WIDGETS) { break; }

		ui_screen_add_widget(screen, widgets[i]);
	}
}



// ================= FOCUS FUNCTIONS ==================

void ui_screen_focus_first(ui_screen_t* screen) {

	// Remove focus from all widgets:
	for (uint8_t i = 0; i < screen->widgets_count; i++) {
		ui_widget_t* child_widget = screen->widgets[i];

		ui_screen_blur(child_widget);
	}

	// Set focus to the first focusable widget:
    for (uint8_t i = 0; i < screen->widgets_count; i++) {
    	ui_widget_t* child_widget = screen->widgets[i];

    	if (child_widget->focusable) {
    		screen->focused_widget_index = i;
    		ui_widget_focus(child_widget);
    		return;
    	}
    }
}

void ui_screen_focus_next(ui_screen_t* screen) {
    // Get currently focused widget:
    uint8_t start = screen->focused_widget_index;
    ui_widget_t* current_child_widget = screen->widgets[start];

    // Search for the next focusable widget:
    for (uint8_t i = start + 1; i < screen->widgets_count; i++) {
    	ui_widget_t* child_widget = screen->widgets[i];

    	if (child_widget->focusable) {
    		ui_widget_blur(current_child_widget);
    		screen->focused_widget_index = i;
    		ui_widget_focus(child_widget);
    		return;
    	}
    }

	// If not found - wrap around to the beginning:
    for (uint8_t i = 0; i < start; i++) {
    	ui_widget_t* child_widget = screen->widgets[i];

    	if (child_widget->focusable) {
    		ui_widget_blur(current_child_widget);
			screen->focused_widget_index = i;
			ui_widget_focus(child_widget);
			return;
        }
    }
}

void ui_screen_focus_previous(ui_screen_t* screen) {
	// Get currently focused widget:
	int start = screen->focused_widget_index;
	ui_widget_t* current_child_widget = screen->widgets[start];

    // Search for the previous focusable widget:
	for (int i = start - 1; i >= 0; i--) {
		ui_widget_t* child_widget = screen->widgets[i];

		if (child_widget->focusable) {
			ui_widget_blur(current_child_widget);
			screen->focused_widget_index = i;
			ui_widget_focus(child_widget);
			return;
		}
	}

	// If not found - wrap around to the end:
    for (int i = screen->widgets_count - 1; i > start; i--) {
    	ui_widget_t* child_widget = screen->widgets[i];

    	if (child_widget->focusable) {
			ui_widget_blur(current_child_widget);
			screen->focused_widget_index = i;
			ui_widget_focus(child_widget);
			return;
		}
   }
}



// ================= EVENT FUNCTIONS ==================

void ui_screen_handle_event(ui_screen_t* screen, ui_event_t event) {
    ui_widget_t* focused_child_widget = screen->widgets[screen->focused_widget_index];

    bool event_served = focused_child_widget->on_event(focused_child_widget, event);

    if (!event_served) {
        switch(event) {
            case UI_EVENT_UP:
            	ui_direction_set(UI_DIRECTION_UP);
                ui_screen_focus_previous(screen);

                 // If the screen has only one widget -> refocus:
                if (screen->widgets_count == 1) {
                	ui_widget_t* child_widget = screen->widgets[0];
                	ui_widget_blur(child_widget);
                	ui_widget_focus(child_widget);
                }

                break;

            case UI_EVENT_DOWN:
            	ui_direction_set(UI_DIRECTION_DOWN);
                ui_screen_focus_next(screen);

                // If the screen has only one widget -> refocus:
                if (screen->widgets_count == 1) {
                	ui_widget_t* child_widget = screen->widgets[0];
                	ui_widget_blur(child_widget);
                	ui_widget_focus(child_widget);
                }

                break;

            default:
                break;
        }
    }
}



// ================ VIRTUAL FUNCTIONS ================

void ui_screen_draw(ui_widget_t* widget) {
	ui_screen_t* screen = SCREEN(widget);

    // If nothing requires redrawing -> exit:
    if (!widget->invalidated) {
        return;
    }

    // Clear the screen:
    lcd_clear(UI_THEME_BACKGROUND_COLOR);

    // Draw child widgets:
    for (uint8_t i = 0; i < screen->widgets_count; i++) {
        ui_widget_t* child_widget = screen->widgets[i];
		child_widget->draw(child_widget);
		child_widget->invalidated = false;
    }

    // Reset invalidation flag:
    widget->invalidated = false;
}

void ui_screen_update_layout(ui_widget_t* widget) {
    ui_screen_t* screen = SCREEN(widget);

    widget->render_x = widget->x;
    widget->render_y = widget->y;

    for (uint8_t i = 0; i < screen->widgets_count; i++) {
        ui_widget_t* child_widget = screen->widgets[i];

        if (child_widget->update_layout) {
        	child_widget->update_layout(child_widget);
        }
    }
}


uint8_t ui_screen_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets) {
    ui_screen_t* screen = SCREEN(widget);

    for (uint8_t i = 0; i < screen->widgets_count; i++) {
        out_widgets[i] = screen->widgets[i];
    }

    return screen->widgets_count;
}