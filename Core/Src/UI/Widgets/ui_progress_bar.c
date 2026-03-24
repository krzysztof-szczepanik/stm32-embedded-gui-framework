/**
 ******************************************************************************
 * @file     ui_progress_bar.c
 * @brief    Horizontal progress bar widget with value label.
 *
 * @details  This widget displays a progress bar whose filled portion reflects
 *           the current value within a defined range. A centered label shows
 *           the numeric value along with an optional suffix (e.g. "%").
 *
 *           The widget supports:
 *           - configurable range (min, max, step)
 *           - a colored bar representing progress
 *           - a formatted label
 *           - focus‑dependent styling for border and background
 *
 *           Unlike a slider, the progress bar is typically non-interactive,
 *           but it may still respond to LEFT/RIGHT events if desired.
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

#include "ui_progress_bar.h"
#include <string.h>
#include <stdio.h>
#include "ui_theme.h"
#include "lcd.h"



// ================= HELPER FUNCTIONS ================

static void ui_progress_bar_draw_border(ui_widget_t* widget) {
	ui_progress_bar_t* progress_bar = PROGRESS_BAR(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t border_color = focused ? progress_bar->focus_border_color : progress_bar->border_color;

	// Draw border:
	if (progress_bar->border_thickness > 0) {
		lcd_fill_rect(x, y, width, height, border_color);
	}
}

static void ui_progress_bar_draw_background(ui_widget_t* widget) {
	ui_progress_bar_t* progress_bar = PROGRESS_BAR(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? progress_bar->focus_background_color : progress_bar->background_color;

	// Draw border:
	ui_progress_bar_draw_border(widget);

	// Draw background:
	lcd_fill_rect(x + progress_bar->border_thickness, y + progress_bar->border_thickness, width - (2 * progress_bar->border_thickness), height - (2 * progress_bar->border_thickness), background_color);
}

static void ui_progress_bar_draw_bar(ui_widget_t* widget) {
	ui_progress_bar_t* progress_bar = PROGRESS_BAR(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	uint16_t inner_x = x + progress_bar->border_thickness;
	uint16_t inner_y = y + progress_bar->border_thickness;
	uint16_t inner_width = width - (2 * progress_bar->border_thickness);
	uint16_t inner_height = height - (2 * progress_bar->border_thickness);

	uint16_t padding = 4;

	uint32_t bar_color = progress_bar->bar_color;

	// Values normalization:
	float normalized_ratio = 0.0f;
	if (progress_bar->max > progress_bar->min) {
		normalized_ratio = (float)(progress_bar->value - progress_bar->min) / (float)(progress_bar->max - progress_bar->min);
	}

	// Compute bar movement range:
	uint16_t min_x = inner_x + padding;
	uint16_t max_x = inner_x + inner_width - padding;

	// Compute bar position:
	int16_t bar_x = min_x;
	uint16_t bar_y = inner_y + padding;
	int16_t bar_width = (uint16_t)(normalized_ratio * (max_x - min_x));
	uint16_t bar_height = inner_height - (2 * padding);

	// Draw bar:
	if (bar_width > 0) {
	    lcd_fill_rect(bar_x, bar_y, bar_width, bar_height, bar_color);
	}
}

static void ui_progress_bar_draw_label(ui_widget_t* widget) {
	ui_progress_bar_t* progress_bar = PROGRESS_BAR(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? progress_bar->focus_background_color : progress_bar->background_color;

	// Update label text based on current progress_bar value:
	snprintf(progress_bar->label, sizeof(progress_bar->label), "%d%s", progress_bar->value, progress_bar->suffix);

	// Compute label position:
	uint16_t text_x = x + (width - progress_bar->label_font->Width * strlen(progress_bar->label)) / 2;
	uint16_t text_y = y + (height - progress_bar->label_font->Height) / 2 + 2;

	// Draw label:
	lcd_set_font(progress_bar->label_font);
	lcd_set_text_color(progress_bar->label_font_color);
	lcd_set_back_color(background_color);

	lcd_display_string_at(text_x, text_y, progress_bar->label, LCD_ALIGN_LEFT);
}



// =================== CONSTRUCTOR ===================

void ui_progress_bar_init(ui_progress_bar_t* progress_bar, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

    ui_widget_init(&progress_bar->base, x, y, width, height,
    		ui_progress_bar_draw,
			NULL,
			ui_progress_bar_on_focus,
			ui_progress_bar_on_blur,
			ui_progress_bar_on_event,
			NULL);

    progress_bar->base.focusable = false;


    // ============= FIELDS ==============

    // Label:
    progress_bar->label_font = UI_THEME_PROGRESS_BAR_LABEL_FONT;
    progress_bar->label_font_color = UI_THEME_PROGRESS_BAR_LABEL_FONT_COLOR;

    // Bar:
    progress_bar->bar_color = UI_THEME_PROGRESS_BAR_BAR_COLOR;

    // Border:
    progress_bar->border_thickness = UI_THEME_PROGRESS_BAR_BORDER_THICKNESS;
    progress_bar->border_color = UI_THEME_PROGRESS_BAR_BORDER_COLOR;

    // Background:
    progress_bar->background_color = UI_THEME_PROGRESS_BAR_BACKGROUND_COLOR;

    // Focus:
    progress_bar->focus_border_color = UI_THEME_PROGRESS_BAR_FOCUS_BORDER_COLOR;
    progress_bar->focus_background_color = UI_THEME_PROGRESS_BAR_FOCUS_BACKGROUND_COLOR;

	// Values range:
    progress_bar->min = 0;
    progress_bar->max = 100;
    progress_bar->value = 0;
    progress_bar->step = 1;
    progress_bar->suffix = "";
}



// ================ VIRTUAL FUNCTIONS ================

void ui_progress_bar_draw(ui_widget_t* widget) {
    ui_progress_bar_draw_background(widget);
    ui_progress_bar_draw_bar(widget);
    ui_progress_bar_draw_label(widget);
}

void ui_progress_bar_on_focus(ui_widget_t* widget) {
	widget->focused = true;
	ui_widget_invalidate(widget);
}

void ui_progress_bar_on_blur(ui_widget_t* widget) {
	widget->focused = false;
	ui_widget_invalidate(widget);
}

bool ui_progress_bar_on_event(ui_widget_t* widget, ui_event_t event) {
    ui_progress_bar_t* progress_bar = PROGRESS_BAR(widget);

    int16_t new_value = progress_bar->value;

    switch(event) {
        case UI_EVENT_RIGHT: new_value += progress_bar->step; break;
        case UI_EVENT_LEFT:  new_value -= progress_bar->step; break;
        default: return false;
    }

	// Limit to range <min, max>:
    if (new_value < progress_bar->min) { new_value = progress_bar->min; }
    if (new_value > progress_bar->max) { new_value = progress_bar->max; }

    progress_bar->value = new_value;

    return true;
}