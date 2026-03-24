/**
 ******************************************************************************
 * @file     ui_direction.h
 * @brief    UI navigation direction state.
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

#ifndef UI_DIRECTION_H
#define UI_DIRECTION_H



// ====================== TYPES ======================

/**
 * @brief    UI navigation directions.
 * 
 * @details  Represents the direction from which a navigation event originates.
 *           Used to enable features like focus wrapping and dynamic UI 
 *           navigation.
 */
typedef enum {
    UI_DIRECTION_NONE,  /**< No direction */
    UI_DIRECTION_UP,    /**< Navigation from bottom to top */
    UI_DIRECTION_DOWN,  /**< Navigation from top to bottom */
    UI_DIRECTION_LEFT,  /**< Navigation from right to left */
    UI_DIRECTION_RIGHT  /**< Navigation from left to right */
} ui_direction_t;



// ===================== GETTERS =====================

ui_direction_t ui_direction_get(void);



// ===================== SETTERS =====================

void ui_direction_set(ui_direction_t direction);

#endif /* UI_DIRECTION_H */