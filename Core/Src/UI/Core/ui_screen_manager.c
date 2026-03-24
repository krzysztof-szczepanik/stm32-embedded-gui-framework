/**
 ******************************************************************************
 * @file     ui_screen_manager.c
 * @brief    Screen manager responsible for screen switching and event 
 *           routing.
 *
 * @details  This module manages all UI screens in the application. It stores
 *           registered screens, tracks the currently active screen, and
 *           provides functions for:
 *           - switching screens
 *           - updating shared UI state
 *           - routing UI events to the active screen
 *           - triggering redraws
 *
 *           The screen manager is used by the main application loop to
 *           display screens and process UI navigation events.
 *
 *           Typical usage:
 *           1. Initialize shared UI data with ui_screens_data_init()
 *           2. Initialize all screens
 *           3. Register screens using ui_screen_manager_register_screen()
 *           4. Select the initial screen with
 *              ui_screen_manager_set_current_screen()
 *           5. In the main loop, call:
 *              - ui_screen_manager_handle_event()
 *              - ui_screen_manager_show_current_screen()
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 Krzysztof Szczepanik.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "ui_screen_manager.h"
#include <stddef.h>
#include "lcd_buffer.h"
#include "ui_direction.h"
#include "ui_screens.h"



// ==================== VARIABLES ====================

static ui_screen_t* registry[UI_COUNT_SCREEN] = {NULL};
static ui_screen_t* current_screen = NULL;
static ui_screen_id_t current_screen_id;



// ==================== FUNCTIONS ====================

void ui_screen_manager_show_current_screen(void) {
	ui_screen_draw(&current_screen->base);
	lcd_swap_buffers();
}

void ui_screen_manager_handle_event(ui_event_t event) {
	ui_screen_handle_event(current_screen, event);
    current_screen->base.invalidated = true;
}

void ui_screen_manager_register_screen(ui_screen_id_t id, ui_screen_t* screen) {
	registry[id] = screen;
}

void ui_screen_manager_screens_data_update() {
	ui_screen_t* screen = current_screen;

	if (screen->update_data) {
		screen->update_data(screen);
	}
}



// ===================== GETTERS =====================

ui_screen_t* ui_screen_manager_get_current_screen(void) {
    return current_screen;
}

ui_screen_id_t ui_screen_manager_get_current_screen_id(void) {
    return current_screen_id;
}



// ===================== SETTERS =====================

void ui_screen_manager_set_current_screen(ui_screen_t* screen) {
	current_screen = screen;

	if (screen->update_data) {
		screen->update_data(screen);
	}

	ui_direction_set(UI_DIRECTION_DOWN);
    ui_screen_focus_first(screen);
}

void ui_screen_manager_set_current_screen_by_id(ui_screen_id_t id) {
	ui_screen_t* screen = registry[id];
	current_screen_id = id;

	ui_screen_manager_set_current_screen(screen);
}