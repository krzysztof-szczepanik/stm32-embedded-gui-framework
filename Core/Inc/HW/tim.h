/**
 ******************************************************************************
 * @file     tim.h
 * @brief    TIM peripheral handle interface.
 * 
 * @details  This module provides the global TIM9 handle and a timer tick
 *           flag used by the main application loop. The timer is initialized
 *           in main.c, and its period‑elapsed interrupt sets the timer_tick
 *           flag.
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

#ifndef TIM_H
#define TIM_H

#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"



// ==================== VARIABLES ====================

/**
 * @brief  Handle structure for TIM9 peripheral.
 * 
 * @note   Must be initialized before starting the timer.
 */
extern TIM_HandleTypeDef htim9;

/**
 * @brief  Flag set by TIM9 period elapsed interrupt.
 * 
 * @note   Set to true when timer overflows; should be cleared by user code.
 */
extern volatile bool timer_tick;

#endif /* TIM_H */