/**
 ******************************************************************************
 * @file     ui_container.h
 * @brief    Base container widget for grouping and positioning child widgets.
 *
 * @details  A container is a widget that holds and manages a list of child
 *           widgets.
 * 
 *           It provides:
 *           - background and border rendering
 *           - padding handling
 *           - focus navigation between child widgets
 *           - recursive layout propagation
 *
 *           Containers do not define their own layout strategy. Instead,
 *           specialized layout widgets such as HBox, VBox, Header, and Footer
 *           extend this type and implement their own layout logic in
 *           update_layout().
 *
 *           All container-based widgets embed this structure as their first
 *           member.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 Krzysztof Szczepanik.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H

#include "ui_widget.h"

#define UI_CONTAINER_MAX_WIDGETS 16  /**< Maximum number of widgets inside a container */



// ====================== TYPES ======================

/**
 * @brief    Base container structure used to group child widgets.
 *
 * @details  This structure stores child widget pointers, focus state,
 *           padding, border settings, and background color. Layout containers
 *           extend this type and implement their own layout logic.
 */
typedef struct {
	// Base widget:
    ui_widget_t base;                                /**< Base widget inherited by all containers. */

    // Widgets:
    ui_widget_t* widgets[UI_CONTAINER_MAX_WIDGETS];  /**< Array of widgets. */
    uint8_t widgets_count;                           /**< Number of widgets. */

	// Focused widget index:
    uint8_t focused_widget_index;                    /**< Index of the currently focused widget. */
    bool focus_entered;                              /**< Flag indicating if focus is inside container */

    // Border:
    uint8_t border_thickness;                        /**< Thickness of the container border. */
    uint32_t border_color;                           /**< Color of the container border in ARGB format. */

    // Background:
    uint32_t background_color;                       /**< Color of the container background in ARGB format. */

    // Padding:
    uint8_t padding_left;                            /**< Left padding. */
    uint8_t padding_right;                           /**< Right padding. */
    uint8_t padding_top;                             /**< Top padding. */
    uint8_t padding_bottom;                          /**< Bottom padding. */
} ui_container_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initializes a container widget.
 *
 * @details  This function prepares the container for use by:
 *           - initializing the base widget
 *           - clearing the child widget list
 *           - resetting focus state
 *           - applying default border, background, and padding values
 *
 *           All container-based widgets must call this function before
 *           adding children.
 *
 * @param    container Pointer to the container instance.
 * @param    x         X position of the container.
 * @param    y         Y position of the container.
 * @param    width     Width of the container.
 * @param    height    Height of the container.
 */
