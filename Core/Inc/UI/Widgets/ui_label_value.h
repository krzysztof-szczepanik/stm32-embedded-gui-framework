/**
 ******************************************************************************
 * @file     ui_label_value.h
 * @brief    Key–value label widget (left text + right value).
 *
 * @details  This widget displays a pair of text labels arranged horizontally:
 *           a left label (key) and a right label (value), separated by a
 *           vertical separator. It is useful for presenting information in
 *           a structured “Label: Value” format (e.g. “Temperature: 21°C”).
 *
 *           The widget is non-interactive and does not handle events.
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

#ifndef UI_LABEL_VALUE_H
#define UI_LABEL_VALUE_H

#include <stdint.h>
#include "ui_widget.h"
#include "ui_label.h"
#include "stm32f429i_discovery_lcd.h"



// ====================== TYPES ======================

/**
 * @brief    Label_value widget (key–value widget).
 *
 * @details  A label_value widget contains two internal labels:
 *           - left_label  - descriptive text (key)
 *           - right_label - displayed value
 *
 *           A vertical separator visually divides the two areas. The
 *           label_value widget supports border, background, padding, and
 *           focus styling.
 */
typedef struct {
	// Base widget:
    ui_widget_t base;                 /**< Base widget. */

    // Border:
    uint8_t border_thickness;         /**< Border thickness. */
    uint32_t border_color;            /**< Border color. */

    // Background:
    uint32_t background_color;        /**< Background color. */

	// Separator:
	uint16_t separator_x_offset;      /**< X offset of the vertical separator. */

	// Left label:
	ui_label_t left_label;            /**< Left-side descriptive label. */
	uint8_t left_label_padding;       /**< Padding around the left label. */

	// Right label:
	ui_label_t right_label;           /**< Right-side value label. */
	uint8_t right_label_padding;      /**< Padding around the right label. */

    // Focus:
	uint32_t focus_background_color;  /**< Border color when focused. */
	uint32_t focus_border_color;      /**< Background color when focused. */
} ui_label_value_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initialize a label_value widget (key–value widget).
 *
 * @details  Sets geometry, assigns virtual functions, initializes default
 *           properties and internal labels.
 *
 *           Most default properties are defined in @ref ui_theme.h.
 *
 * @param    label_value Pointer to the label_value instance.
 * @param    x           X position.
 * @param    y           Y position.
 * @param    width       Label_value width.
 * @param    height      Label_value height.
 */
void ui_label_value_init(ui_label_value_t* label_value, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draw the label_value (key–value widget).
 *
* @param    widget Pointer to the label_value's base widget.
 */
void ui_label_value_draw(ui_widget_t* widget);

/**
 * @brief    Called when the label_value receives focus.
 *
 * @param    widget Pointer to the label_value's base widget.
 */
void ui_label_value_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the label_value loses focus.
 *
 * @param    widget Pointer to the label_value's base widget.
 */
void ui_label_value_on_blur(ui_widget_t* widget);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_label_value_x(ui_label_value_t* label_value) { return &label_value->base.x; }
static inline int16_t* ui_label_value_y(ui_label_value_t* label_value) { return &label_value->base.y; }
static inline uint16_t* ui_label_value_width(ui_label_value_t* label_value) { return &label_value->base.width; }
static inline uint16_t* ui_label_value_height(ui_label_value_t* label_value) { return &label_value->base.height; }
static inline bool* ui_label_value_focusable(ui_label_value_t* label_value) { return &label_value->base.focusable; }

// Border:
static inline uint8_t* ui_label_value_border_thickness(ui_label_value_t* label_value) { return &label_value->border_thickness; }
static inline uint32_t* ui_label_value_border_color(ui_label_value_t* label_value) { return &label_value->border_color; }

// Separator:
static inline uint16_t* ui_label_value_separator_x_offset(ui_label_value_t* label_value) { return &label_value->separator_x_offset; }

// Left label:
static inline ui_label_t* ui_label_value_left_label(ui_label_value_t* label_value) { return &label_value->left_label; }
static inline uint8_t* ui_label_value_left_label_padding(ui_label_value_t* label_value) { return &label_value->left_label_padding; }

// Right label:
static inline ui_label_t* ui_label_value_right_label(ui_label_value_t* label_value) { return &label_value->right_label; }
static inline uint8_t* ui_label_value_right_label_padding(ui_label_value_t* label_value) { return &label_value->right_label_padding; }

// Focus:
static inline uint32_t* ui_label_value_focus_background_color(ui_label_value_t* label_value) { return &label_value->focus_background_color; }
static inline uint32_t* ui_label_value_focus_border_color(ui_label_value_t* label_value) { return &label_value->focus_border_color; }



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_label_value_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a label_value instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a label_value.
 */
#define LABEL_VALUE(widget) ((ui_label_value_t*)(widget))


// Base widget:
#define label_value_x(label_value)                        (*ui_label_value_x(label_value))
#define label_value_y(label_value)                        (*ui_label_value_y(label_value))
#define label_value_width(label_value)                    (*ui_label_value_width(label_value))
#define label_value_height(label_value)                   (*ui_label_value_height(label_value))
#define label_value_focusable(label_value)                (*ui_label_value_focusable(label_value))

// Border:
#define label_value_border_thickness(label_value)         (*ui_label_value_border_thickness(label_value))
#define label_value_border_color(label_value)             (*ui_label_value_border_color(label_value))

// Separator:
#define label_value_separator_x_offset(label_value)       (*ui_label_value_separator_x_offset(label_value))

// Left label:
#define label_value_left_label(label_value)               (*ui_label_value_left_label(label_value))
#define label_value_left_label_padding(label_value)       (*ui_label_value_left_label_padding(label_value))

// Right label:
#define label_value_right_label(label_value)              (*ui_label_value_right_label(label_value))
#define label_value_right_label_padding(label_value)      (*ui_label_value_right_label_padding(label_value))

// Focus:
#define label_value_focus_background_color(label_value)   (*ui_label_value_focus_background_color(label_value))
#define label_value_focus_border_color(label_value)       (*ui_label_value_focus_border_color(label_value))

#endif /* UI_LABEL_VALUE_H */