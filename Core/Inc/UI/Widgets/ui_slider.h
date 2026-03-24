/**
 ******************************************************************************
 * @file     ui_slider.h
 * @brief    Horizontal slider widget with value display.
 *
 * @details  This widget represents a horizontal slider with:
 *           - a draggable handle
 *           - a numeric value displayed as a centered label
 *           - configurable range (min, max, step)
 *           - optional suffix (e.g. "%", "°C")
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

#ifndef UI_SLIDER_H
#define UI_SLIDER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "ui_widget.h"
#include "stm32f429i_discovery_lcd.h"



// ====================== TYPES ======================

/**
 * @brief    Horizontal slider widget.
 *
 * @details  The slider displays a numeric value and allows adjusting it
 *           within a defined range using left/right events. The handle
 *           position is computed proportionally to the current value.
 *
 *           The widget supports custom fonts, colors, suffix text,
 *           and focus‑specific styling.
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

    const char* suffix;               /**< Optional suffix appended to the value. */
} ui_slider_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initialize a slider widget.
 *
 * @details  Sets geometry, assigns virtual functions, initializes default
 *           properties.
 *
 *           Most default properties are defined in @ref ui_theme.h.
 *
 * @param    slider Pointer to the slider instance.
 * @param    x      X position.
 * @param    y      Y position.
 * @param    width  Slider width.
 * @param    height Slider height.
 */
void ui_slider_init(ui_slider_t* slider, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draw the slider.
 *
 * @param    widget Pointer to the slider's base widget.
 */
void ui_slider_draw(ui_widget_t* widget);

/**
 * @brief    Called when the slider receives focus.
 *
 * @param    widget Pointer to the slider's base widget.
 */
void ui_slider_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the slider loses focus.
 *
 * @param    widget Pointer to the slider's base widget.
 */
void ui_slider_on_blur(ui_widget_t* widget);

/**
 * @brief    Handle UI events for the slider.
 *
 * @details  UI_EVENT_LEFT  decreases the value by step.
 *           UI_EVENT_RIGHT increases the value by step.
 *           The value is clamped to the <min, max> range.
 *
 * @param    widget Pointer to the slider's base widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_slider_on_event(ui_widget_t* widget, ui_event_t event);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_slider_x(ui_slider_t* slider) { return &slider->base.x; }
static inline int16_t* ui_slider_y(ui_slider_t* slider) { return &slider->base.y; }
static inline uint16_t* ui_slider_width(ui_slider_t* slider) { return &slider->base.width; }
static inline uint16_t* ui_slider_height(ui_slider_t* slider) { return &slider->base.height; }
static inline bool* ui_slider_focusable(ui_slider_t* slider) { return &slider->base.focusable; }

// Label:
static inline sFONT** ui_slider_label_font(ui_slider_t* slider) { return &slider->label_font; }
static inline uint32_t* ui_slider_label_font_color(ui_slider_t* slider) { return &slider->label_font_color; }

// Handle:
static inline uint16_t* ui_slider_handle_width(ui_slider_t* slider) { return &slider->handle_width; }
static inline uint32_t* ui_slider_handle_color(ui_slider_t* slider) { return &slider->handle_color; }

// Border:
static inline uint8_t* ui_slider_border_thickness(ui_slider_t* slider) { return &slider->border_thickness; }
static inline uint32_t* ui_slider_border_color(ui_slider_t* slider) { return &slider->border_color; }

// Background:
static inline uint32_t* ui_slider_background_color(ui_slider_t* slider) { return &slider->background_color; }

// Focus:
static inline uint32_t* ui_slider_focus_border_color(ui_slider_t* slider) { return &slider->focus_border_color; }
static inline uint32_t* ui_slider_focus_background_color(ui_slider_t* slider) { return &slider->focus_background_color; }

// Values range:
static inline int16_t* ui_slider_min(ui_slider_t* slider) { return &slider->min; }
static inline int16_t* ui_slider_max(ui_slider_t* slider) { return &slider->max; }
static inline int16_t* ui_slider_value(ui_slider_t* slider) { return &slider->value; }
static inline int16_t* ui_slider_step(ui_slider_t* slider) { return &slider->step; }
static inline const char** ui_slider_suffix(ui_slider_t* slider) { return &slider->suffix; }

/**
 * @brief    Automatically set slider value to the midpoint, aligned to step.
 *
 * @details  Computes the midpoint between min and max, then rounds it down
 *           to the nearest step. Useful for initializing the slider to a
 *           meaningful default time.
 *
 * @param    slider Pointer to the slider instance.
 */
static inline void ui_slider_auto_set_value(ui_slider_t* slider) {
	int mid = (slider->max + slider->min) / 2;
	int step = slider->step;

    // rounding down to the nearest step:
	int aligned = ((mid + (step/2 - 1)) / step) * step;
	slider->value = aligned;
}



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_slider_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a slider instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a slider.
 */
#define SLIDER(widget) ((ui_slider_t*)(widget))


// Base widget:
#define slider_x(slider)                      (*ui_slider_x(slider))
#define slider_y(slider)                      (*ui_slider_y(slider))
#define slider_width(slider)                  (*ui_slider_width(slider))
#define slider_height(slider)                 (*ui_slider_height(slider))
#define slider_focusable(slider)              (*ui_slider_focusable(slider))

// Label:
#define slider_label_font(slider)             (*ui_slider_label_font(slider))
#define slider_label_font_color(slider)       (*ui_slider_label_font_color(slider))

// Handle:
#define slider_handle_width(slider)           (*ui_slider_handle_width(slider))
#define slider_handle_color(slider)           (*ui_slider_handle_color(slider))

// Border:
#define slider_border_thickness(slider)       (*ui_slider_border_thickness(slider))
#define slider_border_color(slider)           (*ui_slider_border_color(slider))

// Background:
#define slider_background_color(slider)       (*ui_slider_background_color(slider))

// Focus:
#define slider_focus_border_color(slider)     (*ui_slider_focus_border_color(slider))
#define slider_focus_background_color(slider) (*ui_slider_focus_background_color(slider))

// Values range:
#define slider_min(slider)                    (*ui_slider_min(slider))
#define slider_max(slider)                    (*ui_slider_max(slider))
#define slider_value(slider)                  (*ui_slider_value(slider))
#define slider_step(slider)                   (*ui_slider_step(slider))

#define slider_suffix(slider)                 (*ui_slider_suffix(slider))

#define slider_auto_set_value(slider)         (ui_slider_auto_set_value(slider))

#endif /* UI_SLIDER_H */