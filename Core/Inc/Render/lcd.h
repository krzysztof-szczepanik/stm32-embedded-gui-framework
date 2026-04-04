/**
 ******************************************************************************
 * @file     lcd.h
 * @brief    LCD initialization and drawing interface.
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

#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define LCD_WIDTH  240
#define LCD_HEIGHT 320



// ====================== TYPES ======================

/**
 * @brief  LCD text alignment.
 */
typedef enum {
	LCD_ALIGN_LEFT = 0,    /**< Left-aligned text */
	LCD_ALIGN_CENTER = 1,  /**< Center-aligned text */
	LCD_ALIGN_RIGHT = 2    /**< Right-aligned text */
} lcd_align_t;

/**
 * @brief  LCD layer selection.
 */
typedef enum {
    LCD_LAYER_BACKGROUND = 0,  /**< Background layer */
    LCD_LAYER_FOREGROUND = 1   /**< Foreground layer */
} lcd_layer_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief  Initialize LCD and configure background/foreground layers.
 * 
 * @note   Performs double initialization required by STM32F429I.
 */
void lcd_init(void);



// =================== FUNCTIONS =====================

/**
 * @brief  Set the text color for subsequent text rendering.
 * 
 * @param  color Color value (RGB565 format).
 */
void lcd_set_text_color(uint32_t color);

/**
 * @brief  Set the background color for text rendering.
 * 
 * @param  color Color value (RGB565 format).
 */
void lcd_set_back_color(uint32_t color);

/**
 * @brief  Set the font for text rendering.
 * 
 * @param  font Pointer to sFONT structure.
 */
void lcd_set_font(void* font);

/**
 * @brief  Fill a rectangle area with a color.
 * 
 * @param  x      X coordinate of top-left corner.
 * @param  y      Y coordinate of top-left corner.
 * @param  width  Width of rectangle.
 * @param  height Height of rectangle.
 * @param  color  Fill color.
 */
void lcd_fill_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief  Draw the outline of a rectangle.
 * 
 * @param  x      X coordinate of top-left corner.
 * @param  y      Y coordinate of top-left corner.
 * @param  width  Width of rectangle.
 * @param  height Height of rectangle.
 * @param  color  Outline color.
 */
void lcd_draw_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief  Display a string at a given position.
 * 
 * @param  x    X coordinate.
 * @param  y    Y coordinate.
 * @param  text Pointer to null-terminated string.
 * @param  mode Text alignment mode (left, center, right).
 */
void lcd_display_string_at(uint16_t x, uint16_t y, const char* text, lcd_align_t mode);

/**
 * @brief  Clear the LCD screen with a specific color.
 * 
 * @param  color Fill color.
 */
void lcd_clear(uint32_t color);

/**
 * @brief  Select active LCD layer for drawing operations.
 * 
 * @param  layer Layer to select (background/foreground).
 */
void lcd_select_layer(lcd_layer_t layer);

#endif /* LCD_H */