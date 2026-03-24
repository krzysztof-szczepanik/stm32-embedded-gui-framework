/**
 ******************************************************************************
 * @file     ui_slider_time.h
 * @brief    Time slider widget (HH:MM:SS formatting).
 *
 * @details  This widget represents a horizontal slider whose numeric value
 *           corresponds to time expressed in minutes. The displayed label
 *           automatically formats the value as HH:MM:SS, making it suitable
 *           for selecting durations, timers, schedules, or time offsets.
 *
 *           The widget supports:
 *           - a draggable handle
 *           - formatted time label
 *           - configurable range (min, max, step)
 *           - focus‑dependent styling for border, background and handle
 *
 *           The slider responds to UI_EVENT_LEFT and UI_EVENT_RIGHT to
 *           decrease or increase its value.
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

#ifndef UI_slider_time_TIME_H
#define UI_slider_time_TIME_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "ui_widget.h"
#include "stm32f429i_discovery_lcd.h"



// ====================== TYPES ======================

/**
 * @brief    Time slider widget (value displayed as HH:MM:SS).
 *
 * @details  The slider stores its value in minutes, but the label is always
 *           formatted as HH:MM:SS. This makes it ideal for selecting time
 *           durations or scheduling values.
 */
typedef struct {
	// Base widget:
	ui_widget_t base;                 /**< Base widget. */

	// Label:
    char label[32];                   /**< Buffer for formatted value text. */
    sFONT* label_font;                /**< Font used for the value label. */
    uint32_t label_font_color;        /**< Color of the value label. */

    // Handle:
	uint16_t handle_width;            /**< Width of the slider handle. */
	uint32_t handle_color;            /**< Default handle color. */

    // Border:
    uint8_t border_thickness;         /**< Border thickness. */
    uint32_t border_color;            /**< Border color. */

    // Background:
    uint32_t background_color;        /**< Background color. */

    // Focus:
    uint32_t focus_handle_color;      /**< Handle color when focused. */
    uint32_t focus_border_color;      /**< Border color when focused. */
    uint32_t focus_background_color;  /**< Background color when focused. */

    // Values range:
    int16_t min;                      /**< Minimum slider value. */
    int16_t max;                      /**< Maximum slider value. */
    int16_t value;                    /**< Current slider value. */
    int16_t step;                     /**< Step size for each left/right event. */
} ui_slider_time_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initialize a time slider widget.
 *
 * @details  Sets geometry, assigns virtual functions, initializes default
 *           properties.
 *
 *           Most default properties are defined in @ref ui_theme.h.
 *
 * @param    slider_time Pointer to the slider_time instance.
 * @param    x           X position.
 * @param    y           Y position.
 * @param    width       Slider_time width.
 * @param    height      Slider_time height.
 */
