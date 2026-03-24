/**
 ******************************************************************************
 * @file     ui_vbox.h
 * @brief    Vertical box layout widget for arranging child widgets in a
 *           column.
 *
 * @details  Vbox is a layout container that arranges its child widgets
 *           vertically. It extends the base container and adds:
 *           - horizontal and vertical alignment
 *           - widget stretching modes
 *           - configurable spacing between widgets
 *
 *           Unlike hbox, most vbox functions simply forward calls to the
 *           underlying container implementation. Only layout computation
 *           differs, as vbox arranges widgets top‑to‑bottom instead of
 *           left‑to‑right.
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

#ifndef UI_VBOX_H
#define UI_VBOX_H

#include "ui_container.h"
#include "ui_align.h"
#include "ui_stretch.h"



// ====================== TYPES ======================

/**
 * @brief    Vertical box layout container.
 *
 * @details  Vbox arranges child widgets in a vertical sequence. It supports
 *           stretching modes, alignment options, and spacing between widgets.
 *           Layout is recalculated automatically whenever widgets are added or
 *           when the container is resized.
 */
typedef struct {
    // Base widget:
    ui_container_t base;            /**< Base container used as the underlying widget. */

    // Widget stretching:
    ui_stretch_t stretch;           /**< Stretch mode applied to child widgets. */

    // Alignment:
    ui_align_x_t align_horizontal;  /**< Horizontal alignment of child widgets inside the inner area. */
    ui_align_y_t align_vertical;    /**< Vertical alignment of child widgets inside the inner area. */

    // Spacing between widgets:
    uint16_t spacing;               /**< Spacing between child widgets. */
} ui_vbox_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initializes a vertical box layout widget.
 *
 * @details  This function initializes the underlying container, assigns
 *           virtual methods specific to vbox, and sets default values for:
 *           - stretch mode (UI_STRETCH_BOTH)
 *           - horizontal alignment (UI_ALIGN_LEFT)
 *           - vertical alignment (UI_ALIGN_TOP)
 *           - spacing (0)
 *
 * @param    vbox   Pointer to the vbox instance.
 * @param    x      X position of the vbox.
 * @param    y      Y position of the vbox.
 * @param    width  Width of the vbox.
 * @param    height Height of the vbox.
 */
