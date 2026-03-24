/**
 ******************************************************************************
 * @file     ui_progress_bar.h
 * @brief    Horizontal progress bar widget with value label.
 *
 * @details  This widget displays a progress bar whose filled portion reflects
 *           the current value within a defined range. A centered label shows
 *           the numeric value along with an optional suffix (e.g. "%").
 *
 *           The widget supports:
 *           - configurable range (min, max, step)
 *           - a colored bar representing progress
 *           - a formatted label
 *           - focus‑dependent styling for border and background
 *
 *           Unlike a slider, the progress bar is typically non-interactive,
 *           but it may still respond to LEFT/RIGHT events if desired.
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

#ifndef UI_PROGRESS_BAR_H
#define UI_PROGRESS_BAR_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "ui_widget.h"
#include "stm32f429i_discovery_lcd.h"



// ====================== TYPES ======================

/**
 * @brief    Horizontal progress bar widget.
 *
 * @details  The widget displays a filled bar proportional to the current
 *           value. A label centered inside the widget shows the numeric
 *           value and optional suffix.
 */
typedef struct {
	// Base widget:
	ui_widget_t base;                 /**< Base widget. */

	// Label:
    char label[32];                   /**< Buffer for formatted value text. */
    sFONT* label_font;                /**< Font used for the value label. */
    uint32_t label_font_color;        /**< Color of the value label. */

    // Bar:
	uint32_t bar_color;              /**< Color of the filled portion of the progress bar. */

    // Border:
    uint8_t border_thickness;         /**< Border thickness. */
    uint32_t border_color;            /**< Border color. */

    // Background:
    uint32_t background_color;        /**< Background color. */

    // Focus:
    uint32_t focus_border_color;      /**< Border color when focused. */
    uint32_t focus_background_color;  /**< Background color when focused. */

    // Values range:
    int16_t min;                      /**< Minimum slider value. */
    int16_t max;                      /**< Maximum slider value. */
    int16_t value;                    /**< Current slider value. */
    int16_t step;                     /**< Step size for each left/right event. */

    const char* suffix;              /**< Optional suffix appended to the value. */
} ui_progress_bar_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initialize a progress_bar widget.
 *
 * @details  Sets geometry, assigns virtual functions, initializes default
 *           properties.
 *
 *           Most default properties are defined in @ref ui_theme.h.
 *
 * @param    progress_bar Pointer to the progress bar instance.
 * @param    x            X position.
 * @param    y            Y position.
 * @param    width        Progress_bar width.
 * @param    height       Progress_bar height.
 */
