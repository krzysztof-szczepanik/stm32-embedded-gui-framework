/**
 ******************************************************************************
 * @file     ui_screens_data.h
 * @brief    Shared UI state accessible by all screens.
 *
 * @details  This module stores global UI values that need to be shared
 *           between screens.
 * 
 *           For example, settings changed on one screen may affect what is
 *           displayed on another. Instead of passing values manually between
 *           screens, all shared state is stored here.
 *
 *           Each screen can read or update this state, and the screen manager
 *           calls the screen's update_data() callback whenever a screen
 *           becomes active, ensuring that the UI always reflects the latest
 *           values.
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

#ifndef UI_SCREENS_DATA_H
#define UI_SCREENS_DATA_H

#include <stdint.h>
#include <stdbool.h>



// ====================== TYPES ======================

typedef enum {
    TIMER_STOPPED,
    TIMER_RUNNING
} timer_state_t;

/**
 * @brief    Structure containing all shared UI state.
 *
 * @details  Each screen may read or modify these values. The screen manager
 *           ensures that screens refresh their widgets when becoming active.
 */
typedef struct {

	// ========== MODES_SCREEN ==========
	int16_t list_item_rpm_value;
	int16_t list_item_temp_value;


	// ========== MAIN_SCREEN ===========

	timer_state_t timer_state;
	int16_t list_item_time_value; // seconds
	int16_t list_item_time_value_old;


	// ======== SETTINGS_SCREEN =========

	int16_t list_item_volume_value;
	bool list_item_sound_value; // 0 = OFF, 1 = ON
	bool list_item_sim_value; // 0 = OFF, 1 = ON

} ui_screens_data_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initializes the shared UI state structure.
 *
 * @details  This function clears all stored values and resets the global UI
 *           state to a known default. It must be called once during system
 *           startup before any screen attempts to access shared UI data.
 */
void ui_screens_data_init(void);



// ===================== GETTERS =====================

ui_screens_data_t* ui_screens_data(void);



// ===================== MACROS ======================

#define screens_data(void) (*ui_screens_data(void))

#endif /* UI_SCREENS_DATA_H */