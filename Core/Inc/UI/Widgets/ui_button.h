/**
 ******************************************************************************
 * @file     ui_button.h
 * @brief    Clickable button widget with label and focus styling.
 *
 * @details  This module defines a simple interactive button widget used in
 *           the UI framework. A button consists of:
 *           - a base widget (ui_widget_t)
 *           - a label displayed inside the button
 *           - border and background styling
 *           - focus‑specific colors
 *           - an optional on_click callback
 *
 *           The button supports focus handling, drawing, and event
 *           processing through its virtual functions.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 Krzysztof Szczepanik.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE
 * file in the root directory of this software component. If no LICENSE
 * file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>
#include "ui_widget.h"
#include "ui_label.h"



// ====================== TYPES ======================

/**
 * @brief    Button widget.
 *
 * @details  A button is a clickable UI element containing a label and
 *           customizable visual properties such as border, background,
 *           and focus colors. It inherits from ui_widget_t and overrides
 *           its virtual functions to implement drawing, focus handling,
 *           and event processing.
 */
typedef struct {
	// Base widget:
	ui_widget_t base;                 /**< Base widget. */

    // Border:
    uint8_t border_thickness;         /**< Border thickness. */
    uint32_t border_color;            /**< Border color. */

    // Background:
    uint32_t background_color;        /**< Background color. */

	// Label:
	ui_label_t label;                 /**< Label displayed inside the button. */

    // Focus:
    uint32_t focus_border_color;      /**< Border color when focused. */
    uint32_t focus_background_color;  /**< Background color when focused. */

    /**
     * @brief  Optional click callback.
     * 
     * @return true if the click was handled, false otherwise.
     */
    bool (*on_click)(void);
} ui_button_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initialize a button widget.
 *
 * @details  Sets geometry, assigns virtual functions, initializes default
 *           properties and internal label.
 * 
 *           Most default properties are defined in @ref ui_theme.h.
 *
 * @param    button Pointer to the button.
 * @param    x      X position.
 * @param    y      Y position.
 * @param    width  Button width.
 * @param    height Button height.
 */
void ui_button_init(ui_button_t* button, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draw the button.
 *
 * @param    widget Pointer to the button's base widget.
 */
void ui_button_draw(ui_widget_t* widget);

/**
 * @brief    Called when the button receives focus.
 *
 * @param    widget Pointer to the button's base widget.
 */
void ui_button_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the button loses focus.
 *
 * @param    widget Pointer to the button's base widget.
 */
void ui_button_on_blur(ui_widget_t* widget);

/**
 * @brief    Handle UI events for the button.
 *
 * @details  If the event is UI_EVENT_SELECT and the button has a
 *           @ref ui_button_t::on_click "on_click()" callback, the callback
 *           is executed.
 *
 * @param    widget Pointer to the button's base widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_button_on_event(ui_widget_t* widget, ui_event_t event);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_button_x(ui_button_t* button) { return &button->base.x; }
static inline int16_t* ui_button_y(ui_button_t* button) { return &button->base.y; }
static inline uint16_t* ui_button_width(ui_button_t* button) { return &button->base.width; }
static inline uint16_t* ui_button_height(ui_button_t* button) { return &button->base.height; }
static inline bool* ui_button_focusable(ui_button_t* button) { return &button->base.focusable; }

// Border:
static inline uint8_t* ui_button_border_thickness(ui_button_t* button) { return &button->border_thickness; }
static inline uint32_t* ui_button_border_color(ui_button_t* button) { return &button->border_color; }

// Background:
static inline uint32_t* ui_button_background_color(ui_button_t* button) { return &button->background_color; }

// Label:
static inline ui_label_t* ui_button_label(ui_button_t* button) { return &button->label; }

// Focus:
static inline uint32_t* ui_button_focus_border_color(ui_button_t* button) { return &button->focus_border_color; }
static inline uint32_t* ui_button_focus_background_color(ui_button_t* button) { return &button->focus_background_color; }

// On_click:
static inline bool (**ui_button_on_click(ui_button_t* button))(void) { return &button->on_click; }



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_button_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a button instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a button.
 */
#define BUTTON(widget) ((ui_button_t*)(widget))


// Base widget:
#define button_x(button)                      (*ui_button_x(button))
#define button_y(button)                      (*ui_button_y(button))
#define button_width(button)                  (*ui_button_width(button))
#define button_height(button)                 (*ui_button_height(button))
#define button_focusable(button)              (*ui_button_focusable(button))

// Border:
#define button_border_thickness(button)       (*ui_button_border_thickness(button))
#define button_border_color(button)           (*ui_button_border_color(button))

// Background:
#define button_background_color(button)       (*ui_button_background_color(button))

// Label:
#define button_label(button)                  (*ui_button_label(button))

// Focus:
#define button_focus_border_color(button)     (*ui_button_focus_border_color(button))
#define button_focus_background_color(button) (*ui_button_focus_background_color(button))

// On_click:
#define button_on_click(button)               (*ui_button_on_click(button))

#endif /* BUTTON_H */