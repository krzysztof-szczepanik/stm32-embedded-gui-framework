/**
 ******************************************************************************
 * @file     ui_container.c
 * @brief    Base container widget for grouping and positioning child widgets.
 *
 * @details  A container is a widget that holds and manages a list of child
 *           widgets.
 * 
 *           It provides:
 *           - background and border rendering
 *           - padding handling
 *           - focus navigation between child widgets
 *           - recursive layout propagation
 *
 *           Containers do not define their own layout strategy. Instead,
 *           specialized layout widgets such as HBox, VBox, Header, and Footer
 *           extend this type and implement their own layout logic in
 *           update_layout().
 *
 *           All container-based widgets embed this structure as their first
 *           member.
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

#include "ui_container.h"
#include <stddef.h>
#include "ui_theme.h"
#include "ui_direction.h"
#include "lcd.h"



// =================== CONSTRUCTOR ===================

void ui_container_init(ui_container_t* container, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

	ui_widget_init(&container->base, x, y, width, height,
			ui_container_draw,
			ui_container_update_layout,
			ui_container_on_focus,
			ui_container_on_blur,
			ui_container_on_event,
			ui_container_get_widgets);


    // ============= FIELDS ==============

	// Widgets:
    container->widgets_count = 0;

	// Focused widget index:
    container->focused_widget_index = 0;
    container->focus_entered = false;

    // Border:
    container->border_thickness = UI_THEME_CONTAINER_BORDER_THICKNESS;
    container->border_color = UI_THEME_CONTAINER_BORDER_COLOR;

    // Background:
    container->background_color = UI_THEME_CONTAINER_BACKGROUND_COLOR;

    // Padding:
    container->padding_left = 0;
    container->padding_right = 0;
    container->padding_top = 0;
    container->padding_bottom = 0;
}



// ==================== FUNCTIONS =====================

void ui_container_add_widget(ui_container_t* container, ui_widget_t* widget) {
    if (container->widgets_count >= UI_CONTAINER_MAX_WIDGETS) { return; }

    container->widgets[container->widgets_count++] = widget;
    widget->parent = &container->base; // assign parent widget (the container becomes the parent)
    ui_container_update_layout(&container->base);
}

void ui_container_add_widgets(ui_container_t* container, ui_widget_t** widgets, uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        if (container->widgets_count >= UI_CONTAINER_MAX_WIDGETS) { break; }

        ui_container_add_widget(container, widgets[i]);
    }
}

void ui_container_draw_background(ui_widget_t* widget) {
	ui_container_t* container = CONTAINER(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Border:
	if (container->border_thickness > 0) {
		lcd_fill_rect(x, y, width, height, container->border_color);
	}

	// Background:
	lcd_fill_rect(x + container->border_thickness, y + container->border_thickness, width - (2 * container->border_thickness), height - (2 * container->border_thickness), container->background_color);
}



// ================= FOCUS FUNCTIONS ==================

bool ui_container_focus_next(ui_container_t* container) {
    // Get currently focused widget:
    uint8_t start = container->focused_widget_index;
    ui_widget_t* current_child_widget = container->widgets[start];

    // If this is the last widget -> exit container:
    if (start == container->widgets_count - 1) {
    	ui_widget_blur(current_child_widget);
    	container->focus_entered = false;
    	return false;
    }

    // Search for the next focusable widget:
    for (uint8_t i = start + 1; i < container->widgets_count; i++) {
    	ui_widget_t* child_widget = container->widgets[i];

    	if (child_widget->focusable) {
    		ui_widget_blur(current_child_widget);
    		container->focused_widget_index = i;
    		ui_widget_focus(child_widget);
    		return true;
    	}
    }

    return false;
}

bool ui_container_focus_previous(ui_container_t* container) {
	// Get currently focused widget:
	int start = container->focused_widget_index;
	ui_widget_t* current_child_widget = container->widgets[start];

	// If this is the first widget -> exit container:
	if (start == 0) {
		ui_widget_blur(current_child_widget);
		container->focus_entered = false;
		return false;
	}

	// Search for the previous focusable widget:
	for (int i = start - 1; i >= 0; i--) {
		ui_widget_t* child_widget = container->widgets[i];

		if (child_widget->focusable) {
			ui_widget_blur(current_child_widget);
			container->focused_widget_index = i;
			ui_widget_focus(child_widget);
			return true;
		}
	}

	return false;
}



// ================ VIRTUAL FUNCTIONS ================

void ui_container_draw(ui_widget_t* widget)  {
	ui_container_t* container = CONTAINER(widget);

    // Background and border:
    ui_container_draw_background(widget);

    // Draw child widgets:
    for (uint8_t i = 0; i < container->widgets_count; i++) {
        ui_widget_t* child_widget = container->widgets[i];
		child_widget->draw(child_widget);
		child_widget->invalidated = false;
    }
}

void ui_container_update_layout(ui_widget_t* widget) {
    ui_container_t* container = CONTAINER(widget);

    // If widget has a parent -> global position = parent position + local offset
    // If no parent -> widget is root and uses its own coordinates
    if (widget->parent) {
		widget->render_x = widget->parent->render_x + widget->x;
		widget->render_y = widget->parent->render_y + widget->y;
	} else {
		widget->render_x = widget->x;
		widget->render_y = widget->y;
	}

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;

	// Inner area:
	uint16_t inner_x = x + container->border_thickness + container->padding_left;
	uint16_t inner_y = y + container->border_thickness + container->padding_top;

    // Update child widgets:
    for (uint8_t i = 0; i < container->widgets_count; i++) {
        ui_widget_t* child_widget = container->widgets[i];

        // Local position -> global position:
        child_widget->render_x = inner_x + child_widget->x;
        child_widget->render_y = inner_y + child_widget->y;

        // Recursively update layout if child has its own layout function (concerns only containers):
		if (child_widget->update_layout) {
			child_widget->update_layout(child_widget);
		}
    }
}

void ui_container_on_focus(ui_widget_t* widget) {
    ui_container_t* container = CONTAINER(widget);

    if (container->widgets_count == 0) { return; }

    // We get the last movement direction from the global ui_direction module (this is the direction from which the user "enters" the container):
    ui_direction_t direction = ui_direction_get();
    uint8_t* focused_child_widget_index = &container->focused_widget_index;

    switch (direction) {
        case UI_DIRECTION_DOWN: *focused_child_widget_index = 0; break;
        case UI_DIRECTION_UP:   *focused_child_widget_index = container->widgets_count - 1; break;
        default:                *focused_child_widget_index = 0; break;
    }

    ui_widget_focus(container->widgets[*focused_child_widget_index]);
    container->focus_entered = true;
}

void ui_container_on_blur(ui_widget_t* widget) {
    ui_container_t* container = CONTAINER(widget);

    if (container->widgets_count == 0) return;

    ui_widget_t* focused_child_widget = container->widgets[container->focused_widget_index];
    ui_widget_blur(focused_child_widget);
    container->focus_entered = false;
}

bool ui_container_on_event(ui_widget_t* widget, ui_event_t event) {
    ui_container_t* container = CONTAINER(widget);

    if (container->widgets_count == 0) { return false; }

    ui_widget_t* focused_child_widget = container->widgets[container->focused_widget_index];

    bool event_served = focused_child_widget->on_event(focused_child_widget, event);

    if (event_served) { return true; }

    // If the child did not handle the event, the container tries to move focus:
	switch(event) {
		case UI_EVENT_DOWN: return ui_container_focus_next(container);
		case UI_EVENT_UP: return ui_container_focus_previous(container);
		default: return false;
	}
}

uint8_t ui_container_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets) {
    ui_container_t* container = CONTAINER(widget);

    for (uint8_t i = 0; i < container->widgets_count; i++) {
    	out_widgets[i] = container->widgets[i];
    }

    return container->widgets_count;
}