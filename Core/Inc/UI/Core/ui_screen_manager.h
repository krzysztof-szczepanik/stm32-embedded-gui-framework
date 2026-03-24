/**
 ******************************************************************************
 * @file     ui_screen_manager.h
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

#ifndef UI_SCREEN_MANAGER_H
#define UI_SCREEN_MANAGER_H

#include "ui_screen.h"
#include "ui_events.h"
#include "ui_screens.h"



// ==================== FUNCTIONS ====================

/**
 * @brief  Draws the currently active screen and swaps LCD buffers.
 */
void ui_screen_manager_show_current_screen(void);

/**
 * @brief  Routes a UI event to the active screen.
 *
 * @param  event UI event to process.
 */
void ui_screen_manager_handle_event(ui_event_t event);

/**
 * @brief  Registers a screen in the internal screen registry.
 *
 * @param  id     Screen identifier.
 * @param  screen Pointer to the screen instance.
 */
void ui_screen_manager_register_screen(ui_screen_id_t id, ui_screen_t* screen);

/**
 * @brief    Calls the update_data() callback of the active screen.
 *
 * @details  This function is used to refresh screen widgets whenever shared
 *           UI state changes (e.g., timer updates, settings changes).
 */
void ui_screen_manager_screens_data_update(void);



// ===================== GETTERS =====================

ui_screen_t* ui_screen_manager_get_current_screen(void);

ui_screen_id_t ui_screen_manager_get_current_screen_id(void);



// ===================== SETTERS =====================

void ui_screen_manager_set_current_screen(ui_screen_t* screen);

void ui_screen_manager_set_current_screen_by_id(ui_screen_id_t id);

#endif /* UI_SCREEN_MANAGER_H */