/**
 ******************************************************************************
 * @file     ui_list_item.h
 * @brief    List item widget with left label and optional right-side object.
 *
 * @details  A list item consists of:
 *           - a left-aligned label (text)
 *           - an optional right-side interactive widget (slider, toggle, etc.)
 *           - a vertical separator between the two areas
 *
 *           It is used inside list-like UI containers to present settings
 *           or options in a structured “Label - Control” format.
 *
 *           The widget handles focus transitions between itself and the
 *           right-side object (if present).
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

#ifndef UI_LIST_ITEM_H
#define UI_LIST_ITEM_H

#include <stdint.h>
#include "ui_widget.h"
#include "ui_label.h"



// ====================== TYPES ======================

/**
 * @brief  Type of the right-side object displayed in a list item.
 */
typedef enum {
    UI_LIST_ITEM_NONE,         /**< No object on the right side. */
    UI_LIST_ITEM_SLIDER,       /**< ui_slider_t object. */
	UI_LIST_ITEM_SLIDER_TIME,  /**< ui_slider_time_t object. */
	UI_LIST_ITEM_TOGGLE        /**< ui_toggle_t object. */
} ui_list_item_object_type_t;

/**
 * @brief    List_item widget (label + optional right-side object).
 *
 * @details  The widget displays a left label and optionally an interactive
 *           control on the right side (slider, toggle, etc.). A vertical
 *           separator visually divides the two areas.
 *
 *           The widget manages focus transitions between itself and the
 *           right-side object.
 */
typedef struct {
	// Base widget:
    ui_widget_t base;                        /**< Base widget. */

    // Border:
    uint8_t border_thickness;                /**< Border thickness. */
    uint32_t border_color;                   /**< Border color. */

    // Background:
    uint32_t background_color;               /**< Background color. */

	// Separator:
	uint16_t separator_x_offset;             /**< X offset of the vertical separator. */

	// Label:
	ui_label_t label;                        /**< Left-side descriptive label. */
	uint8_t label_padding;                   /**< Padding around the left label. */

    // Right area (for slider, toggle, etc.):
	ui_list_item_object_type_t object_type;  /**< Type of right-side object. */
    ui_widget_t* object;                     /**< Pointer to created object. */
    uint8_t right_area_padding;              /**< Padding around right object. */

    // Focus:
	uint32_t focus_background_color;         /**< Background color when focused. */
	uint32_t focus_border_color;             /**< Border color when focused. */
} ui_list_item_t;



// =================== CONSTRUCTOR ===================

/**
 * @brief    Initialize a list_item widget.
 *
 * @details  Sets geometry, assigns virtual functions, initializes default
 *           properties and internal labels.
 *
 *           Most default properties are defined in @ref ui_theme.h.
 *
 * @param    list_item Pointer to the list_item instance.
 * @param    x         X position.
 * @param    y         Y position.
 * @param    width     List_item width.
 * @param    height    List_item height.
 */
void ui_list_item_init(ui_list_item_t* list_item, int16_t x, int16_t y, uint16_t width, uint16_t height);



// ================ VIRTUAL FUNCTIONS ================

/**
 * @brief    Draw the list_item.
 *
 * @param    widget Pointer to the list_item's base widget.
 */
void ui_list_item_draw(ui_widget_t* widget);

/**
 * @brief    Called when the list_item receives focus.
 *
 * @param    widget Pointer to the list_item's base widget.
 */
void ui_list_item_on_focus(ui_widget_t* widget);

/**
 * @brief    Called when the list_item loses focus.
 *
 * @param    widget Pointer to the list_item's base widget.
 */
void ui_list_item_on_blur(ui_widget_t* widget);

/**
 * @brief    Handle UI events for the list_item.
 *
 * @details  If a right-side object exists and is focused, the event is
 *           forwarded to it. If the object does not handle the event,
 *           focus returns to the list_item.
 *
 * @param    widget Pointer to the list_item's base widget.
 * @param    event  UI event to process.
 * @return   true if the event was handled, false otherwise.
 */
bool ui_list_item_on_event(ui_widget_t* widget, ui_event_t event);



// ===================== SETTERS =====================

