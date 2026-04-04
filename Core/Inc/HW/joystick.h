/**
 ******************************************************************************
 * @file     joystick.h
 * @brief    Joystick hardware interface.
 *
 * @details  This module provides initialization and reading of the joystick
 *           hardware using ADC channels for VRx/VRy and a GPIO input for the
 *           button. It also provides simple functions for interpreting these
 *           readings as joystick events.
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

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>



// ====================== TYPES ======================

/**
 * @brief  Joystick events.
 */
typedef enum {
    JOYSTICK_NONE = 0,      /**< No movement */
    JOYSTICK_UP,            /**< Joystick moved up */
    JOYSTICK_DOWN,          /**< Joystick moved down */
    JOYSTICK_LEFT,          /**< Joystick moved left */
    JOYSTICK_RIGHT,         /**< Joystick moved right */
    JOYSTICK_CLICK,         /**< Joystick button pressed (state) */
    JOYSTICK_CLICK_EDGE,    /**< Joystick button pressed (impulse) */
    JOYSTICK_INVALID = 255  /**< Invalid state */
} joystick_event_t;



// ==================== FUNCTIONS ====================

/**
 * @brief  Initialize joystick hardware (ADC + GPIO).
 * 
 * @note   Configures ADC channels for VRx/VRy and GPIO for button.
 */
void joystick_init(void);

/**
 * @brief  Read joystick ADC and button values.
 * 
 * @note   Updates internal variables for later use in event detection.
 */
void joystick_read(void);

/**
 * @brief   Get the current joystick event.
 * 
 * @retval  Joystick event as 'joystick_event_t'.
 */
joystick_event_t joystick_get_event(void);



// ===================== GETTERS =====================

uint16_t joystick_get_vrx(void);

uint16_t joystick_get_vry(void);

uint8_t joystick_get_sw(void);

#endif /* JOYSTICK_H */