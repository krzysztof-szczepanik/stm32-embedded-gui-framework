/**
 ******************************************************************************
 * @file     ui_label.c
 * @brief    Text label widget with alignment, padding and focus styling.
 *
 * @details  This module defines a non-interactive text label widget used
 *           throughout the UI framework. A label supports:
 *           - static or formatted dynamic text
 *           - customizable border and background
 *           - padding on all sides
 *           - horizontal and vertical alignment
 *           - focus‑specific colors
 *
 *           The label inherits from ui_widget_t and overrides the draw and
 *           focus handlers.
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

#include "ui_label.h"
#include <string.h>
#include <stdarg.h> // va_list, va_start, va_end
#include <stdio.h> // vsnprintf
#include "ui_theme.h"
#include "lcd.h"



// ================= HELPER FUNCTIONS ================

static void ui_label_draw_border(ui_widget_t* widget) {
	ui_label_t* label = LABEL(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t border_color = focused ? label->focus_border_color : label->border_color;

	// Draw border:
	if (label->border_thickness > 0) {
		lcd_fill_rect(x, y, width, height, border_color);
	}
}

static void ui_label_draw_background(ui_widget_t* widget) {
	ui_label_t* label = LABEL(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? label->focus_background_color : label->background_color;

	// Draw border:
	ui_label_draw_border(widget);

	// Draw background:
	lcd_fill_rect(x + label->border_thickness, y + label->border_thickness, width - (2 * label->border_thickness), height - (2 * label->border_thickness), background_color);
}

static void ui_label_draw_label(ui_widget_t* widget) {
	ui_label_t* label = LABEL(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	uint16_t inner_x = x + label->border_thickness + label->padding_left;
	uint16_t inner_y = y + label->border_thickness + label->padding_top;
	uint16_t inner_width = width  - (2 * label->border_thickness) - label->padding_left - label->padding_right;
	uint16_t inner_height = height - (2 * label->border_thickness) - label->padding_top - label->padding_bottom;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? label->focus_background_color : label->background_color;

	// Select text source:
	const char* text = label->use_text_buffer ? label->text_buffer : label->text;

    // Compute text size:
    uint16_t text_width = label->text_font->Width * strlen(text);
    uint16_t text_height = label->text_font->Height;

    uint16_t text_x = inner_x;
    uint16_t text_y = inner_y;

    // Horizontal alignment:
    switch (label->align_horizontal) {
        case UI_ALIGN_LEFT:     text_x = inner_x; break;
        case UI_ALIGN_CENTER_X: text_x = inner_x + (inner_width - text_width) / 2 + 2; break;
        case UI_ALIGN_RIGHT:    text_x = inner_x + (inner_width - text_width); break;
    }

    // Vertical alignment:
    switch (label->align_vertical) {
        case UI_ALIGN_TOP:      text_y = inner_y; break;
        case UI_ALIGN_CENTER_Y: text_y = inner_y + (inner_height - text_height) / 2 + 2; break;
        case UI_ALIGN_BOTTOM:   text_y = inner_y + (inner_height - text_height); break;
    }

    // Draw text:
	lcd_set_font(label->text_font);
	lcd_set_text_color(label->text_font_color);
	lcd_set_back_color(background_color);

	lcd_display_string_at(text_x, text_y, text, LCD_ALIGN_LEFT);
}



// =================== CONSTRUCTOR ===================

void ui_label_init(ui_label_t* label, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

    ui_widget_init(&label->base, x, y, width, height,
    		ui_label_draw,
			NULL,
			ui_label_on_focus,
			ui_label_on_blur,
			NULL,
			NULL);


    // ============= FIELDS ==============

    // Border:
    label->border_thickness = UI_THEME_LABEL_BORDER_THICKNESS;
    label->border_color = UI_THEME_LABEL_BORDER_COLOR;

    // Background:
    label->background_color = UI_THEME_LABEL_BACKGROUND_COLOR;

    // Label:
    label->text = "";
    label->use_text_buffer = false;
    label->text_font = UI_THEME_LABEL_TEXT_FONT;
    label->text_font_color = UI_THEME_LABEL_TEXT_FONT_COLOR;

    // Focus:
	label->focus_border_color = UI_THEME_LABEL_FOCUS_BORDER_COLOR;
	label->focus_background_color = UI_THEME_LABEL_FOCUS_BACKGROUND_COLOR;

    // Padding:
    label->padding_left = 0;
    label->padding_right = 0;
    label->padding_top = 0;
    label->padding_bottom = 0;

    // Alignment:
    label->align_horizontal = UI_ALIGN_LEFT;
    label->align_vertical = UI_ALIGN_TOP;
}



// ================ VIRTUAL FUNCTIONS ================

void ui_label_draw(ui_widget_t* widget) {
	ui_label_draw_background(widget);
	ui_label_draw_label(widget);
}

void ui_label_on_focus(ui_widget_t* widget) {
	widget->focused = true;
	ui_widget_invalidate(widget);
}

void ui_label_on_blur(ui_widget_t* widget) {
	widget->focused = false;
	ui_widget_invalidate(widget);
}



// ===================== SETTERS =====================

void ui_label_text_format(ui_label_t* label, const char* format, ...) {
    label->use_text_buffer = true;

    va_list args;
    va_start(args, format);
    vsnprintf(label->text_buffer, sizeof(label->text_buffer), format, args);
    va_end(args);
}