void ui_vbox_init(ui_vbox_t* vbox, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ==================== FUNCTIONS ====================

/**
 * @brief    Adds a single widget to the vbox.
 *
 * @details  This function forwards the call to @ref ui_container_add_widget().
 *
 * @param    vbox   Pointer to the vbox.
 * @param    widget Widget to add.
 */
void ui_vbox_add_widget(ui_vbox_t* vbox, ui_widget_t* widget);

/**
 * @brief    Adds multiple widgets to the vbox.
 *
 * @details  This function forwards the call to @ref ui_container_add_widgets().
 *
 * @param    vbox    Pointer to the vbox.
 * @param    widgets Array of widget pointers.
 * @param    count   Number of widgets in the array.
 */
void ui_vbox_add_widgets(ui_vbox_t* vbox, ui_widget_t** widgets, uint8_t count);



// ================= FOCUS FUNCTIONS ==================

/**
 * @brief    Moves focus to the next focusable child widget.
 *
 * @details  This function forwards the call to @ref ui_container_focus_next().
 *
 * @param    vbox Pointer to the vbox.
 * @return   true if focus moved inside the vbox, false otherwise.
 */
bool ui_vbox_focus_next(ui_vbox_t* vbox);

/**
 * @brief    Moves focus to the previous focusable child widget.
 *
 * @details  This function forwards the call to @ref ui_container_focus_previous().
 *
 * @param    vbox Pointer to the vbox.
 * @return   true if focus moved inside the vbox, false otherwise.
 */
bool ui_vbox_focus_previous(ui_vbox_t* vbox);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draws the vbox and its child widgets.
 *
 * @details  This function first draws the container's background and
 *           border using @ref ui_container_draw_background(), then iterates
 *           through all child widgets and calls their draw() functions in
 *           order.
 *
 * @param    widget Pointer to the vbox widget.
 */
void ui_vbox_draw(ui_widget_t* widget);

/**
 * @brief    Updates the layout of the vbox and its children.
 *
 * @details  Computes global render coordinates based on parent position,
 *           border thickness, and padding. Child widgets receive updated
 *           render positions and recursively update their own layout.
 *
 *           Additionally, vbox applies stretching, alignment, and spacing
 *           rules to its child widgets.
 *
 * @param    widget Pointer to the vbox widget.
 */
void ui_vbox_update_layout(ui_widget_t* widget);

/**
 * @brief    Called when the vbox receives focus.
 *
 * @details  This function forwards the call to @ref ui_container_on_focus().
 *
 * @param    widget Pointer to the vbox widget.
 */
void ui_vbox_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the vbox loses focus.
 *
 * @details  This function forwards the call to @ref ui_container_on_blur().
 *
 * @param    widget Pointer to the vbox widget.
 */
void ui_vbox_on_blur(ui_widget_t* widget);

/**
 * @brief    Handles UI events for the vbox.
 *
 * @details  This function forwards the call to @ref ui_container_on_event().
 * 
 * @param    widget Pointer to the vbox widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_vbox_on_event(ui_widget_t* widget, ui_event_t event);

/**
 * @brief    Retrieves the list of child widgets stored in the vbox.
 *
 * @details  This function forwards the call to @ref ui_container_get_widgets().
 *
 * @param    widget      Pointer to the vbox widget.
 * @param    out_widgets Output array for child widget pointers.
 * @return   Number of child widgets.
 */
uint8_t ui_vbox_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_vbox_x(ui_vbox_t* vbox) { return &vbox->base.base.x; }
static inline int16_t* ui_vbox_y(ui_vbox_t* vbox) { return &vbox->base.base.y; }
static inline uint16_t* ui_vbox_width(ui_vbox_t* vbox) { return &vbox->base.base.width; }
static inline uint16_t* ui_vbox_height(ui_vbox_t* vbox) { return &vbox->base.base.height; }
static inline bool* ui_vbox_focusable(ui_vbox_t* vbox) { return &vbox->base.base.focusable; }
static inline ui_widget_t** ui_vbox_parent(ui_vbox_t* vbox) { return &vbox->base.base.parent; }
static inline uint8_t* ui_vbox_border_thickness(ui_vbox_t* vbox) { return &vbox->base.border_thickness; }
static inline uint32_t* ui_vbox_border_color(ui_vbox_t* vbox) { return &vbox->base.border_color; }
static inline uint32_t* ui_vbox_background_color(ui_vbox_t* vbox) { return &vbox->base.background_color; }
static inline uint8_t* ui_vbox_padding_left(ui_vbox_t* vbox) { return &vbox->base.padding_left; }
static inline uint8_t* ui_vbox_padding_right(ui_vbox_t* vbox) { return &vbox->base.padding_right; }
static inline uint8_t* ui_vbox_padding_top(ui_vbox_t* vbox) { return &vbox->base.padding_top; }
static inline uint8_t* ui_vbox_padding_bottom(ui_vbox_t* vbox) { return &vbox->base.padding_bottom; }

// Widgets stretching:
static inline ui_stretch_t* ui_vbox_stretch(ui_vbox_t* vbox) { return &vbox->stretch; }

// Alignment:
static inline ui_align_x_t* ui_vbox_align_horizontal(ui_vbox_t* vbox) { return &vbox->align_horizontal; }
static inline ui_align_y_t* ui_vbox_align_vertical(ui_vbox_t* vbox) { return &vbox->align_vertical; }

// Spacing between widgets:
static inline uint16_t* ui_vbox_spacing(ui_vbox_t* vbox) { return &vbox->spacing; }



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_vbox_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to an vbox instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a vbox.
 */
#define VBOX(widget) ((ui_vbox_t*)(widget))


// Base widget:
#define vbox_x(vbox)                (*ui_vbox_x(vbox))
#define vbox_y(vbox)                (*ui_vbox_y(vbox))
#define vbox_width(vbox)            (*ui_vbox_width(vbox))
#define vbox_height(vbox)           (*ui_vbox_height(vbox))
#define vbox_focusable(vbox)        (*ui_vbox_focusable(vbox))
#define vbox_parent(vbox)           (*ui_vbox_parent(vbox))

#define vbox_border_thickness(vbox) (*ui_vbox_border_thickness(vbox))
#define vbox_border_color(vbox)     (*ui_vbox_border_color(vbox))
#define vbox_background_color(vbox) (*ui_vbox_background_color(vbox))
#define vbox_padding_left(vbox)     (*ui_vbox_padding_left(vbox))
#define vbox_padding_right(vbox)    (*ui_vbox_padding_right(vbox))
#define vbox_padding_top(vbox)      (*ui_vbox_padding_top(vbox))
#define vbox_padding_bottom(vbox)   (*ui_vbox_padding_bottom(vbox))

// Widgets stretching:
#define vbox_stretch(vbox)          (*ui_vbox_stretch(vbox))

// Alignment:
#define vbox_align_horizontal(vbox) (*ui_vbox_align_horizontal(vbox))
#define vbox_align_vertical(vbox)   (*ui_vbox_align_vertical(vbox))

// Spacing between widgets:
#define vbox_spacing(vbox)          (*ui_vbox_spacing(vbox))

#endif /* UI_VBOX_H */