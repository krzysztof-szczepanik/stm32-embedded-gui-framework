/**
 ******************************************************************************
 * @file     ui_vbox.c
 * @brief    Vertical box layout widget for arranging child widgets in a
 *           column.
 *
 * @details  Vbox is a layout container that arranges its child widgets
 *           vertically. It extends the base container and adds:
 *           - horizontal and vertical alignment
 *           - widget stretching modes
 *           - configurable spacing between widgets
 *
 *           Unlike hbox, most vbox functions simply forward calls to the
 *           underlying container implementation. Only layout computation
 *           differs, as vbox arranges widgets top‑to‑bottom instead of
 *           left‑to‑right.
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

#include "ui_vbox.h"



// ================= HELPER FUNCTIONS ================

static void vbox_apply_stretch(ui_vbox_t* vbox, uint16_t inner_x, uint16_t inner_y, uint16_t inner_width, uint16_t inner_height) {
	ui_container_t* container = &vbox->base;

    uint16_t available_height = inner_height - vbox->spacing * (container->widgets_count - 1);
    uint16_t per_child_width  = inner_width;
    uint16_t per_child_height = available_height / container->widgets_count;

    uint16_t offset_y = 0;

    for (uint8_t i = 0; i < container->widgets_count; i++) {
        ui_widget_t* child_widget = container->widgets[i];

        // Position (always applied):
        child_widget->render_x = inner_x;
        child_widget->render_y = inner_y + offset_y;

        // Stretch (depends on mode):
        switch (vbox->stretch) {
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

        offset_y += child_widget->height + vbox->spacing;
    }
}

static void vbox_apply_align(ui_vbox_t* vbox, uint16_t inner_x, uint16_t inner_y, uint16_t inner_width, uint16_t inner_height) {
    ui_container_t* container = &vbox->base;

    // Check if alignment is allowed:
    bool allow_align_x = (vbox->stretch == UI_STRETCH_NONE || vbox->stretch == UI_STRETCH_HEIGHT);
    bool allow_align_y = (vbox->stretch == UI_STRETCH_NONE || vbox->stretch == UI_STRETCH_WIDTH);

    uint16_t offset_y = 0;

    // Vertical alignment:
    if (allow_align_y) {

	    // Calculate total height of child widgets:
		uint16_t total_child_widgets_height = 0;
		for (uint8_t i = 0; i < container->widgets_count; i++) {
			ui_widget_t* child_widget = container->widgets[i];
			total_child_widgets_height += child_widget->height;

			if (i < container->widgets_count - 1) {
				total_child_widgets_height += vbox->spacing;
			}
		}

		// Calculate offset_y:
		switch (vbox->align_vertical) {
			case UI_ALIGN_CENTER_Y: offset_y = (inner_height - total_child_widgets_height) / 2; break;
			case UI_ALIGN_BOTTOM:	offset_y = inner_height - total_child_widgets_height; break;
			case UI_ALIGN_TOP: break;
			default: break;
		}
    }

	// Vertical + horizontal layout:
	uint16_t child_widget_y = offset_y;
	for (uint8_t i = 0; i < container->widgets_count; i++) {
		ui_widget_t* child_widget = container->widgets[i];

		// Position y (always applied):
		child_widget->render_y = inner_y + child_widget_y;

		// Horizontal alignment:
		if (allow_align_x) {
		    uint16_t offset_x = 0;

		    // Calculate offset_x:
		    switch (vbox->align_horizontal) {
		        case UI_ALIGN_CENTER_X: offset_x = (inner_width - child_widget->width) / 2; break;
		        case UI_ALIGN_RIGHT:    offset_x = inner_width - child_widget->width; break;
		        case UI_ALIGN_LEFT: break;
		        default: break;
		    }

		    child_widget->render_x = inner_x + offset_x;
		} else {
		    child_widget->render_x = inner_x;
		}

		// Recursively update layout if child has its own layout function (concerns only containers):
		if (child_widget->update_layout) {
			child_widget->update_layout(child_widget);
		}

		child_widget_y += child_widget->height + vbox->spacing;
	}
}



// =================== CONSTRUCTOR ===================

void ui_vbox_init(ui_vbox_t* vbox, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

    ui_container_init(&vbox->base, x, y, width, height);

    vbox->base.base.draw = ui_vbox_draw;
    vbox->base.base.update_layout = ui_vbox_update_layout;
    vbox->base.base.on_focus = ui_vbox_on_focus;
    vbox->base.base.on_blur = ui_vbox_on_blur;
    vbox->base.base.on_event = ui_vbox_on_event;
    vbox->base.base.get_widgets = ui_vbox_get_widgets;


    // ============= FIELDS ==============

    // Widgets stretching:
    vbox->stretch = UI_STRETCH_BOTH;

    // Alignment:
    vbox->align_horizontal = UI_ALIGN_LEFT;
    vbox->align_vertical = UI_ALIGN_TOP;

    // Spacing between widgets:
    vbox->spacing = 0;
}



// ==================== FUNCTIONS ====================

void ui_vbox_add_widget(ui_vbox_t* vbox, ui_widget_t* widget) {
    ui_container_add_widget(&vbox->base, widget);
}

void ui_vbox_add_widgets(ui_vbox_t* vbox, ui_widget_t** widgets, uint8_t count) {
	ui_container_add_widgets(&vbox->base, widgets, count);
}



// ================= FOCUS FUNCTIONS ==================

bool ui_vbox_focus_next(ui_vbox_t* vbox) {
	return ui_container_focus_next(&vbox->base);
}

bool ui_vbox_focus_previous(ui_vbox_t* vbox) {
	return ui_container_focus_previous(&vbox->base);
}



// ================ VIRTUAL FUNCTIONS ================

void ui_vbox_draw(ui_widget_t* widget) {
    ui_vbox_t* vbox = VBOX(widget);
    ui_container_t* container = &vbox->base;

    // Background and border:
    ui_container_draw_background(widget);

    // Draw child widgets:
    for (uint8_t i = 0; i < container->widgets_count; i++) {
		ui_widget_t* child_widget = container->widgets[i];
		child_widget->draw(child_widget);
		child_widget->invalidated = false;
	}
}

void ui_vbox_update_layout(ui_widget_t* widget) {
    ui_vbox_t* vbox = VBOX(widget);
    ui_container_t* container = &vbox->base;

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

	if (vbox->stretch) {
		vbox_apply_stretch(vbox, inner_x, inner_y, inner_width, inner_height);
	}

	vbox_apply_align(vbox, inner_x, inner_y, inner_width, inner_height);
}

void ui_vbox_on_focus(ui_widget_t* widget) {
	ui_container_on_focus(widget);
}

void ui_vbox_on_blur(ui_widget_t* widget) {
	ui_container_on_blur(widget);
}

bool ui_vbox_on_event(ui_widget_t* widget, ui_event_t event) {
	return ui_container_on_event(widget, event);
}

uint8_t ui_vbox_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets) {
	return ui_container_get_widgets(widget, out_widgets);
}