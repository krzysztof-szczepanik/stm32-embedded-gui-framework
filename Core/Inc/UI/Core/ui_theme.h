/**
 ******************************************************************************
 * @file     ui_theme.h
 * @brief    Centralized UI theme configuration.
 *
 * @details  This module defines all defaults UI colors, fonts and style
 *           constants used across widgets and screens. It provides a single
 *           place for managing the visual appearance of the UI, ensuring
 *           consistent styling throughout the framework.
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

#ifndef UI_THEME_H
#define UI_THEME_H

#include "lcd.h"
#include "ui_color.h"
#include "stm32f429i_discovery_lcd.h"



// =================== SCREEN THEME ==================

#define UI_THEME_BACKGROUND_COLOR ui_color_argb(255, 255, 255, 255)



// ================= CONTAINER THEME =================

// Border:
#define UI_THEME_CONTAINER_BORDER_THICKNESS 2
#define UI_THEME_CONTAINER_BORDER_COLOR ui_color_argb(255, 198, 198, 198)

// Background:
#define UI_THEME_CONTAINER_BACKGROUND_COLOR ui_color_argb(255, 248, 248, 248)



// =================== LABEL THEME ===================

// Border:
#define UI_THEME_LABEL_BORDER_THICKNESS 2
#define UI_THEME_LABEL_BORDER_COLOR ui_color_argb(255, 193, 193, 193)

// Background:
#define UI_THEME_LABEL_BACKGROUND_COLOR ui_color_argb(255, 242, 242, 242)

// Label:
#define UI_THEME_LABEL_TEXT_FONT &Font20
#define UI_THEME_LABEL_TEXT_FONT_COLOR ui_color_argb(255, 48, 48, 48)

// Focus:
#define UI_THEME_LABEL_FOCUS_BORDER_COLOR ui_color_argb(255, 173, 173, 173)
#define UI_THEME_LABEL_FOCUS_BACKGROUND_COLOR ui_color_argb(255, 222, 222, 222)



// =================== BUTTON THEME ==================

// Border:
#define UI_THEME_BUTTON_BORDER_THICKNESS 2
#define UI_THEME_BUTTON_BORDER_COLOR ui_color_argb(255, 193, 193, 193)

// Background:
#define UI_THEME_BUTTON_BACKGROUND_COLOR ui_color_argb(255, 242, 242, 242)

// Focus:
#define UI_THEME_BUTTON_FOCUS_BORDER_COLOR ui_color_argb(255, 173, 173, 173)
#define UI_THEME_BUTTON_FOCUS_BACKGROUND_COLOR ui_color_argb(255, 222, 222, 222)



// ================= LIST_ITEM THEME =================

// Border:
#define UI_THEME_LIST_ITEM_BORDER_THICKNESS 2
#define UI_THEME_LIST_ITEM_BORDER_COLOR ui_color_argb(255, 193, 193, 193)

// Background:
#define UI_THEME_LIST_ITEM_BACKGROUND_COLOR ui_color_argb(255, 242, 242, 242)

// Label:
#define UI_THEME_LIST_ITEM_LABEL_PADDING 4

// Right area:
#define UI_THEME_LIST_ITEM_RIGHT_AREA_PADDING 4

// Focus:
#define UI_THEME_LIST_ITEM_FOCUS_BORDER_COLOR ui_color_argb(255, 173, 173, 173)
#define UI_THEME_LIST_ITEM_FOCUS_BACKGROUND_COLOR ui_color_argb(255, 222, 222, 222)



// ================ LABEL_VALUE THEME ================

// Border:
#define UI_THEME_LABEL_VALUE_BORDER_THICKNESS 2
#define UI_THEME_LABEL_VALUE_BORDER_COLOR ui_color_argb(255, 193, 193, 193)

// Background:
#define UI_THEME_LABEL_VALUE_BACKGROUND_COLOR ui_color_argb(255, 242, 242, 242)

// Left label:
#define UI_THEME_LABEL_VALUE_LEFT_LABEL_PADDING 4

// Right label:
#define UI_THEME_LABEL_VALUE_RIGHT_LABEL_PADDING 4



// =================== SLIDER THEME ==================

// Label:
#define UI_THEME_SLIDER_LABEL_FONT &Font20
#define UI_THEME_SLIDER_LABEL_FONT_COLOR ui_color_argb(255, 48, 48, 48)

// Handle:
#define UI_THEME_SLIDER_HANDLE_WIDTH 8
#define UI_THEME_SLIDER_HANDLE_COLOR ui_color_argb(255, 182, 203, 219)

// Border:
#define UI_THEME_SLIDER_BORDER_THICKNESS 2
#define UI_THEME_SLIDER_BORDER_COLOR ui_color_argb(255, 193, 193, 193)

// Background:
#define UI_THEME_SLIDER_BACKGROUND_COLOR ui_color_argb(255, 242, 242, 242)

// Focus:
#define UI_THEME_SLIDER_FOCUS_HANDLE_COLOR ui_color_argb(255, 167, 188, 204)
#define UI_THEME_SLIDER_FOCUS_BORDER_COLOR ui_color_argb(255, 173, 173, 173)
#define UI_THEME_SLIDER_FOCUS_BACKGROUND_COLOR ui_color_argb(255, 222, 222, 222)



// ================ SLIDER_TIME THEME ================

// Label:
#define UI_THEME_SLIDER_TIME_LABEL_FONT &Font20
#define UI_THEME_SLIDER_TIME_LABEL_FONT_COLOR ui_color_argb(255, 48, 48, 48)

// Handle:
#define UI_THEME_SLIDER_TIME_HANDLE_WIDTH 8
#define UI_THEME_SLIDER_TIME_HANDLE_COLOR ui_color_argb(255, 182, 203, 219)

// Border:
#define UI_THEME_SLIDER_TIME_BORDER_THICKNESS 2
#define UI_THEME_SLIDER_TIME_BORDER_COLOR ui_color_argb(255, 193, 193, 193)

// Background:
#define UI_THEME_SLIDER_TIME_BACKGROUND_COLOR ui_color_argb(255, 242, 242, 242)

// Focus:
#define UI_THEME_SLIDER_TIME_FOCUS_HANDLE_COLOR ui_color_argb(255, 167, 188, 204)
#define UI_THEME_SLIDER_TIME_FOCUS_BORDER_COLOR ui_color_argb(255, 173, 173, 173)
#define UI_THEME_SLIDER_TIME_FOCUS_BACKGROUND_COLOR ui_color_argb(255, 222, 222, 222)



// ================ PROGRESS_BAR THEME ===============

// Label:
#define UI_THEME_PROGRESS_BAR_LABEL_FONT &Font20
#define UI_THEME_PROGRESS_BAR_LABEL_FONT_COLOR ui_color_argb(255, 48, 48, 48)

// Bar:
#define UI_THEME_PROGRESS_BAR_BAR_COLOR ui_color_argb(255, 182, 203, 219)

// Border:
#define UI_THEME_PROGRESS_BAR_BORDER_THICKNESS 2
#define UI_THEME_PROGRESS_BAR_BORDER_COLOR ui_color_argb(255, 193, 193, 193)

// Background:
#define UI_THEME_PROGRESS_BAR_BACKGROUND_COLOR ui_color_argb(255, 242, 242, 242)

// Handle:
#define UI_THEME_PROGRESS_BAR_HANDLE_COLOR ui_color_argb(255, 193, 193, 193)

// Focus:
#define UI_THEME_PROGRESS_BAR_FOCUS_BORDER_COLOR ui_color_argb(255, 173, 173, 173)
#define UI_THEME_PROGRESS_BAR_FOCUS_BACKGROUND_COLOR ui_color_argb(255, 222, 222, 222)



// =================== TOGGLE THEME ==================

// Label:
#define UI_THEME_TOGGLE_LABEL_FONT &Font20
#define UI_THEME_TOGGLE_LABEL_FONT_COLOR ui_color_argb(255, 48, 48, 48)

// Border:
#define UI_THEME_TOGGLE_BORDER_THICKNESS 2
#define UI_THEME_TOGGLE_BORDER_COLOR ui_color_argb(255, 193, 193, 193)

// Background:
#define UI_THEME_TOGGLE_BACKGROUND_COLOR ui_color_argb(255, 242, 242, 242)

// Selected area:
#define UI_THEME_TOGGLE_SELECTED_COLOR ui_color_argb(255, 182, 203, 219)

// Focus:
#define UI_THEME_TOGGLE_FOCUS_BORDER_COLOR ui_color_argb(255, 173, 173, 173)
#define UI_THEME_TOGGLE_FOCUS_BACKGROUND_COLOR ui_color_argb(255, 222, 222, 222)
#define UI_THEME_TOGGLE_FOCUS_SELECTED_COLOR ui_color_argb(255, 167, 188, 204)

#endif /* UI_THEME_H */