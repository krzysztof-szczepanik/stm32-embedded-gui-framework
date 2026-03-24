/**
 ******************************************************************************
 * @file     ui_footer.c
 * @brief    Footer section widget used at the bottom of application screens.
 *
 * @details  The footer is a semantic UI component placed at the bottom of a
 *           screen. It typically contains action buttons, status indicators,
 *           or other controls relevant to the current view.
 * 
 *           Although the footer internally uses ui_hbox_t for layout, it is
 *           represented by a dedicated type to:
 *           - improve readability and prevent accidental misuse
 *           - allow future extension of footer‑specific behavior
 *           - provide a clear semantic separation between screen sections
 *
 *           The footer inherits all behavior from ui_hbox_t, including
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

#include "ui_footer.h"
#include "lcd.h"



// =================== CONSTRUCTOR ===================

void ui_footer_init(ui_footer_t* footer, uint16_t height) {
	ui_hbox_init(&footer->base, 0, LCD_HEIGHT - height, LCD_WIDTH, height);

	footer->base.base.base.draw = ui_footer_draw;
	footer->base.base.base.update_layout = ui_footer_update_layout;
	footer->base.base.base.on_focus = ui_footer_on_focus;
	footer->base.base.base.on_blur = ui_footer_on_blur;
	footer->base.base.base.on_event = ui_footer_on_event;
	footer->base.base.base.get_widgets = ui_footer_get_widgets;
}



// ==================== FUNCTIONS ====================

void ui_footer_add_widget(ui_footer_t* footer, ui_widget_t* widget) {
    ui_hbox_add_widget(&footer->base, widget);
}

void ui_footer_add_widgets(ui_footer_t* footer, ui_widget_t** widgets, uint8_t count) {
	ui_hbox_add_widgets(&footer->base, widgets, count);
}



// ================= FOCUS FUNCTIONS ==================

bool ui_footer_focus_next(ui_footer_t* footer) {
	return ui_hbox_focus_next(&footer->base);
}

bool ui_footer_focus_previous(ui_footer_t* footer) {
	return ui_hbox_focus_previous(&footer->base);
}



// ================ VIRTUAL FUNCTIONS ================

void ui_footer_draw(ui_widget_t* widget) {
	ui_hbox_draw(widget);
}

void ui_footer_update_layout(ui_widget_t* widget) {
    ui_hbox_update_layout(widget);
}

void ui_footer_on_focus(ui_widget_t* widget) {
	ui_hbox_on_focus(widget);
}

void ui_footer_on_blur(ui_widget_t* widget) {
	ui_hbox_on_blur(widget);
}

bool ui_footer_on_event(ui_widget_t* widget, ui_event_t event) {
	return ui_hbox_on_event(widget, event);
}

uint8_t ui_footer_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets) {
	return ui_hbox_get_widgets(widget, out_widgets);
}