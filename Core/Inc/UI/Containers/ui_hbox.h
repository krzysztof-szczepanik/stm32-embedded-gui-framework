/**
 ******************************************************************************
 * @file     ui_hbox.h
 * @brief    Horizontal box layout widget for arranging child widgets in a row.
 *
 * @details  HBox is a layout container that arranges its child widgets
 *           horizontally. It extends the base container and adds:
 *           - horizontal and vertical alignment
 *           - widget stretching modes
 *           - configurable spacing between widgets
 *
 *           Hbox does not manage focus on its own; instead, it relies on
 *           container focus navigation and only overrides directional
 *           behavior to match horizontal layout semantics.
 *
 *           All child widgets are positioned inside the container's inner
 *           area, respecting padding and border thickness inherited from
 *           ui_container_t.
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

#ifndef UI_HBOX_H
#define UI_HBOX_H

#include "ui_container.h"
#include "ui_align.h"
#include "ui_stretch.h"



// ====================== TYPES ======================

/**
 * @brief    Horizontal box layout container.
 *
 * @details  Hbox arranges child widgets in a horizontal sequence. It supports
 *           stretching modes, alignment options, and spacing between widgets.
 *           Layout is recalculated automatically whenever widgets are added or
 *           when the container is resized.
 */
typedef struct {
	// Base widget:
    ui_container_t base;            /**< Base container used as the underlying widget. */

    // Widgets stretching:
    ui_stretch_t stretch;           /**< Stretch mode applied to child widgets. */

    // Alignment:
    ui_align_x_t align_horizontal;  /**< Horizontal alignment of child widgets inside the inner area. */
    ui_align_y_t align_vertical;    /**< Vertical alignment of child widgets inside the inner area. */

    // Spacing between widgets:
    uint16_t spacing;               /**< Spacing between child widgets. */
} ui_hbox_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initializes a horizontal box layout widget.
 *
 * @details  This function initializes the underlying container, assigns
 *           virtual methods specific to hbox, and sets default values for:
 *           - stretch mode (UI_STRETCH_BOTH)
 *           - horizontal alignment (UI_ALIGN_LEFT)
 *           - vertical alignment (UI_ALIGN_TOP)
 *           - spacing (0)
 *
 * @param    hbox   Pointer to the hbox instance.
 * @param    x      X position of the hbox.
 * @param    y      Y position of the hbox.
 * @param    width  Width of the hbox.
 * @param    height Height of the hbox.
 */
