/**
 ******************************************************************************
 * @file     ui_footer.h
 * @brief    Footer section widget used at the bottom of application screens.
 *
 * @details  The footer is a semantic UI component placed at the bottom of a
 *           screen. It typically contains action buttons, status indicators,
 *           or other controls relevant to the current view.
 * 
 *           Although the footer internally uses ui_hbox_t for layout, it is
 *           represented by a dedicated type to:
 *           - improve readability and prevent accidental misuse
 *           - allow future extension of footer‑specific behavior
 *           - provide a clear semantic separation between screen sections
 *
 *           The footer inherits all behavior from ui_hbox_t, including
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

#ifndef UI_FOOTER_H
#define UI_FOOTER_H

#include "ui_hbox.h"



// ====================== TYPES ======================

/**
 * @brief    Footer section widget.
 *
 * @details  The footer is implemented as a horizontal box (ui_hbox_t) but
 *           wrapped in a dedicated type to allow future customization and
 *           to clearly distinguish it from generic layout containers.
 */
typedef struct {
	// Base widget:
    ui_hbox_t base;  /**< Base container used as the underlying widget. */
} ui_footer_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initializes the footer widget.
 *
 * @details  The footer is positioned at the bottom of the screen and spans
 *           the full width of the display. Its height is provided by the
 *           caller.
 *
 *           Virtual functions are overridden to allow footer‑specific
 *           behavior if needed in the future.
 *
 * @param    footer Pointer to the footer instance.
 * @param    height Height of the footer.
 */
void ui_footer_init(ui_footer_t* footer, uint16_t height);



// ==================== FUNCTIONS ====================

/**
 * @brief    Adds a single widget to the footer.
 *
 * @details  This function forwards the call to @ref ui_hbox_add_widget().
 *
 * @param    footer Pointer to the footer.
 * @param    widget Pointer to the widget to add.
 */
void ui_footer_add_widget(ui_footer_t* footer, ui_widget_t* widget);

/**
 * @brief    Adds multiple widgets to the footer.
 *
 * @details  This function forwards the call to @ref ui_hbox_add_widgets().
 *
 * @param    footer  Pointer to the footer.
 * @param    widgets Array of widget pointers.
 * @param    count   Number of widgets in the array.
 */
void ui_footer_add_widgets(ui_footer_t* footer, ui_widget_t** widgets, uint8_t count);



// ================= FOCUS FUNCTIONS ==================

/**
 * @brief    Moves focus to the next focusable child widget.
 *
 * @details  This function forwards the call to @ref ui_hbox_focus_next().
 *
 * @param    footer Pointer to the footer.
 * @return   true if focus moved inside the footer, false otherwise.
 */
bool ui_footer_focus_next(ui_footer_t* footer);

/**
 * @brief    Moves focus to the previous focusable child widget.
 *
 * @details  This function forwards the call to @ref ui_hbox_focus_previous().
 *
 * @param    footer Pointer to the footer.
 * @return   true if focus moved inside the footer, false otherwise.
 */
bool ui_footer_focus_previous(ui_footer_t* footer);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draws the header and its child widgets.
 *
 * @details  This function forwards the call to @ref ui_hbox_draw().
 *
 * @param    widget Pointer to the footer widget.
 */
void ui_footer_draw(ui_widget_t* widget);

/**
 * @brief    Updates the layout of the header and its children.
 *
 * @details  This function forwards the call to @ref ui_hbox_update_layout().
 *
 * @param    widget Pointer to the footer widget.
 */
void ui_footer_update_layout(ui_widget_t* widget);

/**
 * @brief    Called when the footer receives focus.
 *
 * @details  This function forwards the call to @ref ui_hbox_on_focus().
 *
 * @param    widget Pointer to the footer widget.
 */
void ui_footer_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the footer loses focus.
 *
 * @details  This function forwards the call to @ref ui_hbox_on_blur().
 *
 * @param    widget Pointer to the footer widget.
 */
void ui_footer_on_blur(ui_widget_t* widget);

