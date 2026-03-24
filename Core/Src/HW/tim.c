/**
 ******************************************************************************
 * @file     tim.c
 * @brief    Implementation of the TIM peripheral handle interface.
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

#include "tim.h"



// ==================== VARIABLES ====================

TIM_HandleTypeDef htim9;

volatile bool timer_tick = false;



// ================ HELPER FUNCTIONS ==================

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM9) {
    	timer_tick = true;
    }
}