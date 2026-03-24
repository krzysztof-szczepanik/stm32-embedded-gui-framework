/**
 ******************************************************************************
 * @file     ui_hbox.c
 * @brief    Horizontal box layout widget for arranging child widgets in a row.
 *
 * @details  HBox is a layout container that arranges its child widgets
 *           horizontally. It extends the base container and adds:
 *           - horizontal and vertical alignment
 *           - widget stretching modes
 *           - configurable spacing between widgets
 *
 *           Hbox does not manage focus on its own; instead, it relies on
 *           container focus navigation and only overrides directional
 *           behavior to match horizontal layout semantics.
 *
 *           All child widgets are positioned inside the container's inner
 *           area, respecting padding and border thickness inherited from
 *           ui_container_t.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 Krzysztof Szczepanik.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE
 * file in the root directory of this software component. If no LICENSE
 * file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "ui_hbox.h"
#include "ui_direction.h"



// ================= HELPER FUNCTIONS ================

static void hbox_apply_stretch(ui_hbox_t* hbox, uint16_t inner_x, uint16_t inner_y, uint16_t inner_width, uint16_t inner_height) {
	ui_container_t* container = &hbox->base;

    uint16_t available_width  = inner_width - hbox->spacing * (container->widgets_count - 1);
    uint16_t per_child_width  = available_width / container->widgets_count;
    uint16_t per_child_height = inner_height;

    uint16_t offset_x = 0;

    for (uint8_t i = 0; i < container->widgets_count; i++) {
        ui_widget_t* child_widget = container->widgets[i];

        // Position (always applied):
        child_widget->render_x = inner_x + offset_x;
        child_widget->render_y = inner_y;

        // Stretch (depends on mode):
        switch (hbox->stretch) {
        	case UI_STRETCH_NONE:
        		break;

        	case UI_STRETCH_WIDTH:
        		child_widget->width = per_child_width;
        		break;

        	case UI_STRETCH_HEIGHT:
        		child_widget->height = per_child_height;
        		break;

        	case UI_STRETCH_BOTH:
        		child_widget->width = per_child_width;
        		child_widget->height = per_child_height;
        		break;
        }

        // Recursively update layout if child has its own layout function (concerns only containers):
        if (child_widget->update_layout) {
			child_widget->update_layout(child_widget);
		}

        offset_x += child_widget->width + hbox->spacing;
    }
}

static void hbox_apply_align(ui_hbox_t* hbox, uint16_t inner_x, uint16_t inner_y, uint16_t inner_width, uint16_t inner_height) {
    ui_container_t* container = &hbox->base;

    // Check if alignment is allowed:
    bool allow_align_x = (hbox->stretch == UI_STRETCH_NONE || hbox->stretch == UI_STRETCH_HEIGHT);
    bool allow_align_y = (hbox->stretch == UI_STRETCH_NONE || hbox->stretch == UI_STRETCH_WIDTH);

    uint16_t offset_x = 0;

    // Horizontal alignment:
    if (allow_align_x) {

	    // Calculate total width of child widgets:
		uint16_t total_child_widgets_width = 0;
		for (uint8_t i = 0; i < container->widgets_count; i++) {
			ui_widget_t* child_widget = container->widgets[i];
			total_child_widgets_width += child_widget->width;

			if (i < container->widgets_count - 1) {
				total_child_widgets_width += hbox->spacing;
			}
		}

		// Calculate offset_x:
		switch (hbox->align_horizontal) {
			case UI_ALIGN_CENTER_X: offset_x = (inner_width - total_child_widgets_width) / 2; break;
			case UI_ALIGN_RIGHT:	offset_x = inner_width - total_child_widgets_width; break;
			case UI_ALIGN_LEFT: break;
			default: break;
		}
    }

	// Horizontal + vertical layout:
	uint16_t child_widget_x = offset_x;
	for (uint8_t i = 0; i < container->widgets_count; i++) {
		ui_widget_t* child_widget = container->widgets[i];

		// Position x (always applied):
		child_widget->render_x = inner_x + child_widget_x;

		// Vertical alignment:
		if (allow_align_y) {
		    uint16_t offset_y = 0;

		    // Calculate offset_y:
		    switch (hbox->align_vertical) {
		        case UI_ALIGN_CENTER_Y: offset_y = (inner_height - child_widget->height) / 2; break;
		        case UI_ALIGN_BOTTOM:	offset_y = inner_height - child_widget->height; break;
		        case UI_ALIGN_TOP: break;
		        default: break;
		    }

		    child_widget->render_y = inner_y + offset_y;
		} else {
		    child_widget->render_y = inner_y;
		}

		// Recursively update layout if child has its own layout function (concerns only containers):
		if (child_widget->update_layout) {
			child_widget->update_layout(child_widget);
		}

		child_widget_x += child_widget->width + hbox->spacing;
	}
}



// =================== CONSTRUCTOR ===================

void ui_hbox_init(ui_hbox_t* hbox, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

    ui_container_init(&hbox->base, x, y, width, height);

    hbox->base.base.draw = ui_hbox_draw;
    hbox->base.base.update_layout = ui_hbox_update_layout;
    hbox->base.base.on_focus = ui_hbox_on_focus;
    hbox->base.base.on_blur = ui_hbox_on_blur;
    hbox->base.base.on_event = ui_hbox_on_event;
    hbox->base.base.get_widgets = ui_hbox_get_widgets;


    // ============= FIELDS ==============

    // Widgets stretching:
    hbox->stretch = UI_STRETCH_BOTH;

    // Alignment:
    hbox->align_horizontal = UI_ALIGN_LEFT;
    hbox->align_vertical = UI_ALIGN_TOP;

    // Spacing between widgets:
    hbox->spacing = 0;
}



// ==================== FUNCTIONS ====================

void ui_hbox_add_widget(ui_hbox_t* hbox, ui_widget_t* widget) {
    ui_container_add_widget(&hbox->base, widget);
}

void ui_hbox_add_widgets(ui_hbox_t* hbox, ui_widget_t** widgets, uint8_t count) {
	ui_container_add_widgets(&hbox->base, widgets, count);
}



// ================= FOCUS FUNCTIONS ==================

bool ui_hbox_focus_next(ui_hbox_t* hbox) {
	ui_container_t* container = &hbox->base;

    // Get currently focused widget:
    uint8_t start = container->focused_widget_index;
    ui_widget_t* current_child_widget = container->widgets[start];


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

	// If not found - wrap around to the beginning:
	for (uint8_t i = 0; i < start; i++) {
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

bool ui_hbox_focus_previous(ui_hbox_t* hbox) {
	ui_container_t* container = &hbox->base;

	// Get currently focused widget:
	int start = container->focused_widget_index;
	ui_widget_t* current_child_widget = container->widgets[start];

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

	// If not found - wrap around to the end:
	for (int i = container->widgets_count - 1; i > start; i--) {
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

void ui_hbox_draw(ui_widget_t* widget) {
    ui_hbox_t* hbox = HBOX(widget);
    ui_container_t* container = &hbox->base;

    // Background and border:
    ui_container_draw_background(widget);

    // Draw child widgets:
    for (uint8_t i = 0; i < container->widgets_count; i++) {
		ui_widget_t* child_widget = container->widgets[i];
		child_widget->draw(child_widget);
		child_widget->invalidated = false;
	}
}

void ui_hbox_update_layout(ui_widget_t* widget) {
    ui_hbox_t* hbox = HBOX(widget);
    ui_container_t* container = &hbox->base;

    if (container->widgets_count == 0) { return; }

    uint16_t x = widget->render_x;
   	uint16_t y = widget->render_y;
   	uint16_t width = widget->width;
   	uint16_t height = widget->height;

    // Inner area:
	uint16_t inner_x = x + container->border_thickness + container->padding_left;
	uint16_t inner_y = y + container->border_thickness + container->padding_top;
	uint16_t inner_width = width - (2 * container->border_thickness) - container->padding_left - container->padding_right;
	uint16_t inner_height = height - (2 * container->border_thickness) - container->padding_top - container->padding_bottom;

	if (hbox->stretch) {
		hbox_apply_stretch(hbox, inner_x, inner_y, inner_width, inner_height);
	}

	hbox_apply_align(hbox, inner_x, inner_y, inner_width, inner_height);
}

void ui_hbox_on_focus(ui_widget_t* widget) {
	ui_hbox_t* hbox = HBOX(widget);
	ui_container_t* container = &hbox->base;

    if (container->widgets_count == 0) { return; }

     // We get the last movement direction from the global ui_direction module (this is the direction from which the user "enters" the container):
    ui_direction_t direction = ui_direction_get();
    uint8_t* focused_child_widget_index = &container->focused_widget_index;

    switch (direction) {
        default: *focused_child_widget_index = 0; break;
    }

    ui_widget_focus(container->widgets[*focused_child_widget_index]);
    container->focus_entered = true;
}

void ui_hbox_on_blur(ui_widget_t* widget) {
	ui_hbox_t* hbox = HBOX(widget);
	ui_container_t* container = &hbox->base;

    if (container->widgets_count == 0) return;

    ui_widget_t* focused_widget_child = container->widgets[container->focused_widget_index];
    ui_widget_blur(focused_widget_child);
    container->focus_entered = false;
}

bool ui_hbox_on_event(ui_widget_t* widget, ui_event_t event) {
	ui_hbox_t* hbox = HBOX(widget);
	ui_container_t* container = &hbox->base;

    if (container->widgets_count == 0) { return false; }

    ui_widget_t* focused_child_widget = container->widgets[container->focused_widget_index];

    bool event_served = focused_child_widget->on_event(focused_child_widget, event);

    if (event_served) { return true; }

    // If the child did not handle the event, the container tries to move focus:
	switch(event) {
		case UI_EVENT_RIGHT: return ui_hbox_focus_next(hbox);
		case UI_EVENT_LEFT: return ui_hbox_focus_previous(hbox);
		default: return false;
	}
}

uint8_t ui_hbox_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets) {
    return ui_container_get_widgets(widget, out_widgets);
}