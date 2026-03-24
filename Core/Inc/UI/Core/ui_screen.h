/**
 ******************************************************************************
 * @file     ui_screen.h
 * @brief    Base screen container.
 *
 * @details  This module defines the base screen type used as the root widget
 *           of every displayed view.
 * 
 *           A screen manages its child widgets, handles focus navigation,
 *           routes UI events to widgets, and propagates drawing and layout
 *           updates through the entire widget tree.
 * 
 *           All application screens inherit from this structure.
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

#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include "ui_widget.h"

#define UI_SCREEN_MAX_WIDGETS 16  /**< Maximum number of widgets inside a screen */



// ====================== TYPES ======================

/**
 * @brief  Forward declaration of the screen structure.
 */
typedef struct ui_screen ui_screen_t;

/**
 * @brief    Base screen structure used as the root widget of a view.
 *
 * @details  A screen acts as a container for widgets, manages focus
 *           navigation, and propagates events and layout updates through the
 *           widget tree.
 */
struct ui_screen {
	
    // Base widget:
    ui_widget_t base;                             /**< Base widget inherited by all screens. */

    // Widgets:
    ui_widget_t* widgets[UI_SCREEN_MAX_WIDGETS];  /**< Array of widgets. */
    uint8_t widgets_count;                        /**< Number of widgets. */

    // Focused widget index:
    uint8_t focused_widget_index;                 /**< Index of the currently focused widget. */

    // Virtual functions:
	/**
	 * @brief    Optional screen update callback.
	 *
	 * @details  This function is called automatically whenever the screen
	 *           becomes active. It allows the screen to refresh its internal
	 *           widget values based on the shared UI state stored in
	 *           @ref ui_screens_data.
	 *
	 *           Typical use cases:
	 *           - synchronizing widget values with settings changed on another
	 *             screen
	 *           - restoring slider/toggle states
	 *           - updating labels before the screen is drawn
	 *           - reacting to global state changes (e.g. timer state)
	 *
	 *           Each screen may provide its own implementation of this function.
	 *           If NULL, no update is performed.
	 *
	 * @param    screen Pointer to the screen instance being activated.
	 */
    void (*update_data)(ui_screen_t* screen);
};



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initializes a screen.
 *
 * @details  This function prepares the screen for use by:
 *           - initializing the base widget
 *           - clearing the widget list
 *           - resetting focus state
 *           - clearing virtual function pointers
 *
 *           Every screen must call this function before adding widgets.
 *
 * @param    screen Pointer to the screen instance to initialize.
 */
void ui_screen_init(ui_screen_t* screen);



// ==================== FUNCTIONS ====================

/**
 * @brief    Adds a single widget to the screen.
 * 
 * @details  The widget is appended to the internal widget list and becomes
 *           part of the screen's layout and event routing system.
 * 
 * @param    screen Pointer to the screen.
 * @param    widget Pointer to the widget to add.
 */
void ui_screen_add_widget(ui_screen_t* screen, ui_widget_t* widget);

/**
 * @brief    Adds multiple widgets to the screen.
 * 
 * @details  Widgets are added sequentially until either the provided list
 *           is exhausted or the screen reaches its maximum capacity.
 * 
 * @param    screen  Pointer to the screen.
 * @param    widgets Array of widget pointers.
 * @param    count   Number of widgets in the array.
 */
void ui_screen_add_widgets(ui_screen_t* screen, ui_widget_t** widgets, uint8_t count);



// ================= FOCUS FUNCTIONS ==================

/**
 * @brief  Sets focus to the first focusable widget on the screen.
 * 
 * @param  screen Pointer to the screen.
 */
void ui_screen_focus_first(ui_screen_t* screen);

/**
 * @brief    Moves focus to the next focusable widget.
 * 
 * @details  Wraps around when reaching the end of the widget list.
 * 
 * @param    screen Pointer to the screen.
 */
void ui_screen_focus_next(ui_screen_t* screen);

/**
 * @brief    Moves focus to the previous focusable widget.
 * 
 * @details  Wraps around when reaching the beginning of the widget list.
 * 
 * @param    screen Pointer to the screen.
 */
void ui_screen_focus_previous(ui_screen_t* screen);



// ================= EVENT FUNCTIONS ==================

/**
 * @brief    Routes an event to the currently focused widget.
 *
 * @details  If the focused widget does not handle the event, the screen may
 *           attempt fallback handling (e.g., focus navigation).
 *
 * @param    screen Pointer to the screen.
 * @param    event  Event to process.
 */
void ui_screen_handle_event(ui_screen_t* screen, ui_event_t event);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief  Draws the screen and all its child widgets.
 * 
 * @param  widget Pointer to the screen's base widget.
 */
void ui_screen_draw(ui_widget_t* widget);

/**
 * @brief  Updates the layout of the screen and its child widgets.
 * 
 * @param  widget Pointer to the screen's base widget.
 */
void ui_screen_update_layout(ui_widget_t* widget);

/**
 * @brief   Returns the list of child widgets belonging to the screen.
 * 
 * @param   widget      Pointer to the screen's base widget.
 * @param   out_widgets Output array for child widget pointers.
 * @return  Number of child widgets.
 */
uint8_t ui_screen_get_widgets(ui_widget_t* widget, ui_widget_t** out_widgets);



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_screen_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a screen instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a screen.
 */
#define SCREEN(widget) ((ui_screen_t*)(widget))

#endif /* UI_SCREEN_H */