/**
 ******************************************************************************
 * @file     ui_button.c
 * @brief    Clickable button widget with label and focus styling.
 *
 * @details  This module defines a simple interactive button widget used in
 *           the UI framework. A button consists of:
 *           - a base widget (ui_widget_t)
 *           - a label displayed inside the button
 *           - border and background styling
 *           - focus‑specific colors
 *           - an optional on_click callback
 *
 *           The button supports focus handling, drawing, and event
 *           processing through its virtual functions.
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

#include "ui_button.h"
#include <string.h>
#include "ui_theme.h"
#include "lcd.h"



// ================= HELPER FUNCTIONS ================

static void ui_button_draw_border(ui_widget_t* widget) {
	ui_button_t* button = BUTTON(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t border_color = focused ? button->focus_border_color : button->border_color;

	// Draw border:
	if (button->border_thickness > 0) {
		lcd_fill_rect(x, y, width, height, border_color);
	}
}

static void ui_button_draw_background(ui_widget_t* widget) {
	ui_button_t* button = BUTTON(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? button->focus_background_color : button->background_color;

	// Draw border:
	ui_button_draw_border(widget);

	// Draw background:
	lcd_fill_rect(x + button->border_thickness, y + button->border_thickness, width - (2 * button->border_thickness), height - (2 * button->border_thickness), background_color);
}

static void ui_button_draw_label(ui_widget_t* widget) {
	ui_button_t* button = BUTTON(widget);
	ui_label_t* label = &button->label;

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	uint16_t inner_x = x + button->border_thickness;
	uint16_t inner_y = y + button->border_thickness;
	uint16_t inner_width = width - (2 * button->border_thickness);
	uint16_t inner_height = height - (2 * button->border_thickness);

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? button->focus_background_color : button->background_color;

	// Compute label position and size:
	uint16_t label_x = inner_x;
	uint16_t label_y = inner_y;
	uint16_t label_width = inner_width;
	uint16_t label_height = inner_height;

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



// =================== CONSTRUCTOR ===================

void ui_button_init(ui_button_t* button, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

    ui_widget_init(&button->base, x, y, width, height,
    		ui_button_draw,
			NULL,
			ui_button_on_focus,
			ui_button_on_blur,
			ui_button_on_event,
			NULL);

    button->on_click = NULL;


    // ============= FIELDS ==============

    // Border:
    button->border_thickness = UI_THEME_BUTTON_BORDER_THICKNESS;
    button->border_color = UI_THEME_BUTTON_BORDER_COLOR;

    // Background:
    button->background_color = UI_THEME_BUTTON_BACKGROUND_COLOR;

    // Label:
    ui_label_init(&button->label, 0, 0, 0, 0);

    // Focus:
    button->focus_border_color = UI_THEME_BUTTON_FOCUS_BORDER_COLOR;
    button->focus_background_color = UI_THEME_BUTTON_FOCUS_BACKGROUND_COLOR;
}



// ================ VIRTUAL FUNCTIONS ================

void ui_button_draw(ui_widget_t* widget) {
   ui_button_draw_background(widget);
   ui_button_draw_label(widget);
}

void ui_button_on_focus(ui_widget_t* widget) {
	widget->focused = true;
	ui_widget_invalidate(widget);
}

void ui_button_on_blur(ui_widget_t* widget) {
	widget->focused = false;
	ui_widget_invalidate(widget);
}

bool ui_button_on_event(ui_widget_t* widget, ui_event_t event) {
	ui_button_t* button = BUTTON(widget);

	switch (event) {
		case UI_EVENT_SELECT:
			if (button->on_click) { return button->on_click(); }
			return true;

		default:
			return false;
	}
}