void ui_container_init(ui_container_t* container, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ==================== FUNCTIONS ====================

/**
 * @brief    Adds a single widget to the container.
 *
 * @details  This function appends the widget to the container's internal
 *           list, assigns the container as its parent, and recalculates
 *           the layout of all child widgets.
 *
 * @param    container Pointer to the container.
 * @param    widget    Pointer to the widget to add.
 */
void ui_container_add_widget(ui_container_t* container, ui_widget_t* widget);

/**
 * @brief    Adds multiple widgets to the container.
 *
 * @details  Widgets are added sequentially until either the provided list
 *           is exhausted or the container reaches its maximum capacity.
 *
 * @param    container Pointer to the container.
 * @param    widgets   Array of widget pointers.
 * @param    count     Number of widgets in the array.
 */
void ui_container_add_widgets(ui_container_t* container, ui_widget_t** widgets, uint8_t count);

/**
 * @brief    Draws the container's background and border.
 *
 * @details  This function renders the container's border (if enabled) and
 *           fills the inner area with the configured background color.
 *
 * @param    widget Pointer to the container widget.
 */
void ui_container_draw_background(ui_widget_t* widget);



// ================= FOCUS FUNCTIONS ==================

/**
 * @brief    Moves focus to the next focusable child widget.
 *
 * @details  If the currently focused widget is the last in the list, the
 *           function returns false, indicating that focus should leave the
 *           container.
 *
 * @param    container Pointer to the container.
 * @return   true if focus moved inside the container, false otherwise.
 */
bool ui_container_focus_next(ui_container_t* container);

/**
 * @brief    Moves focus to the previous focusable child widget.
 *
 * @details  If the currently focused widget is the first in the list, the
 *           function returns false, indicating that focus should leave the
 *           container.
 *
 * @param    container Pointer to the container.
 * @return   true if focus moved inside the container, false otherwise.
 */
bool ui_container_focus_previous(ui_container_t* container);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draws the container and all its child widgets.
 *
 * @details  This function first draws the container's background and
 *           border, then iterates through all child widgets and calls their
 *           draw() functions in order.
 *
 * @param    widget Pointer to the container widget.
 */
void ui_container_draw(ui_widget_t* widget);

/**
 * @brief    Updates the layout of the container and its children.
 *
 * @details  Computes global render coordinates based on parent position,
 *           border thickness, and padding. Child widgets receive updated
 *           render positions and recursively update their own layout.
 *
 * @param    widget Pointer to the container widget.
 */
void ui_container_update_layout(ui_widget_t* widget);

/**
 * @brief    Called when the container receives focus.
 *
 * @details  Focus is transferred to the first or last child widget
 *           depending on the direction of navigation stored in the global
 *           direction module.
 *
 * @param    widget Pointer to the container widget.
 */
void ui_container_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the container loses focus.
 *
 * @details  The currently focused child widget is blurred and the
 *           container's internal focus state is reset.
 *
 * @param    widget Pointer to the container widget.
 */
void ui_container_on_blur(ui_widget_t* widget);

/**
 * @brief    Handles UI events for the container.
 *
 * @details  Events are first passed to the focused child widget. If the
 *           child does not handle the event, the container attempts to
 *           move focus according to the event type.
 *
 * @param    widget Pointer to the container widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_container_on_event(ui_widget_t* widget, ui_event_t event);

/**
 * @brief    Retrieves the list of child widgets stored in the container.
 *
 * @details  Copies all child widget pointers into the provided output
 *           array and returns the number of widgets stored in the
 *           container.
 *
 * @param    widget      Pointer to the container widget.
 * @param    out_widgets Output array for child widget pointers.
 * @return   Number of child widgets.
 */
uint8_t ui_container_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_container_x(ui_container_t* container) { return &container->base.x; }
static inline int16_t* ui_container_y(ui_container_t* container) { return &container->base.y; }
static inline uint16_t* ui_container_width(ui_container_t* container) { return &container->base.width; }
static inline uint16_t* ui_container_height(ui_container_t* container) { return &container->base.height; }
static inline bool* ui_container_focusable(ui_container_t* container) { return &container->base.focusable; }
static inline ui_widget_t** ui_container_parent(ui_container_t* container) { return &container->base.parent; }

// Widgets:
static inline ui_widget_t*** ui_container_widgets(ui_container_t* container) { return (ui_widget_t***)&container->widgets; }
static inline uint8_t* ui_container_widgets_count(ui_container_t* container) { return &container->widgets_count; }

// Border:
static inline uint8_t* ui_container_border_thickness(ui_container_t* container) { return &container->border_thickness; }
static inline uint32_t* ui_container_border_color(ui_container_t* container) { return &container->border_color; }

// Background:
static inline uint32_t* ui_container_background_color(ui_container_t* container) { return &container->background_color; }

// Padding:
static inline uint8_t* ui_container_padding_left(ui_container_t* container) { return &container->padding_left; }
static inline uint8_t* ui_container_padding_right(ui_container_t* container) { return &container->padding_right; }
static inline uint8_t* ui_container_padding_top(ui_container_t* container) { return &container->padding_top; }
static inline uint8_t* ui_container_padding_bottom(ui_container_t* container) { return &container->padding_bottom; }



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_container_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a container instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a container.
 */
#define CONTAINER(widget) ((ui_container_t*)(widget))


// Base widget:
#define container_x(container)                (*ui_container_x(container))
#define container_y(container)                (*ui_container_y(container))
#define container_width(container)            (*ui_container_width(container))
#define container_height(container)           (*ui_container_height(container))
#define container_focusable(container)        (*ui_container_focusable(container))
#define container_parent(container)           (*ui_container_parent(container))

// Widgets:
#define container_widgets(container)          (*ui_container_widgets(container))
#define container_widgets_count(container)    (*ui_container_widgets_count(container))

// Border:
#define container_border_thickness(container) (*ui_container_border_thickness(container))
#define container_border_color(container)     (*ui_container_border_color(container))

// Background:
#define container_background_color(container) (*ui_container_background_color(container))

// Padding:
#define container_padding_left(container)     (*ui_container_padding_left(container))
#define container_padding_right(container)    (*ui_container_padding_right(container))
#define container_padding_top(container)      (*ui_container_padding_top(container))
#define container_padding_bottom(container)   (*ui_container_padding_bottom(container))

#endif /* UI_CONTAINER_H */