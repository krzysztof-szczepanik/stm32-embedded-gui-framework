/**
 ******************************************************************************
 * @file     ui_slider.c
 * @brief    Horizontal slider widget with value display.
 *
 * @details  This widget represents a horizontal slider with:
 *           - a draggable handle
 *           - a numeric value displayed as a centered label
 *           - configurable range (min, max, step)
 *           - optional suffix (e.g. "%", "°C")
 *           - focus‑dependent styling for border, background and handle
 *
 *           The slider responds to UI_EVENT_LEFT and UI_EVENT_RIGHT to
 *           decrease or increase its value.
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


#include "ui_slider.h"
#include <string.h>
#include <stdio.h>
#include "ui_theme.h"
#include "lcd.h"



// ================= HELPER FUNCTIONS ================

static void ui_slider_draw_border(ui_widget_t* widget) {
	ui_slider_t* slider = SLIDER(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t border_color = focused ? slider->focus_border_color : slider->border_color;

	// Draw border:
	if (slider->border_thickness > 0) {
		lcd_fill_rect(x, y, width, height, border_color);
	}
}

static void ui_slider_draw_background(ui_widget_t* widget) {
	ui_slider_t* slider = SLIDER(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? slider->focus_background_color : slider->background_color;

	// Draw border:
	ui_slider_draw_border(widget);

	// Draw background:
	lcd_fill_rect(x + slider->border_thickness, y + slider->border_thickness, width - (2 * slider->border_thickness), height - (2 * slider->border_thickness), background_color);
}

static void ui_slider_draw_handle(ui_widget_t* widget) {
	ui_slider_t* slider = SLIDER(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	uint16_t inner_x = x + slider->border_thickness;
	uint16_t inner_y = y + slider->border_thickness;
	uint16_t inner_width = width - (2 * slider->border_thickness);
	uint16_t inner_height = height - (2 * slider->border_thickness);

	uint16_t padding = 4;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t handle_color = focused ? slider->focus_handle_color : slider->handle_color;

	// Values normalization:
	float normalized_ratio = 0.0f;
	if (slider->max > slider->min) {
		normalized_ratio = (float)(slider->value - slider->min) / (float)(slider->max - slider->min);
	}

	// Compute handle movement range:
	uint16_t min_x = inner_x + padding;
	uint16_t max_x = inner_x + inner_width - slider->handle_width - padding;

	// Compute handle position:
	int16_t handle_x = min_x + (uint16_t)(normalized_ratio * (max_x - min_x));
	uint16_t handle_y = inner_y + padding;

	// Draw handle:
	lcd_fill_rect(handle_x, handle_y, slider->handle_width, inner_height - (2 * padding), handle_color);
}

static void ui_slider_draw_label(ui_widget_t* widget) {
	ui_slider_t* slider = SLIDER(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? slider->focus_background_color : slider->background_color;

	// Update label text based on current slider value:
	snprintf(slider->label, sizeof(slider->label), "%d%s", slider->value, slider->suffix);

	// Compute label position:
	uint16_t text_x = x + (width - slider->label_font->Width * strlen(slider->label)) / 2;
	uint16_t text_y = y + (height - slider->label_font->Height) / 2 + 2;

	// Draw label:
	lcd_set_font(slider->label_font);
	lcd_set_text_color(slider->label_font_color);
	lcd_set_back_color(background_color);

	lcd_display_string_at(text_x, text_y, slider->label, LCD_ALIGN_LEFT);
}



// =================== CONSTRUCTOR ===================

void ui_slider_init(ui_slider_t* slider, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

    ui_widget_init(&slider->base, x, y, width, height,
    		ui_slider_draw,
			NULL,
			ui_slider_on_focus,
			ui_slider_on_blur,
			ui_slider_on_event,
			NULL);


    // ============= FIELDS ==============

    // Label:
    slider->label_font = UI_THEME_SLIDER_LABEL_FONT;
    slider->label_font_color = UI_THEME_SLIDER_LABEL_FONT_COLOR;

    // Handle:
    slider->handle_width = UI_THEME_SLIDER_HANDLE_WIDTH;
    slider->handle_color = UI_THEME_SLIDER_HANDLE_COLOR;

    // Border:
    slider->border_thickness = UI_THEME_SLIDER_BORDER_THICKNESS;
    slider->border_color = UI_THEME_SLIDER_BORDER_COLOR;

    // Background:
    slider->background_color = UI_THEME_SLIDER_BACKGROUND_COLOR;

    // Focus:
    slider->focus_border_color = UI_THEME_SLIDER_FOCUS_BORDER_COLOR;
    slider->focus_background_color = UI_THEME_SLIDER_FOCUS_BACKGROUND_COLOR;
    slider->focus_handle_color = UI_THEME_SLIDER_FOCUS_HANDLE_COLOR;

    // Values range:
    slider->min = 0;
    slider->max = 100;
    slider->value = 0;
    slider->step = 1;
    slider->suffix = "";
}



// ================ VIRTUAL FUNCTIONS ================

void ui_slider_draw(ui_widget_t* widget) {
    ui_slider_draw_background(widget);
    ui_slider_draw_handle(widget);
    ui_slider_draw_label(widget);
}

void ui_slider_on_focus(ui_widget_t* widget) {
	widget->focused = true;
	ui_widget_invalidate(widget);
}

void ui_slider_on_blur(ui_widget_t* widget) {
	widget->focused = false;
	ui_widget_invalidate(widget);
}

bool ui_slider_on_event(ui_widget_t* widget, ui_event_t event) {
    ui_slider_t* slider = SLIDER(widget);

    int16_t new_value = slider->value;

    switch(event) {
        case UI_EVENT_RIGHT: new_value += slider->step; break;
        case UI_EVENT_LEFT:  new_value -= slider->step; break;
        default: return false;
    }

    // Limit to range <min, max>:
    if (new_value < slider->min) { new_value = slider->min; }
    if (new_value > slider->max) { new_value = slider->max; }

    slider->value = new_value;

    return true;
}