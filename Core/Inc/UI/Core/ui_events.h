/**
 ******************************************************************************
 * @file     ui_events.h
 * @brief    Generic UI event abstraction.
 *
 * @details  This module defines the set of UI events used across the
 *           interface. It provides an abstraction layer over input hardware
 *           so that the UI logic remains independent of specific input
 *           devices such as joysticks, buttons or other controllers.
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

#ifndef UI_EVENTS_H
#define UI_EVENTS_H



// ====================== TYPES ======================

/**
 * @brief    Generic UI events used across the user interface.
 * 
 * @details  Provides an abstraction layer over input hardware (e.g. joystick),
 *           allowing UI logic to remain independent of specific input devices.
 */
typedef enum {
    UI_EVENT_NONE = 0,  /**< No event */
    UI_EVENT_UP,        /**< Navigation up */
    UI_EVENT_DOWN,      /**< Navigation down */
    UI_EVENT_LEFT,      /**< Navigation left */
    UI_EVENT_RIGHT,     /**< Navigation right */
    UI_EVENT_SELECT     /**< Selection/confirm action */
} ui_event_t;

#endif /* UI_EVENTS_H */