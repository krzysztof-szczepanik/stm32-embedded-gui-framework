/**
 ******************************************************************************
 * @file     ui_toggle.h
 * @brief    Two‑state toggle widget (left/right switch).
 *
 * @details  This widget displays two selectable areas (left and right),
 *           separated by a vertical divider. Each area contains a label
 *           and can be highlighted depending on the selected state.
 *
 *           The widget is interactive: pressing SELECT switches between
 *           the left and right side.
 *
 *           It is useful for binary settings such as ON/OFF, YES/NO,
 *           ENABLE/DISABLE, etc.
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

#ifndef UI_TOGGLE_H
#define UI_TOGGLE_H

#include <stdint.h>
#include <stdbool.h>
#include "ui_widget.h"
#include "stm32f429i_discovery_lcd.h"



// ====================== TYPES ======================

/**
 * @brief  Toggle side selection.
 */
typedef enum {
    UI_TOGGLE_LEFT,  /**< Left side selected. */
    UI_TOGGLE_RIGHT  /**< Right side selected. */
} ui_toggle_side_t;

/**
 * @brief    Two‑state toggle widget.
 *
 * @details  The widget contains:
 *           - a left area with label
 *           - a right area with label
 *           - a separator between them
 *           - a selected state indicating which side is active
 *
 *           Focus styling affects border, background, and selected color.
 */
typedef struct {
	// Base widget:
	ui_widget_t base;                      /**< Base widget. */

    // Border:
    uint8_t border_thickness;              /**< Border thickness. */
    uint32_t border_color;                 /**< Border color. */

    // Background:
    uint32_t background_color;             /**< Background color. */

	// Left area:
	const char* left_area_label;           /**< Text for the left side. */
	sFONT* left_area_label_font;           /**< Font for the left label. */
	uint32_t left_area_label_font_color;   /**< Left label color. */

    // Right area:
	const char* right_area_label;          /**< Text for the right side. */
	sFONT* right_area_label_font;          /**< Font for the right label. */
	uint32_t right_area_label_font_color;  /**< Right label color. */

    // Selected area:
	ui_toggle_side_t selected;             /**< Currently selected side. */
	uint32_t selected_color;               /**< Background color of selected side. */

    // Focus:
    uint32_t focus_border_color;           /**< Border color when focused. */
    uint32_t focus_background_color;       /**< Background color when focused. */
    uint32_t focus_selected_color;         /**< Selected area color when focused. */
} ui_toggle_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initialize a toggle widget.
 *
 * @details  Sets geometry, assigns virtual functions, initializes default
 *           properties and labels.
 *
 *           Most default properties are defined in @ref ui_theme.h.
 *
 * @param    toggle Pointer to the toggle instance.
 * @param    x      X position.
 * @param    y      Y position.
 * @param    width  Toggle width.
 * @param    height Toggle height.
 */
