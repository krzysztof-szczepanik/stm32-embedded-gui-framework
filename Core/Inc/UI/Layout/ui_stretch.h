/**
 ******************************************************************************
 * @file     ui_stretch.h
 * @brief    Stretching behavior for widgets inside layout containers.
 *
 * @details  This module defines stretch policies used by layout containers
 *           such as HBox, VBox, Header, Footer, and others.
 * 
 *           Stretching  determines how a widget expands to fill available
 *           space along the horizontal and/or vertical axis.
 *
 *           These values are used by container layout engines during size
 *           allocation.
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

#ifndef UI_STRETCH_H
#define UI_STRETCH_H



// ====================== TYPES ======================

/**
 * @brief  Stretching behavior for widgets inside containers.
 */
typedef enum {
    UI_STRETCH_NONE,   /**< No stretching. Widget keeps its size. */
    UI_STRETCH_WIDTH,   /**< Stretch horizontally. */
    UI_STRETCH_HEIGHT,  /**< Stretch vertically. */
    UI_STRETCH_BOTH     /**< Stretch in both directions. */
} ui_stretch_t;

#endif /* UI_STRETCH_H */