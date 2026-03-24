/**
 ******************************************************************************
 * @file     ui_label.h
 * @brief    Text label widget with alignment, padding and focus styling.
 *
 * @details  This module defines a non-interactive text label widget used
 *           throughout the UI framework. A label supports:
 *           - static or formatted dynamic text
 *           - customizable border and background
 *           - padding on all sides
 *           - horizontal and vertical alignment
 *           - focus‑specific colors
 *
 *           The label inherits from ui_widget_t and overrides the draw and
 *           focus handlers.
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

#ifndef UI_LABEL_H
#define UI_LABEL_H

#include <stdint.h>
#include <stdbool.h>
#include "ui_align.h"
#include "ui_widget.h"
#include "stm32f429i_discovery_lcd.h"



// ====================== TYPES ======================

/**
 * @brief    Label widget.
 *
 * @details  A label displays text inside a rectangular area. It supports
 *           padding, alignment, dynamic text formatting, and focus‑specific
 *           styling.
 */
typedef struct {
	// Base widget:
	ui_widget_t base;                                   /**< Base widget. */

    // Border:
    uint8_t border_thickness;                           /**< Border thickness. */
    uint32_t border_color;                              /**< Border color. */

    // Background:
    uint32_t background_color;                          /**< Background color. */

	// Label:
    const char* text;     // static text                /**< Static text. */
    char text_buffer[32]; // dynamic text               /**< Dynamic text buffer for formatted text. */
    bool use_text_buffer; // dynamic text - usage flag  /**< Selects between static and dynamic text. */
    sFONT* text_font;                                   /**< Font used for rendering text. */
    uint32_t text_font_color;                           /**< Text color. */

    // Focus:
    uint32_t focus_border_color;                        /**< Border color when focused. */
    uint32_t focus_background_color;                    /**< Background color when focused. */

    // Padding:
    uint8_t padding_left;                               /**< Left padding. */
    uint8_t padding_right;                              /**< Right padding. */
    uint8_t padding_top;                                /**< Top padding. */
    uint8_t padding_bottom;                             /**< Bottom padding. */

    // Alignment:
    ui_align_x_t align_horizontal;                      /**< Horizontal alignment. */
    ui_align_y_t align_vertical;                        /**< Vertical alignment. */
} ui_label_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initialize a label widget.
 *
 * @details  Sets geometry, assigns virtual functions, initializes default
 *           properties.
 * 
 *           Most default properties are defined in @ref ui_theme.h.
 *
 * @param    label  Pointer to the label instance.
 * @param    x      X position.
 * @param    y      Y position.
 * @param    width  Label width.
 * @param    height Label height.
 */
void ui_label_init(ui_label_t* label, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draw the label.
 *
 * @param    widget Pointer to the label's base widget.
 */
void ui_label_draw(ui_widget_t* widget);

/**
 * @brief    Called when the label receives focus.
 *
 * @param    widget Pointer to the label's base widget.
 */
void ui_label_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the label loses focus.
 *
 * @param    widget Pointer to the label's base widget.
 */
void ui_label_on_blur(ui_widget_t* widget);



// ===================== SETTERS =====================

/**
 * @brief    Set label text using printf‑style formatting.
 *
 * @details  Writes formatted text into the internal buffer and enables
 *           dynamic text mode.
 *
 * @param    label  Pointer to the label instance.
 * @param    fmt    Format string.
 * @param    ...    Format arguments.
 *
 * @example
 *     ui_label_t label;
 *     ui_label_init(&label, 10, 10, 100, 20);
 *
 *     // Set dynamic text:
 *     ui_label_text_format(&label, "RPM: %u", 1500);
 *
 *     // Later update:
 *     ui_label_text_format(&label, "Temp: %.1f C", 23.7f);
 *
 *     // The label will automatically use the internal text buffer.
 */
void ui_label_text_format(ui_label_t* label, const char* fmt, ...);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_label_x(ui_label_t* label) { return &label->base.x; }
static inline int16_t* ui_label_y(ui_label_t* label) { return &label->base.y; }
static inline uint16_t* ui_label_width(ui_label_t* label) { return &label->base.width; }
static inline uint16_t* ui_label_height(ui_label_t* label) { return &label->base.height; }
static inline bool* ui_label_focusable(ui_label_t* label) { return &label->base.focusable; }

// Border:
static inline uint8_t* ui_label_border_thickness(ui_label_t* label) { return &label->border_thickness; }
static inline uint32_t* ui_label_border_color(ui_label_t* label) { return &label->border_color; }

// Background:
static inline uint32_t* ui_label_background_color(ui_label_t* label) { return &label->background_color; }

// Label:
static inline const char** ui_label_text(ui_label_t* label) { label->use_text_buffer = false; return &label->text; }
static inline sFONT** ui_label_text_font(ui_label_t* label) { return &label->text_font; }
static inline uint32_t* ui_label_text_font_color(ui_label_t* label) { return &label->text_font_color; }

// Focus:
static inline uint32_t* ui_label_focus_border_color(ui_label_t* label) { return &label->focus_border_color; }
static inline uint32_t* ui_label_focus_background_color(ui_label_t* label) { return &label->focus_background_color; }

// Padding:
static inline uint8_t* ui_label_padding_left(ui_label_t* label) { return &label->padding_left; }
static inline uint8_t* ui_label_padding_right(ui_label_t* label) { return &label->padding_right; }
static inline uint8_t* ui_label_padding_top(ui_label_t* label) { return &label->padding_top; }
static inline uint8_t* ui_label_padding_bottom(ui_label_t* label) { return &label->padding_bottom; }

// Alignment:
static inline ui_align_x_t* ui_label_align_horizontal(ui_label_t* label) { return &label->align_horizontal; }
static inline ui_align_y_t* ui_label_align_vertical(ui_label_t* label) { return &label->align_vertical; }



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_label_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a label instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a label.
 */
#define LABEL(widget) ((ui_label_t*)(widget))


// Base widget:
#define label_x(label)                      (*ui_label_x(label))
#define label_y(label)                      (*ui_label_y(label))
#define label_width(label)                  (*ui_label_width(label))
#define label_height(label)                 (*ui_label_height(label))
#define label_focusable(label)              (*ui_label_focusable(label))

// Border:
#define label_border_thickness(label)       (*ui_label_border_thickness(label))
#define label_border_color(label)           (*ui_label_border_color(label))

// Background:
#define label_background_color(label)       (*ui_label_background_color(label))

// Label:
#define label_text(label)                   (*ui_label_text(label))
#define label_text_format(label, fmt, ...)  (ui_label_text_format((label), (fmt), ##__VA_ARGS__))
#define label_text_font(label)              (*ui_label_text_font(label))
#define label_text_font_color(label)        (*ui_label_text_font_color(label))

// Focus:
#define label_focus_border_color(label)     (*ui_label_focus_border_color(label))
#define label_focus_background_color(label) (*ui_label_focus_background_color(label))

// Padding:
#define label_padding_left(label)           (*ui_label_padding_left(label))
#define label_padding_right(label)          (*ui_label_padding_right(label))
#define label_padding_top(label)            (*ui_label_padding_top(label))
#define label_padding_bottom(label)         (*ui_label_padding_bottom(label))

// Alignment:
#define label_align_horizontal(label)       (*ui_label_align_horizontal(label))
#define label_align_vertical(label)         (*ui_label_align_vertical(label))

#endif /* UI_LABEL_H */