/**
 ******************************************************************************
 * @file     ui_color.h
 * @brief    Utility for creating ARGB color values.
 * 
 * @details  This module provides a simple helper for constructing 32‑bit ARGB
 *           color values in a readable form, avoiding the need to write
 *           hexadecimal color constants directly in the code.
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

#ifndef UI_COLOR_H
#define UI_COLOR_H

#include <stdint.h>



// ==================== FUNCTIONS ====================

/**
 * @brief   Create a 32-bit ARGB color value.
 * 
 * @param   a Alpha channel (0–255).
 * @param   r Red channel (0–255).
 * @param   g Green channel (0–255).
 * @param   b Blue channel (0–255).
 * @return  32-bit color value in ARGB format (0xAARRGGBB).
 */
static inline uint32_t ui_color_argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)a << 24) |
           ((uint32_t)r << 16) |
           ((uint32_t)g << 8)  |
           ((uint32_t)b);
}

#endif /* UI_COLOR_H */