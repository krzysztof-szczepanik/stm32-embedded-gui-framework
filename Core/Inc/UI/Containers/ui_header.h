/**
 ******************************************************************************
 * @file     ui_header.h
 * @brief    Header section widget used at the top of application screens.
 *
 * @details  The header is a semantic UI component placed at the top of a
 *           screen. It typically contains navigation buttons, titles, icons,
 *           or other controls relevant to the current view.
 * 
 *           Although the header internally uses ui_hbox_t for layout, it is
 *           represented by a dedicated type to:
 *           - improve readability and prevent accidental misuse
 *           - allow future extension of header‑specific behavior
 *           - provide a clear semantic separation between screen sections
 *
 *           The header inherits all behavior from ui_hbox_t, including
 *           stretching, alignment, spacing, and child widget management.
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

#ifndef UI_HEADER_H
#define UI_HEADER_H

#include "ui_hbox.h"



// ====================== TYPES ======================

/**
 * @brief    Header section widget.
 *
 * @details  The header is implemented as a horizontal box (ui_hbox_t) but
 *           wrapped in a dedicated type to allow future customization and
 *           to clearly distinguish it from generic layout containers.
 */
typedef struct {
	// Base widget:
    ui_hbox_t base;  /**< Base container used as the underlying widget. */
} ui_header_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initializes the header widget.
 *
 * @details  The header is positioned at the top of the screen and spans the
 *           full width of the display. Its height is provided by the caller.
 *           
 *           Virtual functions are overridden to allow header‑specific
 *           behavior if needed in the future.
 *
 * @param    header Pointer to the header instance.
 * @param    height Height of the header.
 */
void ui_header_init(ui_header_t* header, uint16_t height);



// ==================== FUNCTIONS ====================

/**
 * @brief    Adds a single widget to the header.
 *
 * @details  This function forwards the call to @ref ui_hbox_add_widget().
 *
 * @param    header Pointer to the header.
 * @param    widget Pointer to the widget to add.
 */
void ui_header_add_widget(ui_header_t* header, ui_widget_t* widget);

/**
 * @brief    Adds multiple widgets to the header.
 *
 * @details  This function forwards the call to @ref ui_hbox_add_widgets().
 *
 * @param    header  Pointer to the header.
 * @param    widgets Array of widget pointers.
 * @param    count   Number of widgets in the array.
 */
void ui_header_add_widgets(ui_header_t* header, ui_widget_t** widgets, uint8_t count);



// ================= FOCUS FUNCTIONS ==================

/**
 * @brief    Moves focus to the next focusable child widget.
 *
 * @details  This function forwards the call to @ref ui_hbox_focus_next().
 *
 * @param    header Pointer to the header.
 * @return   true if focus moved inside the header, false otherwise.
 */
bool ui_header_focus_next(ui_header_t* header);

/**
 * @brief    Moves focus to the previous focusable child widget.
 *
 * @details  This function forwards the call to @ref ui_hbox_focus_previous().
 *
 * @param    header Pointer to the header.
 * @return   true if focus moved inside the header, false otherwise.
 */
bool ui_header_focus_previous(ui_header_t* header);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draws the header and its child widgets.
 *
 * @details  This function forwards the call to @ref ui_hbox_draw().
 *
 * @param    widget Pointer to the header widget.
 */
void ui_header_draw(ui_widget_t* widget);

/**
 * @brief    Updates the layout of the header and its children.
 *
 * @details  This function forwards the call to @ref ui_hbox_update_layout().
 *
 * @param    widget Pointer to the header widget.
 */
void ui_header_update_layout(ui_widget_t* widget);

/**
 * @brief    Called when the header receives focus.
 *
 * @details  This function forwards the call to @ref ui_hbox_on_focus().
 *
 * @param    widget Pointer to the header widget.
 */
void ui_header_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the header loses focus.
 *
 * @details  This function forwards the call to @ref ui_hbox_on_blur().
 *
 * @param    widget Pointer to the header widget.
 */
