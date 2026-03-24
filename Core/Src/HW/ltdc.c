/**
 ******************************************************************************
 * @file     ltdc.c
 * @brief    Implementation of the LTDC peripheral handle interface.
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

#include "ltdc.h"



// ==================== VARIABLES ====================

LTDC_HandleTypeDef hltdc;