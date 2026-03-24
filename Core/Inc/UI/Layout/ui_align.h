/**
 ******************************************************************************
 * @file     ui_align.h
 * @brief    Alignment options for widgets inside layout containers.
 *
 * @details  This module defines horizontal and vertical alignment modes used
 *           by layout containers such as HBox and VBox. Alignment determines
 *           how widgets are positioned within the available space when they
 *           do not stretch to fill it.
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

#ifndef UI_ALIGN_H
#define UI_ALIGN_H



// ====================== TYPES ======================

/**
 * @brief  Horizontal alignment options.
 */
typedef enum {
    UI_ALIGN_LEFT,      /**< Align to the left edge. */
    UI_ALIGN_CENTER_X,  /**< Center horizontally. */
    UI_ALIGN_RIGHT      /**< Align to the right edge. */
} ui_align_x_t;

/**
 * @brief  Vertical alignment options.
 */
typedef enum {
    UI_ALIGN_TOP,       /**< Align to the top edge. */
    UI_ALIGN_CENTER_Y,  /**< Center vertically. */
    UI_ALIGN_BOTTOM     /**< Align to the bottom edge. */
} ui_align_y_t;

#endif /* UI_ALIGN_H */