/**
 ******************************************************************************
 * @file     lcd.c
 * @brief    Implementation of the LCD initialization and drawing interface.
 * 
 * @details  This module initializes the LCD, configures background and
 *           foreground layers, clears frame buffers and sets default colors
 *           and fonts.
 * 
 *           It also provides simple drawing functions such as text rendering,
 *           rectangle filling, rectangle outlines and layer selection, using
 *           the platform’s LCD BSP driver.
 * 
 *           Buffer swapping and VSYNC synchronization are handled by the
 *           lcd_buffer module.
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

#include "lcd.h"
#include <stdint.h>
#include <string.h>
#include "ltdc.h"
#include "stm32f429i_discovery_lcd.h"



// ================ HELPER FUNCTIONS ==================

static void lcd_clear_buffer (uint32_t address) {
    uint32_t size = LCD_WIDTH * LCD_HEIGHT * 4;
    memset((void*)address, 0x00, size);
}



// =================== CONSTRUCTOR ===================

void lcd_init(void) {
    // Double initialization required by STM32F429I:
    BSP_LCD_Init();
    BSP_LCD_Init();

    uint32_t offset = LCD_WIDTH * LCD_HEIGHT * 4; // calculate foreground offset

    // Clear frame buffers:
    lcd_clear_buffer(LCD_FRAME_BUFFER);
    lcd_clear_buffer(LCD_FRAME_BUFFER + offset);

    // Initialize layers:
    BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER, LCD_FRAME_BUFFER);
    BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER, LCD_FRAME_BUFFER + offset);

    // Set initial colors:
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

    // Clear both layers:
    BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
    BSP_LCD_Clear(LCD_COLOR_BLACK);

    BSP_LCD_SelectLayer(LCD_BACKGROUND_LAYER);
    BSP_LCD_Clear(LCD_COLOR_BLACK);
}



// =================== FUNCTIONS =====================

void lcd_set_text_color(uint32_t color) {
    BSP_LCD_SetTextColor(color);
}

void lcd_set_back_color(uint32_t color) {
    BSP_LCD_SetBackColor(color);
}

void lcd_set_font(void* font) {
    BSP_LCD_SetFont((sFONT*)font);
}

void lcd_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    BSP_LCD_SetTextColor(color);
    BSP_LCD_FillRect(x, y, width, height);
}

void lcd_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    BSP_LCD_SetTextColor(color);
    BSP_LCD_DrawRect(x, y, width, height);
}

void lcd_display_string_at(uint16_t x, uint16_t y, const char* text, lcd_align_t mode) {

    Text_AlignModeTypdef bsp_mode;

    switch (mode) {
        case LCD_ALIGN_CENTER: bsp_mode = CENTER_MODE; break;
        case LCD_ALIGN_RIGHT:  bsp_mode = RIGHT_MODE;  break;
        default:               bsp_mode = LEFT_MODE;   break;
    }

    BSP_LCD_DisplayStringAt(x, y, (uint8_t*)text, bsp_mode);
}

void lcd_clear(uint32_t color) {
    BSP_LCD_Clear(color);
}

void lcd_select_layer(lcd_layer_t layer) {
    BSP_LCD_SelectLayer((uint32_t)layer);
}