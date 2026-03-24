/**
 ******************************************************************************
 * @file     lcd_buffer.c
 * @brief    Implementation of the LTDC double‑buffering utility interface.
 * 
 * @details  This module provides a minimal interface for initializing LCD
 *           layers and performing VSYNC‑synchronized buffer swaps.
 * 
 *           These functions are used by higher‑level modules to
 *           achieve smooth, tear‑free screen updates.
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

#include "lcd_buffer.h"
#include "lcd.h"
#include "stm32f429i_discovery_lcd.h"



// ==================== VARIABLES ====================

// Current visible and draw layers:
static uint32_t current_display_layer = LCD_BACKGROUND_LAYER;
static uint32_t current_draw_layer = LCD_FOREGROUND_LAYER;

// Flag set by LTDC interrupt when ready to swap buffers:
volatile uint8_t ready_to_swap = 0;



// ================ HELPER FUNCTIONS ==================

// Function called by HAL when LTDC reaches a specific line (LCD_HEIGHT + 3 + 2) - sets the "ready_to_swap" flag:
void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc) {
	ready_to_swap = 1;
}



// =================== CONSTRUCTOR ===================

void lcd_buffer_init(void) {
	BSP_LCD_SetLayerVisible(LCD_BACKGROUND_LAYER, ENABLE);
	BSP_LCD_SetLayerVisible(LCD_FOREGROUND_LAYER, DISABLE);

	// Select the layer for drawing:
	BSP_LCD_SelectLayer(current_draw_layer);

	// Enable the LTDC line interrupt:
	__HAL_LTDC_ENABLE_IT(&hltdc, LTDC_IT_LI);

	// First synchronization of LTDC registers (without this, the foreground has garbage and flickering appears):
	lcd_swap_buffers();
}



// ==================== FUNCTIONS =====================

void lcd_swap_buffers(void) {

    // Waiting for the end of the frame (VSYNC) - triggering the interrupt:
    HAL_LTDC_ProgramLineEvent(&hltdc, LCD_HEIGHT + 3 + 2);

    // CPU waits until the ready_to_swap flag is set to 1, when it is set, it performs the layer swap:
    while (!ready_to_swap);
    ready_to_swap = 0;

    if (current_display_layer == LCD_BACKGROUND_LAYER) {
        // Background was visible -> show foreground:
        BSP_LCD_SetLayerVisible(LCD_BACKGROUND_LAYER, DISABLE);
        BSP_LCD_SetLayerVisible(LCD_FOREGROUND_LAYER, ENABLE);

        current_display_layer = LCD_FOREGROUND_LAYER;
        current_draw_layer    = LCD_BACKGROUND_LAYER;
    } else {
        // Foreground was visible -> show background:
        BSP_LCD_SetLayerVisible(LCD_FOREGROUND_LAYER, DISABLE);
        BSP_LCD_SetLayerVisible(LCD_BACKGROUND_LAYER, ENABLE);

        current_display_layer = LCD_BACKGROUND_LAYER;
        current_draw_layer    = LCD_FOREGROUND_LAYER;
    }

    // Select the invisible layer for drawing:
    BSP_LCD_SelectLayer(current_draw_layer);

    // Immediate application of LTDC configuration changes:
    HAL_LTDC_Reload(&hltdc, LTDC_RELOAD_VERTICAL_BLANKING);
    while (hltdc.Instance->SRCR != 0UL); // waiting until the reload is complete
}