/**
 ******************************************************************************
 * @file     ui_header.c
 * @brief    Header section widget used at the top of application screens.
 *
 * @details  The header is a semantic UI component placed at the top of a
 *           screen. It typically contains navigation buttons, titles, icons,
 *           or other controls relevant to the current view.
 * 
 *           Although the header internally uses ui_hbox_t for layout, it is
 *           represented by a dedicated type to:
 *           - improve readability and prevent accidental misuse
 *           - allow future extension of header‑specific behavior
 *           - provide a clear semantic separation between screen sections
 *
 *           The header inherits all behavior from ui_hbox_t, including
 *           stretching, alignment, spacing, and child widget management.
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

#include "ui_header.h"
#include "lcd.h"



// =================== CONSTRUCTOR ===================

void ui_header_init(ui_header_t* header, uint16_t height) {
	ui_hbox_init(&header->base, 0, 0, LCD_WIDTH, height);

	header->base.base.base.draw = ui_header_draw;
	header->base.base.base.update_layout = ui_header_update_layout;
	header->base.base.base.on_focus = ui_header_on_focus;
	header->base.base.base.on_blur = ui_header_on_blur;
	header->base.base.base.on_event = ui_header_on_event;
	header->base.base.base.get_widgets = ui_header_get_widgets;
}



// ==================== FUNCTIONS ====================

void ui_header_add_widget(ui_header_t* header, ui_widget_t* widget) {
    ui_hbox_add_widget(&header->base, widget);
}

void ui_header_add_widgets(ui_header_t* header, ui_widget_t** widgets, uint8_t count) {
	ui_hbox_add_widgets(&header->base, widgets, count);
}



// ================= FOCUS FUNCTIONS ==================

bool ui_header_focus_next(ui_header_t* header) {
	return ui_hbox_focus_next(&header->base);
}

bool ui_header_focus_previous(ui_header_t* header) {
	return ui_hbox_focus_previous(&header->base);
}



// ================ VIRTUAL FUNCTIONS ================

void ui_header_draw(ui_widget_t* widget) {
	ui_hbox_draw(widget);
}

void ui_header_update_layout(ui_widget_t* widget) {
    ui_hbox_update_layout(widget);
}

void ui_header_on_focus(ui_widget_t* widget) {
	ui_hbox_on_focus(widget);
}

void ui_header_on_blur(ui_widget_t* widget) {
	ui_hbox_on_blur(widget);
}

bool ui_header_on_event(ui_widget_t* widget, ui_event_t event) {
	return ui_hbox_on_event(widget, event);
}

uint8_t ui_header_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets) {
	return ui_hbox_get_widgets(widget, out_widgets);
}