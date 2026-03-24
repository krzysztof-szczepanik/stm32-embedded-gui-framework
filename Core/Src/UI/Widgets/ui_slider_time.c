/**
 ******************************************************************************
 * @file     ui_slider_time.c
 * @brief    Time slider widget (HH:MM:SS formatting).
 *
 * @details  This widget represents a horizontal slider whose numeric value
 *           corresponds to time expressed in minutes. The displayed label
 *           automatically formats the value as HH:MM:SS, making it suitable
 *           for selecting durations, timers, schedules, or time offsets.
 *
 *           The widget supports:
 *           - a draggable handle
 *           - formatted time label
 *           - configurable range (min, max, step)
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

#include "ui_slider_time.h"
#include <string.h>
#include <stdio.h>
#include "ui_theme.h"
#include "lcd.h"



// ================= HELPER FUNCTIONS ================

static void ui_slider_time_draw_border(ui_widget_t* widget) {
	ui_slider_time_t* slider_time = SLIDER_TIME(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t border_color = focused ? slider_time->focus_border_color : slider_time->border_color;

	// Draw border:
	if (slider_time->border_thickness > 0) {
		lcd_fill_rect(x, y, width, height, border_color);
	}
}

static void ui_slider_time_draw_background(ui_widget_t* widget) {
	ui_slider_time_t* slider_time = SLIDER_TIME(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? slider_time->focus_background_color : slider_time->background_color;

	// Draw border:
	ui_slider_time_draw_border(widget);

	// Draw background:
	lcd_fill_rect(x + slider_time->border_thickness, y + slider_time->border_thickness, width - (2 * slider_time->border_thickness), height - (2 * slider_time->border_thickness), background_color);
}

static void ui_slider_time_draw_handle(ui_widget_t* widget) {
	ui_slider_time_t* slider_time = SLIDER_TIME(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	uint16_t inner_x = x + slider_time->border_thickness;
	uint16_t inner_y = y + slider_time->border_thickness;
	uint16_t inner_width = width - (2 * slider_time->border_thickness);
	uint16_t inner_height = height - (2 * slider_time->border_thickness);

	uint16_t padding = 4;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t handle_color = focused ? slider_time->focus_handle_color : slider_time->handle_color;

	// Values normalization:
	float normalized_ratio = 0.0f;
	if (slider_time->max > slider_time->min) {
		normalized_ratio = (float)(slider_time->value - slider_time->min) / (float)(slider_time->max - slider_time->min);
	}

	// Compute handle movement range:
	uint16_t min_x = inner_x + padding;
	uint16_t max_x = inner_x + inner_width - slider_time->handle_width - padding;

	// Compute handle position:
	int16_t handle_x = min_x + (uint16_t)(normalized_ratio * (max_x - min_x));
	uint16_t handle_y = inner_y + padding;

	// Draw handle:
	lcd_fill_rect(handle_x, handle_y, slider_time->handle_width, inner_height - (2 * padding), handle_color);
}

static void ui_slider_time_draw_label(ui_widget_t* widget) {
	ui_slider_time_t* slider_time = SLIDER_TIME(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? slider_time->focus_background_color : slider_time->background_color;

	// Update label text based on current slider_time value:
	int hours = slider_time->value / 60;
	int minutes = slider_time->value % 60;

	snprintf(slider_time->label, sizeof(slider_time->label), "%02d:%02d:00", hours, minutes);

	// Compute label position:
	uint16_t text_x = x + (width - slider_time->label_font->Width * strlen(slider_time->label)) / 2;
	uint16_t text_y = y + (height - slider_time->label_font->Height) / 2 + 2;

	// Draw label:
	lcd_set_font(slider_time->label_font);
	lcd_set_text_color(slider_time->label_font_color);
	lcd_set_back_color(background_color);

	lcd_display_string_at(text_x, text_y, slider_time->label, LCD_ALIGN_LEFT);
}



// =================== CONSTRUCTOR ===================

void ui_slider_time_init(ui_slider_time_t* slider_time, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

    ui_widget_init(&slider_time->base, x, y, width, height,
    		ui_slider_time_draw,
			NULL,
			ui_slider_time_on_focus,
			ui_slider_time_on_blur,
			ui_slider_time_on_event,
			NULL);


    // ============= FIELDS ==============

    // Label:
    slider_time->label_font = UI_THEME_SLIDER_TIME_LABEL_FONT;
    slider_time->label_font_color = UI_THEME_SLIDER_TIME_LABEL_FONT_COLOR;

    // Handle:
    slider_time->handle_width = UI_THEME_SLIDER_TIME_HANDLE_WIDTH;
    slider_time->handle_color = UI_THEME_SLIDER_TIME_HANDLE_COLOR;

    // Border:
    slider_time->border_thickness = UI_THEME_SLIDER_TIME_BORDER_THICKNESS;
    slider_time->border_color = UI_THEME_SLIDER_TIME_BORDER_COLOR;

    // Background:
    slider_time->background_color = UI_THEME_SLIDER_TIME_BACKGROUND_COLOR;

    // Focus:
    slider_time->focus_border_color = UI_THEME_SLIDER_TIME_FOCUS_BORDER_COLOR;
    slider_time->focus_background_color = UI_THEME_SLIDER_TIME_FOCUS_BACKGROUND_COLOR;
    slider_time->focus_handle_color = UI_THEME_SLIDER_TIME_FOCUS_HANDLE_COLOR;

    // Values range:
    slider_time->min = 0;
    slider_time->max = 100;
    slider_time->value = 0;
    slider_time->step = 1;
}



// ================ VIRTUAL FUNCTIONS ================

void ui_slider_time_draw(ui_widget_t* widget) {
    ui_slider_time_draw_background(widget);
    ui_slider_time_draw_handle(widget);
    ui_slider_time_draw_label(widget);
}

void ui_slider_time_on_focus(ui_widget_t* widget) {
	widget->focused = true;
	ui_widget_invalidate(widget);
}

void ui_slider_time_on_blur(ui_widget_t* widget) {
	widget->focused = false;
	ui_widget_invalidate(widget);
}

bool ui_slider_time_on_event(ui_widget_t* widget, ui_event_t event) {
    ui_slider_time_t* slider_time = SLIDER_TIME(widget);

    int16_t new_value = slider_time->value;

    switch(event) {
        case UI_EVENT_RIGHT: new_value += slider_time->step; break;
        case UI_EVENT_LEFT:  new_value -= slider_time->step; break;
        default: return false;
    }

    // Limit to range <min, max>:
    if (new_value < slider_time->min) { new_value = slider_time->min; }
    if (new_value > slider_time->max) { new_value = slider_time->max; }

    slider_time->value = new_value;

    return true;
}