/**
 ******************************************************************************
 * @file     ui_label_value.c
 * @brief    Key–value label widget (left text + right value).
 *
 * @details  This widget displays a pair of text labels arranged horizontally:
 *           a left label (key) and a right label (value), separated by a
 *           vertical separator. It is useful for presenting information in
 *           a structured “Label: Value” format (e.g. “Temperature: 21°C”).
 *
 *           The widget is non-interactive and does not handle events.
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

#include "ui_label_value.h"
#include <string.h>
#include <stdlib.h>
#include "ui_theme.h"
#include "lcd.h"



// ================= HELPER FUNCTIONS ================

static void ui_label_value_draw_separator(ui_widget_t* widget) {
	ui_label_value_t* label_value = LABEL_VALUE(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t height = widget->height;

	uint16_t inner_x = x + label_value->border_thickness;
	uint16_t inner_y = y + label_value->border_thickness;
	uint16_t inner_height = height - (2 * label_value->border_thickness);

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t separator_color = focused ? label_value->focus_border_color : label_value->border_color;

	// Compute separator position and size:
	uint16_t separator_x = inner_x + label_value->separator_x_offset;
	uint16_t separator_y = inner_y;
	uint16_t separator_width = label_value->border_thickness;
	uint16_t separator_height = inner_height;

	// Draw separator:
	if (label_value->border_thickness > 0) {
		lcd_fill_rect(separator_x, separator_y, separator_width, separator_height, separator_color);
	}
}

static void ui_label_value_draw_border(ui_widget_t* widget) {
	ui_label_value_t* label_value = LABEL_VALUE(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t border_color = focused ? label_value->focus_border_color : label_value->border_color;

	// Draw border:
	if (label_value->border_thickness > 0) {
		lcd_fill_rect(x, y, width, height, border_color);
	}
}

static void ui_label_value_draw_background(ui_widget_t* widget) {
	ui_label_value_t* label_value = LABEL_VALUE(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? label_value->focus_background_color : label_value->background_color;

	// Draw border:
	ui_label_value_draw_border(widget);

	// Draw background:
	lcd_fill_rect(x + label_value->border_thickness, y + label_value->border_thickness, width - (2 * label_value->border_thickness), height - (2 * label_value->border_thickness), background_color);

	// Draw separator:
	ui_label_value_draw_separator(widget);
}

static void ui_label_value_draw_left_label(ui_widget_t* widget) {
	ui_label_value_t* label_value = LABEL_VALUE(widget);
	ui_label_t* label = &label_value->left_label;

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t height = widget->height;

	uint16_t inner_x = x + label_value->border_thickness;
	uint16_t inner_y = y + label_value->border_thickness;
	uint16_t inner_height = height - (2 * label_value->border_thickness);

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? label_value->focus_background_color : label_value->background_color;

	// Compute label position and size:
	uint16_t label_x = inner_x + label_value->left_label_padding;
	uint16_t label_y = inner_y + label_value->left_label_padding;
	uint16_t label_width = label_value->separator_x_offset - (2 * label_value->left_label_padding);
	uint16_t label_height = inner_height - (2 * label_value->left_label_padding);

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

static void ui_label_value_draw_right_label(ui_widget_t* widget) {
	ui_label_value_t* label_value = LABEL_VALUE(widget);
	ui_label_t* label = &label_value->right_label;

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	uint16_t inner_x = x + label_value->border_thickness;
	uint16_t inner_y = y + label_value->border_thickness;
	uint16_t inner_width = width - (2 * label_value->border_thickness);
	uint16_t inner_height = height - (2 * label_value->border_thickness);

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? label_value->focus_background_color : label_value->background_color;

	// Compute label position and size:
	uint16_t label_x = inner_x + (label_value->separator_x_offset + label_value->border_thickness) + label_value->right_label_padding;
	uint16_t label_y = inner_y + label_value->right_label_padding;
	uint16_t label_width = inner_width - (label_value->separator_x_offset + label_value->border_thickness) - (2 * label_value->right_label_padding);
	uint16_t label_height = inner_height - (2 * label_value->right_label_padding);

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

void ui_label_value_init(ui_label_value_t* label_value, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

    ui_widget_init(&label_value->base, x, y, width, height,
    		ui_label_value_draw,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL);

    label_value->base.focusable = false;


    // ============= FIELDS ==============

    // Border:
    label_value->border_thickness = UI_THEME_LABEL_VALUE_BORDER_THICKNESS;
    label_value->border_color = UI_THEME_LABEL_VALUE_BORDER_COLOR;

    // Background:
    label_value->background_color = UI_THEME_LABEL_VALUE_BACKGROUND_COLOR;

    // Separator:
    label_value->separator_x_offset = 100;

    // Left label:
    ui_label_init(&label_value->left_label, 0, 0, 0, 0);
    label_value->left_label_padding = UI_THEME_LABEL_VALUE_LEFT_LABEL_PADDING;

    // Right label:
	ui_label_init(&label_value->right_label, 0, 0, 0, 0);
	label_value->right_label_padding = UI_THEME_LABEL_VALUE_RIGHT_LABEL_PADDING;
}



// ================ VIRTUAL FUNCTIONS ================

void ui_label_value_draw(ui_widget_t* widget) {
	ui_label_value_draw_background(widget);
	ui_label_value_draw_left_label(widget);
	ui_label_value_draw_right_label(widget);
}