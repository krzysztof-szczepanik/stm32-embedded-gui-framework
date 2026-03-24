/**
 ******************************************************************************
 * @file     ltdc.h
 * @brief    LTDC peripheral handle interface.
 * 
 * @details  This module provides the global LTDC handle used by the system.
 *           The handle is initialized in main.c and later accessed by the
 *           lcd and lcd_buffer modules for display operations.
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

/** @addtogroup ltdc
 * @{
 */

#ifndef LTDC_H
#define LTDC_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_ltdc.h"



// ==================== VARIABLES ====================

/**
 * @brief  Handle structure for LTDC peripheral.
 * 
 * @note   Must be initialized before using LTDC functions.
 */
extern LTDC_HandleTypeDef hltdc;

#endif /* HW_LTDC_H */

/** @} */ // ltdc