/**
 ******************************************************************************
 * @file     joystick.c
 * @brief    Implementation of the joystick hardware interface.
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

#include "joystick.h"
#include "hardware_io.h"

// Thresholds for joystick directions:
#define JOYSTICK_THRESHOLD_LOW  1500
#define JOYSTICK_THRESHOLD_HIGH 2500



// ==================== VARIABLES ====================

// Variables for storing ADC and GPIO values:
static uint16_t joystick_vrx = 0;
static uint16_t joystick_vry = 0;
static uint8_t  joystick_sw = 1;
static uint8_t previous_sw = 1; // previous state of the click button (for JOYSTICK_CLICK_EDGE)



// ==================== FUNCTIONS ====================

void joystick_init(void) {
    configure_adc_registers();
    configure_gpio_registers();
}

// Reading raw values from ADC and GPIO:
void joystick_read(void) {
        previous_sw = joystick_sw;                       // Store previous button state (for JOYSTICK_CLICK_EDGE)
        joystick_vrx = read_adc(11);                     // PC1 => ADC1_IN11
        joystick_vry = read_adc(12);                     // PC2 => ADC1_IN12
        joystick_sw  = read_gpio_pin(GPIOC, GPIO_PIN_3); // PC3 | 0 = pressed, 1 = not pressed
}

joystick_event_t joystick_get_event(void) {

    // Pressed:
	if (previous_sw == 1 && joystick_sw == 0) {	return JOYSTICK_CLICK_EDGE; } // impulse
	if (joystick_sw == 0) { return JOYSTICK_CLICK; } // state

    // Up / down:
    if (joystick_vry < JOYSTICK_THRESHOLD_LOW)  { return JOYSTICK_UP; }
    if (joystick_vry > JOYSTICK_THRESHOLD_HIGH) { return JOYSTICK_DOWN; }

    // Left / right:
    if (joystick_vrx < JOYSTICK_THRESHOLD_LOW)  { return JOYSTICK_LEFT; }
    if (joystick_vrx > JOYSTICK_THRESHOLD_HIGH) { return JOYSTICK_RIGHT; }

    return JOYSTICK_NONE;
}



// ===================== GETTERS =====================

uint16_t joystick_get_vrx(void) { return joystick_vrx; }
uint16_t joystick_get_vry(void) { return joystick_vry; }
uint8_t joystick_get_sw(void)  { return joystick_sw; }