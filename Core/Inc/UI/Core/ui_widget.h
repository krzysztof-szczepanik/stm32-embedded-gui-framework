/**
 ******************************************************************************
 * @file     ui_widget.h
 * @brief    Base UI widget structure and virtual interface for all UI
 *           elements.
 *
 * @details  This module defines the fundamental widget type used throughout
 *           the UI framework.
 * 
 *           A widget provides:
 *           - local geometry (x, y, width, height)
 *           - absolute render position (after layout)
 *           - focus handling
 *           - invalidation propagation
 *           - parent reference
 *           - virtual function callbacks for drawing, layout updates and
 *             event handling
 *
 *           All widgets and containers embed this structure as their first
 *           member, enabling polymorphic behavior across the entire UI
 *           system.
 *
 *           Containers override @ref ui_widget_t::get_widgets "get_widgets()"
 *           to expose their child widgets.
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

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <stdint.h>
#include <stdbool.h>
#include "ui_events.h"



// ====================== TYPES ======================

/**
 * @brief  Forward declaration of the widget structure.
 */
typedef struct ui_widget ui_widget_t;

/**
 * @brief    Base widget structure used by all UI elements.
 *
 * @details  This structure acts as a lightweight "class" with virtual
 *           methods.Every widget embeds this struct as its first member,
 *           enabling inheritance and polymorphism across the UI framework.
 */
struct ui_widget {

    // Geometry:
    int16_t x;           /**< Local X position relative to parent. */
    int16_t y;           /**< Local Y position relative to parent. */
    uint16_t width;      /**< Widget width. */
    uint16_t height;     /**< Widget height. */

    // Render position (absolute):
    int16_t render_x;    /**< Absolute X position after layout calculation. */
    int16_t render_y;    /**< Absolute Y position after layout calculation. */

    // Focus flags:
    bool focusable;      /**< Whether the widget can receive focus. */
    bool focused;        /**< Whether the widget is currently focused. */

    // Redraw flag:
    bool invalidated;    /**< Marks widget for redraw on the next render pass. */

    // Parent pointer:
    ui_widget_t* parent; /**< Pointer to parent widget (NULL for root). */

    // Virtual functions:
    /**
     * @brief  Draws the widget.
     * 
     * @param  widget Pointer to the widget instance.
     */
    void (*draw)(ui_widget_t* widget);
    /**
     * @brief  Updates widget layout (size and position).
     * 
     * @param  widget Pointer to the widget instance.
     */
    void (*update_layout)(ui_widget_t* widget);
    /**
     * @brief  Called when the widget receives focus.
     * 
     * @param  widget Pointer to the widget instance.
     */
    void (*on_focus)(ui_widget_t* widget);
    /**
     * @brief  Called when the widget loses focus.
     * 
     * @param  widget Pointer to the widget instance.
     */
    void (*on_blur)(ui_widget_t* widget);
    /**
     * @brief   Handles a UI event.
     * 
     * @param   widget Pointer to the widget instance.
     * @param   event  Event to process.
     * @retval  true   Event was handled.
     * @retval  false  Event was not handled.
     */
    bool (*on_event)(ui_widget_t* widget, ui_event_t event);

    /**
     * @brief   Retrieves child widgets.
     *
     * @param   widget      Parent widget.
     * @param   out_widgets Output array for child widget pointers.
     * @retval  Number of children.
     * 
     * @note    Leaf widgets return 0.
     */
    uint8_t (*get_widgets)(ui_widget_t* widget, ui_widget_t** out_widgets);
};



// =================== CONSTRUCTOR ===================

/**
 * @brief  Initialize a widget with geometry and virtual function pointers.
 *
 * @param  widget        Pointer to the widget instance.
 * @param  x             Initial X position.
 * @param  y             Initial Y position.
 * @param  width         Initial width.
 * @param  height        Initial height.
 * @param  draw          Draw callback.
 * @param  update_layout Layout update callback.
 * @param  on_focus      Focus callback.
 * @param  on_blur       Blur callback.
 * @param  on_event      Event handler callback.
 * @param  get_widgets   Child retrieval callback.
 */
void ui_widget_init(ui_widget_t* widget, int16_t x, int16_t y, uint16_t width, uint16_t height,
		void (*draw)(ui_widget_t* widget),
		void (*update_layout)(ui_widget_t* widget),
		void (*on_focus)(ui_widget_t* widget),
		void (*on_blur)(ui_widget_t* widget),
		bool (*on_event)(ui_widget_t* widget, ui_event_t event),
		uint8_t (*get_widgets)(ui_widget_t* widget, ui_widget_t** out_widgets));



// ==================== FUNCTIONS ====================

/**
 * @brief  Marks the widget as invalidated and propagates the flag to its
 *         parent.
 *
 * @param  widget Pointer to the widget instance.
 */
void ui_widget_invalidate(ui_widget_t* widget);

/**
 * @brief  Sets the widget as focused and calls its focus callback.
 *
 * @param  widget Pointer to the widget instance.
 */
void ui_widget_focus(ui_widget_t* widget);

/**
 * @brief  Removes focus from the widget and calls its blur callback.
 *
 * @param  widget Pointer to the widget instance.
 */
void ui_widget_blur(ui_widget_t* widget);


// =============== GETTERS (REFERENCE) ===============

// Geometry:
static inline int16_t* ui_widget_x(ui_widget_t* widget) { return &widget->x; }
static inline int16_t* ui_widget_y(ui_widget_t* widget) { return &widget->y; }
static inline uint16_t* ui_widget_width(ui_widget_t* widget) { return &widget->width; }
static inline uint16_t* ui_widget_height(ui_widget_t* widget) { return &widget->height; }

// Focus flags:
static inline bool* ui_widget_focusable(ui_widget_t* widget) { return &widget->focusable; }

// Redraw flag:
static inline bool* ui_widget_invalidated(ui_widget_t* widget) { return &widget->invalidated; }

// Parent pointer:
static inline ui_widget_t** ui_widget_parent(ui_widget_t* widget) { return &widget->parent; }



// ===================== MACROS ======================

// Geometry:
#define widget_x(widget)           (*ui_widget_x(widget))
#define widget_y(widget)           (*ui_widget_y(widget))
#define widget_width(widget)       (*ui_widget_width(widget))
#define widget_height(widget)      (*ui_widget_height(widget))

// Focus flags:
#define widget_focusable(widget)   (*ui_widget_focusable(widget))

// Redraw flag:
#define widget_invalidated(widget) (*ui_widget_invalidated(widget))

// Parent pointer:
#define widget_parent(widget)      (*ui_widget_parent(widget))

#endif /* UI_WIDGET_H */