/**
 * @brief    Set the type of the right-side object.
 *
 * @details  The object type can be set only once. The corresponding widget
 *           (slider, toggle, etc.) is created automatically.
 *
 * @param    widget Pointer to the list_item.
 * @param    type   Object type to create.
 */
void ui_list_item_object_type(ui_widget_t* widget, ui_list_item_object_type_t type);



// =============== GETTERS (REFERENCE) ===============

// Base widget:
static inline int16_t* ui_list_item_x(ui_list_item_t* list_item) { return &list_item->base.x; }
static inline int16_t* ui_list_item_y(ui_list_item_t* list_item) { return &list_item->base.y; }
static inline uint16_t* ui_list_item_width(ui_list_item_t* list_item) { return &list_item->base.width; }
static inline uint16_t* ui_list_item_height(ui_list_item_t* list_item) { return &list_item->base.height; }
static inline bool* ui_list_item_focusable(ui_list_item_t* list_item) { return &list_item->base.focusable; }

// Border:
static inline uint8_t* ui_list_item_border_thickness(ui_list_item_t* list_item) { return &list_item->border_thickness; }
static inline uint32_t* ui_list_item_border_color(ui_list_item_t* list_item) { return &list_item->border_color; }

// Separator:
static inline uint16_t* ui_list_item_separator_x_offset(ui_list_item_t* list_item) { return &list_item->separator_x_offset; }

// Label:
static inline ui_label_t* ui_list_item_label(ui_list_item_t* list_item) { return &list_item->label; }
static inline uint8_t* ui_list_item_label_padding(ui_list_item_t* list_item) { return &list_item->label_padding; }

// Right area (for slider, toggle, etc.):
static inline ui_widget_t** ui_list_item_object(ui_list_item_t* list_item) { return &list_item->object; }
static inline uint8_t* ui_list_item_right_area_padding(ui_list_item_t* list_item) { return &list_item->right_area_padding; }

// Focus:
static inline uint32_t* ui_list_item_focus_background_color(ui_list_item_t* list_item) { return &list_item->focus_background_color; }
static inline uint32_t* ui_list_item_focus_border_color(ui_list_item_t* list_item) { return &list_item->focus_border_color; }



// ===================== MACROS ======================

// Casting:
/**
 * @brief    Casts a generic widget pointer to ui_list_item_t.
 *
 * @details  This macro is used when a function receives a ui_widget_t
 *           pointer but the caller knows it refers to a list_item instance.
 * 
 *           It performs a safe C-style cast without additional checks.
 * 
 * @param    widget Pointer to a ui_widget_t that is known to be a list_item.
 */
#define LIST_ITEM(widget) ((ui_list_item_t*)(widget))


// Base widget:
#define list_item_x(list_item)                        (*ui_list_item_x(list_item))
#define list_item_y(list_item)                        (*ui_list_item_y(list_item))
#define list_item_width(list_item)                    (*ui_list_item_width(list_item))
#define list_item_height(list_item)                   (*ui_list_item_height(list_item))
#define list_item_focusable(list_item)                (*ui_list_item_focusable(list_item))

// Border:
#define list_item_border_thickness(list_item)         (*ui_list_item_border_thickness(list_item))
#define list_item_border_color(list_item)             (*ui_list_item_border_color(list_item))

// Separator:
#define list_item_separator_x_offset(list_item)       (*ui_list_item_separator_x_offset(list_item))

// Label:
#define list_item_label(list_item)                    (*ui_list_item_label(list_item))
#define list_item_label_padding(list_item)            (*ui_list_item_label_padding(list_item))

// Right area (for slider, toggle, etc.):
#define list_item_object_type(list_item, object_type) (ui_list_item_object_type(&(list_item)->base, object_type))
#define list_item_object(list_item)                   (*ui_list_item_object(list_item))
#define list_item_right_area_padding(list_item)       (*ui_list_item_right_area_padding(list_item))

// Focus:
#define list_item_focus_background_color(list_item)   (*ui_list_item_focus_background_color(list_item))
#define list_item_focus_border_color(list_item)       (*ui_list_item_focus_border_color(list_item))

#endif /* UI_LIST_ITEM_H */