/**
 ******************************************************************************
 * @file     lcd_buffer.h
 * @brief    LTDC double‑buffering utility interface.
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

#ifndef LCD_BUFFER_H
#define LCD_BUFFER_H

#include <stdint.h>
#include "ltdc.h"



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initialize the LCD framebuffer module.
 * 
 * @details  Sets up background/foreground layers and enables the LTDC line
 *           interrupt. Also performs first buffer swap to avoid flickering in
 *           foreground layer.
 */
void lcd_buffer_init(void);



// ==================== FUNCTIONS =====================

/**
 * @brief    Swap the current draw and display buffers (double buffering).
 * 
 * @details  Waits for VSYNC using LTDC line event callback and switches the
 *           visible layer with the draw layer. Ensures smooth rendering
 *           without tearing.
 */
void lcd_swap_buffers(void);

#endif /* LCD_BUFFER_H */