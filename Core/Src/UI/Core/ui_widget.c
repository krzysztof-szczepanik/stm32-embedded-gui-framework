/**
 ******************************************************************************
 * @file     ui_widget.c
 * @brief    Implementation of the base UI widget structure and virtual
 *           interface for all UI elements.
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


#include "ui_widget.h"
#include <stddef.h>



// =================== CONSTRUCTOR ===================

void ui_widget_init(ui_widget_t* widget, int16_t x, int16_t y, uint16_t width, uint16_t height,
		void (*draw)(ui_widget_t* widget),
		void (*update_layout)(ui_widget_t* widget),
		void (*on_focus)(ui_widget_t* widget),
		void (*on_blur)(ui_widget_t* widget),
		bool (*on_event)(ui_widget_t* widget, ui_event_t event),
		uint8_t (*get_children)(ui_widget_t* widget, ui_widget_t** out_children)) {

	// Geometry:
	widget->x = x;
	widget->y = y;
	widget->width = width;
	widget->height = height;

	// Render position (absolute):
	widget->render_x = x;
	widget->render_y = y;

	// Focus flags:
	widget->focusable = true;
	widget->focused = false;

	// Redraw flag:
	widget->invalidated = true;

	// Parent pointer:
	widget->parent = NULL;

	// Virtual functions:
	widget->draw = draw;
	widget->update_layout = update_layout;
	widget->on_focus = on_focus;
	widget->on_blur = on_blur;
	widget->on_event = on_event;
	widget->get_widgets = get_children;
}



// ==================== FUNCTIONS ====================

void ui_widget_invalidate(ui_widget_t* widget) {
    widget->invalidated = true;

	// Propagate invalidation up to the screen:
    if (widget->parent) {
        ui_widget_invalidate(widget->parent);
    }
}

void ui_widget_focus(ui_widget_t* widget) {
    widget->focused = true;
    widget->on_focus(widget);
}

void ui_widget_blur(ui_widget_t* widget) {
    widget->focused = false;
    widget->on_blur(widget);
}