void ui_header_on_blur(ui_widget_t* widget);

/**
 * @brief    Handles UI events for the header.
 *
 * @details  This function forwards the call to @ref ui_hbox_on_event().
 *
 * @param    widget Pointer to the header widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_header_on_event(ui_widget_t* widget, ui_event_t event);

/**
 * @brief    Retrieves the list of child widgets stored in the header.
 *
 * @details  This function forwards the call to @ref ui_hbox_get_widgets().
 *
 * @param    widget      Pointer to the header widget.
 * @param    out_widgets Output array for child widget pointers.
 * @return   Number of child widgets.
 */
uint8_t ui_header_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_header_x(ui_header_t* header) { return &header->base.base.base.x; }
static inline int16_t* ui_header_y(ui_header_t* header) { return &header->base.base.base.y; }
static inline uint16_t* ui_header_width(ui_header_t* header) { return &header->base.base.base.width; }
static inline uint16_t* ui_header_height(ui_header_t* header) { return &header->base.base.base.height; }
static inline bool* ui_header_focusable(ui_header_t* header) { return &header->base.base.base.focusable; }
static inline ui_widget_t** ui_header_parent(ui_header_t* header) { return &header->base.base.base.parent; }
static inline uint8_t* ui_header_border_thickness(ui_header_t* header) { return &header->base.base.border_thickness; }
static inline uint32_t* ui_header_border_color(ui_header_t* header) { return &header->base.base.border_color; }
static inline uint32_t* ui_header_background_color(ui_header_t* header) { return &header->base.base.background_color; }
static inline uint8_t* ui_header_padding_left(ui_header_t* header) { return &header->base.base.padding_left; }
static inline uint8_t* ui_header_padding_right(ui_header_t* header) { return &header->base.base.padding_right; }
static inline uint8_t* ui_header_padding_top(ui_header_t* header) { return &header->base.base.padding_top; }
static inline uint8_t* ui_header_padding_bottom(ui_header_t* header) { return &header->base.base.padding_bottom; }

// Widgets stretching:
static inline ui_stretch_t* ui_header_stretch(ui_header_t* header) { return &header->base.stretch; }

// Alignment:
static inline ui_align_x_t* ui_header_align_horizontal(ui_header_t* header) { return &header->base.align_horizontal; }
static inline ui_align_y_t* ui_header_align_vertical(ui_header_t* header) { return &header->base.align_vertical; }

// Spacing between widgets:
static inline uint16_t* ui_header_spacing(ui_header_t* header) { return &header->base.spacing; }



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_header_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to an header instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a header.
 */
#define header(widget) ((ui_header_t*)(widget))


// Base widget:
#define header_x(header)                (*ui_header_x(header))
#define header_y(header)                (*ui_header_y(header))
#define header_width(header)            (*ui_header_width(header))
#define header_height(header)           (*ui_header_height(header))
#define header_focusable(header)        (*ui_header_focusable(header))
#define header_parent(header)           (*ui_header_parent(header))

#define header_border_thickness(header) (*ui_header_border_thickness(header))
#define header_border_color(header)     (*ui_header_border_color(header))
#define header_background_color(header) (*ui_header_background_color(header))
#define header_padding_left(header)     (*ui_header_padding_left(header))
#define header_padding_right(header)    (*ui_header_padding_right(header))
#define header_padding_top(header)      (*ui_header_padding_top(header))
#define header_padding_bottom(header)   (*ui_header_padding_bottom(header))

// Widgets stretching:
#define header_stretch(header)          (*ui_header_stretch(header))

// Alignment:
#define header_align_horizontal(header) (*ui_header_align_horizontal(header))
#define header_align_vertical(header)   (*ui_header_align_vertical(header))

// Spacing between widgets:
#define header_spacing(header)          (*ui_header_spacing(header))

#endif /* UI_HEADER_H */