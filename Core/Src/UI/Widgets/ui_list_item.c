/**
 ******************************************************************************
 * @file     ui_list_item.c
 * @brief    List item widget with left label and optional right-side object.
 *
 * @details  A list item consists of:
 *           - a left-aligned label (text)
 *           - an optional right-side interactive widget (slider, toggle, etc.)
 *           - a vertical separator between the two areas
 *
 *           It is used inside list-like UI containers to present settings
 *           or options in a structured “Label - Control” format.
 *
 *           The widget handles focus transitions between itself and the
 *           right-side object (if present).
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


#include "ui_list_item.h"
#include <string.h>
#include <stdlib.h>
#include "ui_theme.h"
#include "ui_slider.h"
#include "ui_slider_time.h"
#include "ui_toggle.h"
#include "lcd.h"



// ================= HELPER FUNCTIONS ================

static bool ui_list_item_focus_in(ui_list_item_t* list_item) {

	// If there is no object -> do nothing:
    if (list_item->object == NULL) { return false; }

    ui_widget_t* child_widget  = list_item->object;

    if (child_widget->focusable) {
		ui_widget_blur(&list_item->base);
		ui_widget_focus(child_widget);
		return true;
    }

    return false;
}

static bool ui_list_item_focus_out(ui_list_item_t* list_item) {

    // If there is no object -> do nothing:
	if (list_item->object == NULL) { return false; }

	ui_widget_t* child_widget  = list_item->object;

	if (child_widget->focusable) {
		ui_widget_blur(child_widget);
		ui_widget_focus(&list_item->base);
		return true;
	}

    return false;
}

static void ui_list_item_create_object(ui_widget_t* widget) {
	ui_list_item_t* list_item = LIST_ITEM(widget);

    switch (list_item->object_type) {

        case UI_LIST_ITEM_SLIDER: {
            ui_slider_t* slider = malloc(sizeof(ui_slider_t));
            ui_slider_init(slider, 0, 0, 0, 0);
            list_item->object = &slider->base;
            break;
        }

        case UI_LIST_ITEM_SLIDER_TIME: {
		    ui_slider_time_t* slider_time = malloc(sizeof(ui_slider_time_t));
		    ui_slider_time_init(slider_time, 0, 0, 0, 0);
		    list_item->object = &slider_time->base;
		   	break;
        }

        case UI_LIST_ITEM_TOGGLE: {
            ui_toggle_t* toggle = malloc(sizeof(ui_toggle_t));
            ui_toggle_init(toggle, 0, 0, 0, 0);
            list_item->object = &toggle->base;
            break;
        }

        case UI_LIST_ITEM_NONE:
        default:
        	list_item->object = NULL;
            break;
    }
}

static void ui_list_item_draw_separator(ui_widget_t* widget) {
	ui_list_item_t* list_item = LIST_ITEM(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t height = widget->height;

	uint16_t inner_x = x + list_item->border_thickness;
	uint16_t inner_y = y + list_item->border_thickness;
	uint16_t inner_height = height - (2 * list_item->border_thickness);

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t separator_color = focused ? list_item->focus_border_color : list_item->border_color;

	// Compute separator position and size:
	uint16_t separator_x = inner_x + list_item->separator_x_offset;
	uint16_t separator_y = inner_y;
	uint16_t separator_width = list_item->border_thickness;
	uint16_t separator_height = inner_height;

	// Draw separator:
	if (list_item->border_thickness > 0) {
		lcd_fill_rect(separator_x, separator_y, separator_width, separator_height, separator_color);
	}
}

static void ui_list_item_draw_border(ui_widget_t* widget) {
	ui_list_item_t* list_item = LIST_ITEM(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t border_color = focused ? list_item->focus_border_color : list_item->border_color;

	// Draw border:
	if (list_item->border_thickness > 0) {
		lcd_fill_rect(x, y, width, height, border_color);
	}
}

static void ui_list_item_draw_background(ui_widget_t* widget) {
	ui_list_item_t* list_item = LIST_ITEM(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? list_item->focus_background_color : list_item->background_color;

	// Draw border:
	ui_list_item_draw_border(widget);

	// Draw background:
	lcd_fill_rect(x + list_item->border_thickness, y + list_item->border_thickness, width - (2 * list_item->border_thickness), height - (2 * list_item->border_thickness), background_color);

	// Draw separator:
	ui_list_item_draw_separator(widget);
}

static void ui_list_item_draw_label(ui_widget_t* widget) {
	ui_list_item_t* list_item = LIST_ITEM(widget);
	ui_label_t* label = &list_item->label;

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t height = widget->height;

	uint16_t inner_x = x + list_item->border_thickness;
	uint16_t inner_y = y + list_item->border_thickness;
	uint16_t inner_height = height - (2 * list_item->border_thickness);

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? list_item->focus_background_color : list_item->background_color;

	// Compute label position and size:
	uint16_t label_x = inner_x + list_item->label_padding;
	uint16_t label_y = inner_y + list_item->label_padding;
	uint16_t label_width = list_item->separator_x_offset - (2 * list_item->label_padding);
	uint16_t label_height = inner_height - (2 * list_item->label_padding);

	// Apply label geometry:
	label->base.render_x = label_x;
	label->base.render_y = label_y;

	label_width(label) = label_width;
	label_height(label) = label_height;

	// Label inherits widget background:
	label_background_color(label) = background_color;
	label_border_color(label) = background_color;

	// Center label text:
	label_align_horizontal(label) = UI_ALIGN_CENTER_X;
	label_align_vertical(label) = UI_ALIGN_CENTER_Y;

	// Draw label:
	ui_label_draw(&label->base);
}

static void ui_list_item_draw_right_area_object(ui_widget_t* widget) {
	ui_list_item_t* list_item = LIST_ITEM(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	uint16_t inner_x = x + list_item->border_thickness;
	uint16_t inner_y = y + list_item->border_thickness;
	uint16_t inner_width = width - (2 * list_item->border_thickness);
	uint16_t inner_height = height - (2 * list_item->border_thickness);

	// Compute right area position and size:
	uint16_t right_area_x = inner_x + (list_item->separator_x_offset + list_item->border_thickness) + list_item->right_area_padding;
	uint16_t right_area_y = inner_y + list_item->right_area_padding;
	uint16_t right_area_width = inner_width - (list_item->separator_x_offset + list_item->border_thickness) - (2 * list_item->right_area_padding);
	uint16_t right_area_height = inner_height - (2 * list_item->right_area_padding);

	// Draw right area object (slider, toggle, etc.) if it exists:
	if (list_item->object != NULL) {
		ui_widget_t* object = list_item->object;
		object->render_x = right_area_x;
		object->render_y = right_area_y;

		widget_width(object) = right_area_width;
		widget_height(object) = right_area_height;

		object->draw(object);
	}
}



// =================== CONSTRUCTOR ===================

void ui_list_item_init(ui_list_item_t* list_item, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

    ui_widget_init(&list_item->base, x, y, width, height,
    		ui_list_item_draw,
			NULL,
			ui_list_item_on_focus,
			ui_list_item_on_blur,
			ui_list_item_on_event,
			NULL);


    // ============= FIELDS ==============

    // Border:
    list_item->border_thickness = UI_THEME_LIST_ITEM_BORDER_THICKNESS;
    list_item->border_color = UI_THEME_LIST_ITEM_BORDER_COLOR;

    // Background:
    list_item->background_color = UI_THEME_LIST_ITEM_BACKGROUND_COLOR;

    // Separator:
    list_item->separator_x_offset = 100;

    // Label:
    ui_label_init(&list_item->label, 0, 0, 0, 0);
    list_item->label_padding = UI_THEME_LIST_ITEM_LABEL_PADDING;

    // Right area (for slider, toggle, etc.):
    list_item->object_type = UI_LIST_ITEM_NONE;
    list_item->object = NULL;
    list_item->right_area_padding = UI_THEME_LIST_ITEM_RIGHT_AREA_PADDING;

    // Focus:
    list_item->focus_border_color = UI_THEME_LIST_ITEM_FOCUS_BORDER_COLOR;
    list_item->focus_background_color = UI_THEME_LIST_ITEM_FOCUS_BACKGROUND_COLOR;
}



// ================ VIRTUAL FUNCTIONS ================

void ui_list_item_draw(ui_widget_t* widget) {
	ui_list_item_draw_background(widget);
	ui_list_item_draw_label(widget);
	ui_list_item_draw_right_area_object(widget);
}

void ui_list_item_on_focus(ui_widget_t* widget) {
	ui_widget_invalidate(widget);
}

void ui_list_item_on_blur(ui_widget_t* widget) {
	ui_list_item_t* list_item = LIST_ITEM(widget);

	// If the child object was focused -> blur it:
	if (list_item->object && list_item->object->focused) {
		list_item->object->focused = false;

		if (list_item->object->on_blur) {
			list_item->object->on_blur(list_item->object);
		}
	}

	ui_widget_invalidate(widget);
}

bool ui_list_item_on_event(ui_widget_t* widget, ui_event_t event) {
	ui_list_item_t* list_item = LIST_ITEM(widget);

	// If there is no object -> do nothing:
    if (list_item->object == NULL) { return false; }

    ui_widget_t* child_widget  = list_item->object;

    if (child_widget->focused) {
    	bool event_served = child_widget->on_event(child_widget, event);

    	if (event_served) { return true; }

		// If the child did not handle the event -> return focus to list_item:
    	ui_list_item_focus_out(list_item);
		return true;
    }

	// If the child widget did not handle the event:
	switch (event) {
		case UI_EVENT_SELECT:
			if (widget->focused) {
				ui_list_item_focus_in(list_item);
				return true;
			}
			break;

		default:
			return false;
	}

	return true;
}



// ===================== SETTERS =====================

void ui_list_item_object_type(ui_widget_t* widget, ui_list_item_object_type_t type) {
    ui_list_item_t* list_item = LIST_ITEM(widget);

    // Object type can be set only once:
    if (list_item->object_type != UI_LIST_ITEM_NONE) { return; }

    list_item->object_type = type;
    ui_list_item_create_object(widget);
}