void ui_toggle_init(ui_toggle_t* toggle, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draw the toggle.
 *
 * @param    widget Pointer to the toggle's base widget.
 */
void ui_toggle_draw(ui_widget_t* widget);

/**
 * @brief    Called when the toggle receives focus.
 *
 * @param    widget Pointer to the toggle's base widget.
 */
void ui_toggle_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the toggle loses focus.
 *
 * @param    widget Pointer to the toggle's base widget.
 */
void ui_toggle_on_blur(ui_widget_t* widget);

/**
 * @brief    Handle UI events for the toggle.
 *
 * @details  UI_EVENT_SELECT switches between left and right side.
 *
 * @param    widget Pointer to the toggle's base widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_toggle_on_event(ui_widget_t* widget, ui_event_t event);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_toggle_x(ui_toggle_t* toggle) { return &toggle->base.x; }
static inline int16_t* ui_toggle_y(ui_toggle_t* toggle) { return &toggle->base.y; }
static inline uint16_t* ui_toggle_width(ui_toggle_t* toggle) { return &toggle->base.width; }
static inline uint16_t* ui_toggle_height(ui_toggle_t* toggle) { return &toggle->base.height; }
static inline bool* ui_toggle_focusable(ui_toggle_t* toggle) { return &toggle->base.focusable; }

// Border:
static inline uint8_t* ui_toggle_border_thickness(ui_toggle_t* toggle) { return &toggle->border_thickness; }
static inline uint32_t* ui_toggle_border_color(ui_toggle_t* toggle) { return &toggle->border_color; }

// Background:
static inline uint32_t* ui_toggle_background_color(ui_toggle_t* toggle) { return &toggle->background_color; }

// Left area:
static inline const char** ui_toggle_left_area_label(ui_toggle_t* toggle) { return &toggle->left_area_label; }
static inline sFONT** ui_toggle_left_area_label_font(ui_toggle_t* toggle) { return &toggle->left_area_label_font; }
static inline uint32_t* ui_toggle_left_area_label_font_color(ui_toggle_t* toggle) { return &toggle->left_area_label_font_color; }

// Right area:
static inline const char** ui_toggle_right_area_label(ui_toggle_t* toggle) { return &toggle->right_area_label; }
static inline sFONT** ui_toggle_right_area_label_font(ui_toggle_t* toggle) { return &toggle->right_area_label_font; }
static inline uint32_t* ui_toggle_right_area_label_font_color(ui_toggle_t* toggle) { return &toggle->right_area_label_font_color; }

// Selected area:
static inline bool ui_toggle_selected(ui_toggle_t* toggle) { return toggle->selected == UI_TOGGLE_RIGHT; }
static inline uint32_t* ui_toggle_selected_color(ui_toggle_t* toggle) { return &toggle->selected_color; }

// Focus:
static inline uint32_t* ui_toggle_focus_border_color(ui_toggle_t* toggle) { return &toggle->focus_border_color; }
static inline uint32_t* ui_toggle_focus_background_color(ui_toggle_t* toggle) { return &toggle->focus_background_color; }
static inline uint32_t* ui_toggle_focus_selected_color(ui_toggle_t* toggle) { return &toggle->focus_selected_color; }



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_toggle_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a toggle instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a toggle.
 */
#define TOGGLE(widget) ((ui_toggle_t*)(widget))


// Base widget:
#define toggle_x(toggle)                           (*ui_toggle_x(toggle))
#define toggle_y(toggle)                           (*ui_toggle_y(toggle))
#define toggle_width(toggle)                       (*ui_toggle_width(toggle))
#define toggle_height(toggle)                      (*ui_toggle_height(toggle))
#define toggle_focusable(toggle)                   (*ui_toggle_focusable(toggle))

// Border:
#define toggle_border_thickness(toggle)            (*ui_toggle_border_thickness(toggle))
#define toggle_border_color(toggle)                (*ui_toggle_border_color(toggle))

// Background:
#define toggle_background_color(toggle)            (*ui_toggle_background_color(toggle))

// Left area:
#define toggle_left_area_label(toggle)             (*ui_toggle_left_area_label(toggle))
#define toggle_left_area_label_font(toggle)        (*ui_toggle_left_area_label_font(toggle))
#define toggle_left_area_label_font_color(toggle)  (*ui_toggle_left_area_label_font_color(toggle))

// Right area:
#define toggle_right_area_label(toggle)            (*ui_toggle_right_area_label(toggle))
#define toggle_right_area_label_font(toggle)       (*ui_toggle_right_area_label_font(toggle))
#define toggle_right_area_label_font_color(toggle) (*ui_toggle_right_area_label_font_color(toggle))

// Selected area:
#define toggle_selected(toggle)                    (ui_toggle_selected(toggle))
#define toggle_selected_color(toggle)              (*ui_toggle_selected_color(toggle))

// Focus:
#define toggle_focus_border_color(toggle)          (*ui_toggle_focus_border_color(toggle))
#define toggle_focus_background_color(toggle)      (*ui_toggle_focus_background_color(toggle))
#define toggle_focus_selected_color(toggle)        (*ui_toggle_focus_selected_color(toggle))

#endif /* UI_TOGGLE_H */