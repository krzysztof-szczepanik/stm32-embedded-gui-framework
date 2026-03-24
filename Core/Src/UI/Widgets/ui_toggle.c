/**
 ******************************************************************************
 * @file     ui_toggle.c
 * @brief    Two‑state toggle widget (left/right switch).
 *
 * @details  This widget displays two selectable areas (left and right),
 *           separated by a vertical divider. Each area contains a label
 *           and can be highlighted depending on the selected state.
 *
 *           The widget is interactive: pressing SELECT switches between
 *           the left and right side.
 *
 *           It is useful for binary settings such as ON/OFF, YES/NO,
 *           ENABLE/DISABLE, etc.
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

#include "ui_toggle.h"
#include <string.h>
#include <stdio.h>
#include "ui_theme.h"
#include "lcd.h"



// ================= HELPER FUNCTIONS ================

static void ui_toggle_draw_background(ui_widget_t* widget) {
	ui_toggle_t* toggle = TOGGLE(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	uint16_t inner_x = x + toggle->border_thickness;
	uint16_t inner_y = y + toggle->border_thickness;
	uint16_t inner_width = width  - (2 * toggle->border_thickness);
	uint16_t inner_height = height - (2 * toggle->border_thickness);

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t border_color = focused ? toggle->focus_border_color : toggle->border_color;
	uint32_t background_color = focused ? toggle->focus_background_color : toggle->background_color;

	// Draw border:
	if (toggle->border_thickness > 0) {
		lcd_fill_rect(x, y, width, height, border_color);
	}

	// Draw background:
	lcd_fill_rect(x + toggle->border_thickness, y + toggle->border_thickness, width - (2 * toggle->border_thickness), height - (2 * toggle->border_thickness), background_color);

	// Compute separator position:
	uint16_t separator_x = inner_x + (inner_width / 2) - (toggle->border_thickness / 2);

	// Draw separator:
	lcd_fill_rect(separator_x, inner_y, toggle->border_thickness, inner_height, border_color);
}

static void ui_toggle_draw_label(ui_widget_t* widget) {
	ui_toggle_t* toggle = TOGGLE(widget);

	uint16_t x = widget->render_x;
	uint16_t y = widget->render_y;
	uint16_t width = widget->width;
	uint16_t height = widget->height;

	uint16_t inner_x = x + toggle->border_thickness;
	uint16_t inner_y = y + toggle->border_thickness;
	uint16_t inner_width = width  - (2 * toggle->border_thickness);
	uint16_t inner_height = height - (2 * toggle->border_thickness);

	uint16_t padding = 4;

	// Compute separator position:
	uint16_t separator_x = inner_x + (inner_width / 2) - (toggle->border_thickness / 2);

	// Compute left area position and size:
	uint16_t left_area_x = inner_x;
	uint16_t left_area_width = separator_x - inner_x;

	// Compute right area position and size:
	uint16_t right_area_x = separator_x + toggle->border_thickness;
	uint16_t right_area_width = (inner_x + inner_width) - right_area_x;

	// Select color depending on focus state:
	bool focused = widget->focused;

	uint32_t background_color = focused ? toggle->focus_background_color : toggle->background_color;
	uint32_t selected_color = focused ? toggle->focus_selected_color : toggle->selected_color;

	uint32_t left_area_color = (toggle->selected == UI_TOGGLE_LEFT) ? selected_color : background_color;
	uint32_t right_area_color = (toggle->selected == UI_TOGGLE_RIGHT) ? selected_color : background_color;

	// Draw background for left and right areas:
	lcd_fill_rect(left_area_x + padding, inner_y + padding, left_area_width - (2 * padding), inner_height - (2 * padding), left_area_color);
	lcd_fill_rect(right_area_x + padding, inner_y + padding, right_area_width - (2 * padding), inner_height - (2 * padding), right_area_color);

	// Compute label position for left area:
	uint16_t left_area_text_x = left_area_x + (left_area_width - toggle->left_area_label_font->Width * strlen(toggle->left_area_label)) / 2;
	uint16_t left_area_text_y = y + (height - toggle->left_area_label_font->Height) / 2 + 2;

	// Compute label position for right area:
	uint16_t right_area_text_x = right_area_x + (right_area_width - toggle->right_area_label_font->Width * strlen(toggle->right_area_label)) / 2;
	uint16_t right_area_text_y = y + (height - toggle->right_area_label_font->Height) / 2 + 2;

	// Draw label for left area:
	lcd_set_font(toggle->left_area_label_font);
	lcd_set_text_color(toggle->left_area_label_font_color);
	lcd_set_back_color(left_area_color);

	lcd_display_string_at(left_area_text_x, left_area_text_y, toggle->left_area_label, LCD_ALIGN_LEFT);

	// Draw label for right area:
	lcd_set_font(toggle->right_area_label_font);
	lcd_set_text_color(toggle->right_area_label_font_color);
	lcd_set_back_color(right_area_color);

	lcd_display_string_at(right_area_text_x, right_area_text_y, toggle->right_area_label, LCD_ALIGN_LEFT);
}



// =================== CONSTRUCTOR ===================

void ui_toggle_init(ui_toggle_t* toggle, int16_t x, int16_t y, uint16_t width, uint16_t height) {

	// ========== BASE WIDGET ===========

    ui_widget_init(&toggle->base, x, y, width, height,
    		ui_toggle_draw,
			NULL,
			ui_toggle_on_focus,
			ui_toggle_on_blur,
			ui_toggle_on_event,
			NULL);


     // ============= FIELDS ==============

    // Border:
    toggle->border_thickness = UI_THEME_TOGGLE_BORDER_THICKNESS;
    toggle->border_color = UI_THEME_TOGGLE_BORDER_COLOR;

    // Background:
    toggle->background_color = UI_THEME_TOGGLE_BACKGROUND_COLOR;

	// Left area:
    toggle->left_area_label = "OFF";
    toggle->left_area_label_font = UI_THEME_TOGGLE_LABEL_FONT;
    toggle->left_area_label_font_color = UI_THEME_TOGGLE_LABEL_FONT_COLOR;

    // Right area:
    toggle->right_area_label = "ON";
    toggle->right_area_label_font = UI_THEME_TOGGLE_LABEL_FONT;
    toggle->right_area_label_font_color = UI_THEME_TOGGLE_LABEL_FONT_COLOR;

    // Selected area:
    toggle->selected = UI_TOGGLE_LEFT;
    toggle->selected_color = UI_THEME_TOGGLE_SELECTED_COLOR;

    // Focus:
    toggle->focus_border_color = UI_THEME_TOGGLE_FOCUS_BORDER_COLOR;
    toggle->focus_background_color = UI_THEME_TOGGLE_FOCUS_BACKGROUND_COLOR;
    toggle->focus_selected_color = UI_THEME_TOGGLE_FOCUS_SELECTED_COLOR;
}



// ================ VIRTUAL FUNCTIONS ================

void ui_toggle_draw(ui_widget_t* widget) {
    ui_toggle_draw_background(widget);
    ui_toggle_draw_label(widget);
}

void ui_toggle_on_focus(ui_widget_t* widget) {
	widget->focused = true;
	ui_widget_invalidate(widget);
}

void ui_toggle_on_blur(ui_widget_t* widget) {
	widget->focused = false;
	ui_widget_invalidate(widget);
}

bool ui_toggle_on_event(ui_widget_t* widget, ui_event_t event) {
	ui_toggle_t* toggle = TOGGLE(widget);

	switch(event) {
		case UI_EVENT_SELECT: (toggle->selected == UI_TOGGLE_LEFT) ? (toggle->selected = UI_TOGGLE_RIGHT) : (toggle->selected = UI_TOGGLE_LEFT); break;
		default: return false;
	}

	return true;
}