void ui_hbox_init(ui_hbox_t* hbox, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ==================== FUNCTIONS ====================

/**
 * @brief    Adds a single widget to the hbox.
 *
 * @details  This function forwards the call to @ref ui_container_add_widget().
 *
 * @param    hbox   Pointer to the hbox.
 * @param    widget Pointer to the widget to add.
 */
void ui_hbox_add_widget(ui_hbox_t* hbox, ui_widget_t* widget);

/**
 * @brief    Adds multiple widgets to the hbox.
 *
 * @details  This function forwards the call to @ref ui_container_add_widgets().
 *
 * @param    hbox    Pointer to the hbox.
 * @param    widgets Array of widget pointers.
 * @param    count   Number of widgets in the array.
 */
void ui_hbox_add_widgets(ui_hbox_t* hbox, ui_widget_t** widgets, uint8_t count);



// ================= FOCUS FUNCTIONS ==================

/**
 * @brief    Moves focus to the next focusable child widget.
 *
 * @details  Wraps around when reaching the end of the widget list.
 *
 * @param    hbox Pointer to the hbox.
 * @return   true if focus moved inside the hbox, false otherwise.
 */
bool ui_hbox_focus_next(ui_hbox_t* hbox);

/**
 * @brief    Moves focus to the previous focusable child widget.
 *
 * @details  Wraps around when reaching the beginning of the widget list.
 *
 * @param    hbox Pointer to the hbox.
 * @return   true if focus moved inside the hbox, false otherwise.
 */
bool ui_hbox_focus_previous(ui_hbox_t* hbox);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draws the hbox and its child widgets.
 *
 * @details  This function first draws the container's background and
 *           border using @ref ui_container_draw_background(), then iterates
 *           through all child widgets and calls their draw() functions in
 *           order.
 * 
 * @param    widget Pointer to the hbox widget.
 */
void ui_hbox_draw(ui_widget_t* widget);

/**
 * @brief    Updates the layout of the hbox and its children.
 *
 * @details  Computes global render coordinates based on parent position,
 *           border thickness, and padding. Child widgets receive updated
 *           render positions and recursively update their own layout.
 *
 *           Additionally, hbox applies stretching, alignment, and spacing
 *           rules to its child widgets.
 *
 * @param    widget Pointer to the hbox widget.
 */
void ui_hbox_update_layout(ui_widget_t* widget);

/**
 * @brief    Called when the hbox receives focus.
 *
 * @details  Focus is transferred to the first or last child widget
 *           depending on the direction of navigation stored in the global
 *           direction module.
 *
 * @param    widget Pointer to the hbox widget.
 */
void ui_hbox_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the hbox loses focus.
 *
 * @details  The currently focused child widget is blurred and the
 *           container's internal focus state is reset.
 *
 * @param    widget Pointer to the hbox widget.
 */
void ui_hbox_on_blur(ui_widget_t* widget);

/**
 * @brief    Handles UI events for the hbox.
 *
 * @details  LEFT and RIGHT events move focus horizontally. Other events are
 *           forwarded to the focused child widget.
 *
 * @param    widget Pointer to the hbox widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_hbox_on_event(ui_widget_t* widget, ui_event_t event);

/**
 * @brief    Retrieves the list of child widgets stored in the hbox.
 *
 * @details  Forwards the call to @ref ui_container_get_widgets().
 *
 * @param    widget      Pointer to the hbox widget.
 * @param    out_widgets Output array for child widget pointers.
 * @return   Number of child widgets.
 */
uint8_t ui_hbox_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_hbox_x(ui_hbox_t* hbox) { return &hbox->base.base.x; }
static inline int16_t* ui_hbox_y(ui_hbox_t* hbox) { return &hbox->base.base.y; }
static inline uint16_t* ui_hbox_width(ui_hbox_t* hbox) { return &hbox->base.base.width; }
static inline uint16_t* ui_hbox_height(ui_hbox_t* hbox) { return &hbox->base.base.height; }
static inline bool* ui_hbox_focusable(ui_hbox_t* hbox) { return &hbox->base.base.focusable; }
static inline ui_widget_t** ui_hbox_parent(ui_hbox_t* hbox) { return &hbox->base.base.parent; }
static inline uint8_t* ui_hbox_border_thickness(ui_hbox_t* hbox) { return &hbox->base.border_thickness; }
static inline uint32_t* ui_hbox_border_color(ui_hbox_t* hbox) { return &hbox->base.border_color; }
static inline uint32_t* ui_hbox_background_color(ui_hbox_t* hbox) { return &hbox->base.background_color; }
static inline uint8_t* ui_hbox_padding_left(ui_hbox_t* hbox) { return &hbox->base.padding_left; }
static inline uint8_t* ui_hbox_padding_right(ui_hbox_t* hbox) { return &hbox->base.padding_right; }
static inline uint8_t* ui_hbox_padding_top(ui_hbox_t* hbox) { return &hbox->base.padding_top; }
static inline uint8_t* ui_hbox_padding_bottom(ui_hbox_t* hbox) { return &hbox->base.padding_bottom; }

// Widgets stretching:
static inline ui_stretch_t* ui_hbox_stretch(ui_hbox_t* hbox) { return &hbox->stretch; }

// Alignment:
static inline ui_align_x_t* ui_hbox_align_horizontal(ui_hbox_t* hbox) { return &hbox->align_horizontal; }
static inline ui_align_y_t* ui_hbox_align_vertical(ui_hbox_t* hbox) { return &hbox->align_vertical; }

// Spacing between widgets:
static inline uint16_t* ui_hbox_spacing(ui_hbox_t* hbox) { return &hbox->spacing; }



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_hbox_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to an hbox instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a hbox.
 */
#define HBOX(widget) ((ui_hbox_t*)(widget))


// Base widget:
#define hbox_x(hbox)                (*ui_hbox_x(hbox))
#define hbox_y(hbox)                (*ui_hbox_y(hbox))
#define hbox_width(hbox)            (*ui_hbox_width(hbox))
#define hbox_height(hbox)           (*ui_hbox_height(hbox))
#define hbox_focusable(hbox)        (*ui_hbox_focusable(hbox))
#define hbox_parent(hbox)           (*ui_hbox_parent(hbox))

#define hbox_border_thickness(hbox) (*ui_hbox_border_thickness(hbox))
#define hbox_border_color(hbox)     (*ui_hbox_border_color(hbox))
#define hbox_background_color(hbox) (*ui_hbox_background_color(hbox))
#define hbox_padding_left(hbox)     (*ui_hbox_padding_left(hbox))
#define hbox_padding_right(hbox)    (*ui_hbox_padding_right(hbox))
#define hbox_padding_top(hbox)      (*ui_hbox_padding_top(hbox))
#define hbox_padding_bottom(hbox)   (*ui_hbox_padding_bottom(hbox))

// Widgets stretching:
#define hbox_stretch(hbox)          (*ui_hbox_stretch(hbox))

// Alignment:
#define hbox_align_horizontal(hbox) (*ui_hbox_align_horizontal(hbox))
#define hbox_align_vertical(hbox)   (*ui_hbox_align_vertical(hbox))

// Spacing between widgets:
#define hbox_spacing(hbox)          (*ui_hbox_spacing(hbox))

#endif /* UI_HBOX_H */