/**
 * @brief    Handles UI events for the footer.
 *
 * @details  This function forwards the call to @ref ui_hbox_on_event().
 *
 * @param    widget Pointer to the footer widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_footer_on_event(ui_widget_t* widget, ui_event_t event);

/**
 * @brief    Retrieves the list of child widgets stored in the footer.
 *
 * @details  This function forwards the call to @ref ui_hbox_get_widgets().
 *
 * @param    widget      Pointer to the footer widget.
 * @param    out_widgets Output array for child widget pointers.
 * @return   Number of child widgets.
 */
uint8_t ui_footer_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_footer_x(ui_footer_t* footer) { return &footer->base.base.base.x; }
static inline int16_t* ui_footer_y(ui_footer_t* footer) { return &footer->base.base.base.y; }
static inline uint16_t* ui_footer_width(ui_footer_t* footer) { return &footer->base.base.base.width; }
static inline uint16_t* ui_footer_height(ui_footer_t* footer) { return &footer->base.base.base.height; }
static inline bool* ui_footer_focusable(ui_footer_t* footer) { return &footer->base.base.base.focusable; }
static inline ui_widget_t** ui_footer_parent(ui_footer_t* footer) { return &footer->base.base.base.parent; }
static inline uint8_t* ui_footer_border_thickness(ui_footer_t* footer) { return &footer->base.base.border_thickness; }
static inline uint32_t* ui_footer_border_color(ui_footer_t* footer) { return &footer->base.base.border_color; }
static inline uint32_t* ui_footer_background_color(ui_footer_t* footer) { return &footer->base.base.background_color; }
static inline uint8_t* ui_footer_padding_left(ui_footer_t* footer) { return &footer->base.base.padding_left; }
static inline uint8_t* ui_footer_padding_right(ui_footer_t* footer) { return &footer->base.base.padding_right; }
static inline uint8_t* ui_footer_padding_top(ui_footer_t* footer) { return &footer->base.base.padding_top; }
static inline uint8_t* ui_footer_padding_bottom(ui_footer_t* footer) { return &footer->base.base.padding_bottom; }

// Widgets stretching:
static inline ui_stretch_t* ui_footer_stretch(ui_footer_t* footer) { return &footer->base.stretch; }

// Alignment:
static inline ui_align_x_t* ui_footer_align_horizontal(ui_footer_t* footer) { return &footer->base.align_horizontal; }
static inline ui_align_y_t* ui_footer_align_vertical(ui_footer_t* footer) { return &footer->base.align_vertical; }

// Spacing between widgets:
static inline uint16_t* ui_footer_spacing(ui_footer_t* footer) { return &footer->base.spacing; }



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_footer_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a footer instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a footer.
 */
#define footer(widget) ((ui_footer_t*)(widget))


// Base widget:
#define footer_x(footer)                (*ui_footer_x(footer))
#define footer_y(footer)                (*ui_footer_y(footer))
#define footer_width(footer)            (*ui_footer_width(footer))
#define footer_height(footer)           (*ui_footer_height(footer))
#define footer_focusable(footer)        (*ui_footer_focusable(footer))
#define footer_parent(footer)           (*ui_footer_parent(footer))

#define footer_border_thickness(footer) (*ui_footer_border_thickness(footer))
#define footer_border_color(footer)     (*ui_footer_border_color(footer))
#define footer_background_color(footer) (*ui_footer_background_color(footer))
#define footer_padding_left(footer)     (*ui_footer_padding_left(footer))
#define footer_padding_right(footer)    (*ui_footer_padding_right(footer))
#define footer_padding_top(footer)      (*ui_footer_padding_top(footer))
#define footer_padding_bottom(footer)   (*ui_footer_padding_bottom(footer))

// Widgets stretching:
#define footer_stretch(footer)          (*ui_footer_stretch(footer))

// Alignment:
#define footer_align_horizontal(footer) (*ui_footer_align_horizontal(footer))
#define footer_align_vertical(footer)   (*ui_footer_align_vertical(footer))

// Spacing between widgets:
#define footer_spacing(footer)          (*ui_footer_spacing(footer))

#endif /* UI_FOOTER_H */