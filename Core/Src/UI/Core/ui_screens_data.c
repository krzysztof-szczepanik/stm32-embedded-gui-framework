/**
 ******************************************************************************
 * @file     ui_screens_data.c
 * @brief    Shared UI state accessible by all screens.
 *
 * @details  This module stores global UI values that need to be shared
 *           between screens.
 * 
 *           For example, settings changed on one screen may affect what is
 *           displayed on another. Instead of passing values manually between
 *           screens, all shared state is stored here.
 *
 *           Each screen can read or update this state, and the screen manager
 *           calls the screen's update_data() callback whenever a screen
 *           becomes active, ensuring that the UI always reflects the latest
 *           values.
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


#include "ui_screens_data.h"
#include <string.h>

static ui_screens_data_t screens_data;



// =================== CONSTRUCTOR ===================

void ui_screens_data_init(void) {
    memset(&screens_data, 0, sizeof(screens_data));
}



// ===================== GETTERS =====================

ui_screens_data_t* ui_screens_data(void) {
    return &screens_data;
}