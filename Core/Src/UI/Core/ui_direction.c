/**
 ******************************************************************************
 * @file     ui_direction.c
 * @brief    Implementation of the UI navigation direction state.
 *
 * @details  This module stores and provides the current UI navigation
 *           direction. It is used by the UI framework to determine from which
 *           side a navigation event originated, enabling features such as
 *           directional focus movement.
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

#include "ui_direction.h"



// ==================== VARIABLES ====================

static ui_direction_t current_direction = UI_DIRECTION_NONE;



// ===================== GETTERS =====================

ui_direction_t ui_direction_get(void) {
	return current_direction;
}



// ===================== SETTERS =====================

void ui_direction_set(ui_direction_t direction) {
	current_direction = direction;
}