void ui_progress_bar_init(ui_progress_bar_t* progress_bar, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draw the progress_bar.
 *
 * @param    widget Pointer to the progress_bar's base widget.
 */
void ui_progress_bar_draw(ui_widget_t* widget);

/**
 * @brief    Called when the progress_bar receives focus.
 *
 * @param    widget Pointer to the progress_bar's base widget.
 */
void ui_progress_bar_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the progress_bar loses focus.
 *
 * @param    widget Pointer to the progress_bar's base widget.
 */
void ui_progress_bar_on_blur(ui_widget_t* widget);

/**
 * @brief    Handle UI events for the progress_bar.
 *
 * @details  UI_EVENT_LEFT  decreases the value by step.  
 *           UI_EVENT_RIGHT increases the value by step.  
 *           The value is clamped to the <min, max> range.
 *
 * @param    widget Pointer to the progress_bar's base widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_progress_bar_on_event(ui_widget_t* widget, ui_event_t event);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_progress_bar_x(ui_progress_bar_t* progress_bar) { return &progress_bar->base.x; }
static inline int16_t* ui_progress_bar_y(ui_progress_bar_t* progress_bar) { return &progress_bar->base.y; }
static inline uint16_t* ui_progress_bar_width(ui_progress_bar_t* progress_bar) { return &progress_bar->base.width; }
static inline uint16_t* ui_progress_bar_height(ui_progress_bar_t* progress_bar) { return &progress_bar->base.height; }
static inline bool* ui_progress_bar_focusable(ui_progress_bar_t* progress_bar) { return &progress_bar->base.focusable; }

// Label:
static inline sFONT** ui_progress_bar_label_font(ui_progress_bar_t* progress_bar) { return &progress_bar->label_font; }
static inline uint32_t* ui_progress_bar_label_font_color(ui_progress_bar_t* progress_bar) { return &progress_bar->label_font_color; }

// Bar:
static inline uint32_t* ui_progress_bar_bar_color(ui_progress_bar_t* progress_bar) { return &progress_bar->bar_color; }

// Border:
static inline uint8_t* ui_progress_bar_border_thickness(ui_progress_bar_t* progress_bar) { return &progress_bar->border_thickness; }
static inline uint32_t* ui_progress_bar_border_color(ui_progress_bar_t* progress_bar) { return &progress_bar->border_color; }

// Background:
static inline uint32_t* ui_progress_bar_background_color(ui_progress_bar_t* progress_bar) { return &progress_bar->background_color; }

// Focus:
static inline uint32_t* ui_progress_bar_focus_border_color(ui_progress_bar_t* progress_bar) { return &progress_bar->focus_border_color; }
static inline uint32_t* ui_progress_bar_focus_background_color(ui_progress_bar_t* progress_bar) { return &progress_bar->focus_background_color; }

// Values range:
static inline int16_t* ui_progress_bar_min(ui_progress_bar_t* progress_bar) { return &progress_bar->min; }
static inline int16_t* ui_progress_bar_max(ui_progress_bar_t* progress_bar) { return &progress_bar->max; }
static inline int16_t* ui_progress_bar_value(ui_progress_bar_t* progress_bar) { return &progress_bar->value; }
static inline int16_t* ui_progress_bar_step(ui_progress_bar_t* progress_bar) { return &progress_bar->step; }

static inline const char** ui_progress_bar_suffix(ui_progress_bar_t* progress_bar) { return &progress_bar->suffix; }

/**
 * @brief    Set progress_bar value with clamping to <min, max>.
 *
 * @details  Updates the value and marks the widget as invalidated so that
 *           it will be redrawn on the next frame.
 *
 * @param    progress_bar Pointer to the progress_bar instance.
 * @param    value        New value to assign.
 */
static inline void ui_progress_bar_set_value(ui_progress_bar_t* progress_bar, int16_t value) {
	if (value < progress_bar->min) { value = progress_bar->min; }
	if (value > progress_bar->max) { value = progress_bar->max; }

	progress_bar->value = value;
	progress_bar->base.invalidated = true;
}



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_progress_bar_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a progress_bar instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a progress_bar.
 */
#define PROGRESS_BAR(widget) ((ui_progress_bar_t*)(widget))


// Base widget:
#define progress_bar_x(progress_bar)                      (*ui_progress_bar_x(progress_bar))
#define progress_bar_y(progress_bar)                      (*ui_progress_bar_y(progress_bar))
#define progress_bar_width(progress_bar)                  (*ui_progress_bar_width(progress_bar))
#define progress_bar_height(progress_bar)                 (*ui_progress_bar_height(progress_bar))
#define progress_bar_focusable(progress_bar)              (*ui_progress_bar_focusable(progress_bar))

// Label:
#define progress_bar_label_font(progress_bar)             (*ui_progress_bar_label_font(progress_bar))
#define progress_bar_label_font_color(progress_bar)       (*ui_progress_bar_label_font_color(progress_bar))

// Bar:
#define progress_bar_bar_color(progress_bar)              (*ui_progress_bar_bar_color(progress_bar))

// Border:
#define progress_bar_border_thickness(progress_bar)       (*ui_progress_bar_border_thickness(progress_bar))
#define progress_bar_border_color(progress_bar)           (*ui_progress_bar_border_color(progress_bar))

// Background:
#define progress_bar_background_color(progress_bar)       (*ui_progress_bar_background_color(progress_bar))

// Focus:
#define progress_bar_focus_border_color(progress_bar)     (*ui_progress_bar_focus_border_color(progress_bar))
#define progress_bar_focus_background_color(progress_bar) (*ui_progress_bar_focus_background_color(progress_bar))

// Values range:
#define progress_bar_min(progress_bar)                    (*ui_progress_bar_min(progress_bar))
#define progress_bar_max(progress_bar)                    (*ui_progress_bar_max(progress_bar))
#define progress_bar_value(progress_bar)                  (*ui_progress_bar_value(progress_bar))
#define progress_bar_step(progress_bar)                   (*ui_progress_bar_step(progress_bar))

#define progress_bar_suffix(progress_bar)                 (*ui_progress_bar_suffix(progress_bar))

#define progress_bar_set_value(progress_bar, value)       (ui_progress_bar_set_value(progress_bar, value))

#endif /* UI_PROGRESS_BAR_H */