void ui_slider_time_init(ui_slider_time_t* slider_time, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draw the slider_time.
 *
 * @param    widget Pointer to the slider_time's base widget.
 */
void ui_slider_time_draw(ui_widget_t* widget);

/**
 * @brief    Called when the slider_time receives focus.
 *
 * @param    widget Pointer to the slider_time's base widget.
 */
void ui_slider_time_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the slider_time loses focus.
 *
 * @param    widget Pointer to the slider_time's base widget.
 */
void ui_slider_time_on_blur(ui_widget_t* widget);

/**
 * @brief    Handle UI events for the slider_time.
 *
 * @details  UI_EVENT_LEFT  decreases the value by step.
 *           UI_EVENT_RIGHT increases the value by step.
 *           The value is clamped to the <min, max> range.
 *
 * @param    widget Pointer to the slider_time's base widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_slider_time_on_event(ui_widget_t* widget, ui_event_t event);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_slider_time_x(ui_slider_time_t* slider_time) { return &slider_time->base.x; }
static inline int16_t* ui_slider_time_y(ui_slider_time_t* slider_time) { return &slider_time->base.y; }
static inline uint16_t* ui_slider_time_width(ui_slider_time_t* slider_time) { return &slider_time->base.width; }
static inline uint16_t* ui_slider_time_height(ui_slider_time_t* slider_time) { return &slider_time->base.height; }
static inline bool* ui_slider_time_focusable(ui_slider_time_t* slider_time) { return &slider_time->base.focusable; }

// Label:
static inline sFONT** ui_slider_time_label_font(ui_slider_time_t* slider_time) { return &slider_time->label_font; }
static inline uint32_t* ui_slider_time_label_font_color(ui_slider_time_t* slider_time) { return &slider_time->label_font_color; }

// Handle:
static inline uint16_t* ui_slider_time_handle_width(ui_slider_time_t* slider_time) { return &slider_time->handle_width; }
static inline uint32_t* ui_slider_time_handle_color(ui_slider_time_t* slider_time) { return &slider_time->handle_color; }

// Border:
static inline uint8_t* ui_slider_time_border_thickness(ui_slider_time_t* slider_time) { return &slider_time->border_thickness; }
static inline uint32_t* ui_slider_time_border_color(ui_slider_time_t* slider_time) { return &slider_time->border_color; }

// Background:
static inline uint32_t* ui_slider_time_background_color(ui_slider_time_t* slider_time) { return &slider_time->background_color; }

// Focus:
static inline uint32_t* ui_slider_time_focus_border_color(ui_slider_time_t* slider_time) { return &slider_time->focus_border_color; }
static inline uint32_t* ui_slider_time_focus_background_color(ui_slider_time_t* slider_time) { return &slider_time->focus_background_color; }

// Values range:
static inline int16_t* ui_slider_time_min(ui_slider_time_t* slider_time) { return &slider_time->min; }
static inline int16_t* ui_slider_time_max(ui_slider_time_t* slider_time) { return &slider_time->max; }
static inline int16_t* ui_slider_time_value(ui_slider_time_t* slider_time) { return &slider_time->value; }
static inline int16_t* ui_slider_time_step(ui_slider_time_t* slider_time) { return &slider_time->step; }

/**
 * @brief    Automatically set slider_time value to the midpoint, aligned to step.
 *
 * @details  Computes the midpoint between min and max, then rounds it down
 *           to the nearest step. Useful for initializing the slider to a
 *           meaningful default time.
 *
 * @param    slider_time Pointer to the slider_time instance.
 */
static inline void ui_slider_time_auto_set_value(ui_slider_time_t* slider_time) {
	int mid = (slider_time->max + slider_time->min) / 2;
	int step = slider_time->step;

    // rounding down to the nearest step:
	int aligned = ((mid + (step/2 - 1)) / step) * step;
	slider_time->value = aligned;
}



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_slider_time_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a slider_time instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a slider_time.
 */
#define SLIDER_TIME(widget) ((ui_slider_time_t*)(widget))


// Base widget:
#define slider_time_x(slider_time)                      (*ui_slider_time_x(slider_time))
#define slider_time_y(slider_time)                      (*ui_slider_time_y(slider_time))
#define slider_time_width(slider_time)                  (*ui_slider_time_width(slider_time))
#define slider_time_height(slider_time)                 (*ui_slider_time_height(slider_time))
#define slider_time_focusable(slider_time)              (*ui_slider_time_focusable(slider_time))

// Label:
#define slider_time_label_font(slider_time)             (*ui_slider_time_label_font(slider_time))
#define slider_time_label_font_color(slider_time)       (*ui_slider_time_label_font_color(slider_time))

// Handle:
#define slider_time_handle_width(slider_time)           (*ui_slider_time_handle_width(slider_time))
#define slider_time_handle_color(slider_time)           (*ui_slider_time_handle_color(slider_time))

// Border:
#define slider_time_border_thickness(slider_time)       (*ui_slider_time_border_thickness(slider_time))
#define slider_time_border_color(slider_time)           (*ui_slider_time_border_color(slider_time))

// Background:
#define slider_time_background_color(slider_time)       (*ui_slider_time_background_color(slider_time))

// Focus:
#define slider_time_focus_border_color(slider_time)     (*ui_slider_time_focus_border_color(slider_time))
#define slider_time_focus_background_color(slider_time) (*ui_slider_time_focus_background_color(slider_time))

// Values range:
#define slider_time_min(slider_time)                    (*ui_slider_time_min(slider_time))
#define slider_time_max(slider_time)                    (*ui_slider_time_max(slider_time))
#define slider_time_value(slider_time)                  (*ui_slider_time_value(slider_time))
#define slider_time_step(slider_time)                   (*ui_slider_time_step(slider_time))

#define slider_time_auto_set_value(slider_time)         (ui_slider_time_auto_set_value(slider_time))

#endif /* UI_slider_time_TIME_H */