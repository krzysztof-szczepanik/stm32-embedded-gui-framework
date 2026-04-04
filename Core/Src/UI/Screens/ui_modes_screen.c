#include "ui_modes_screen.h"
#include <stdbool.h>
#include "lcd.h"
#include "ui_color.h"
#include "ui_screen_manager.h"
#include "ui_screen.h"
#include "ui_screens_data.h"



// ==================== VARIABLES ====================

static ui_modes_screen_t* g_modes_screen;



// ==================== CALLBACKS ====================

static bool button_back_clicked(void) {
	ui_screen_manager_set_current_screen_by_id(UI_MAIN_SCREEN);

    return true;
}

static bool button_apply_clicked(void) {
	ui_list_item_t* list_item_time = &g_modes_screen->list_item_time;
	ui_list_item_t* list_item_rpm = &g_modes_screen->list_item_rpm;
	ui_list_item_t* list_item_temp = &g_modes_screen->list_item_temp;

	ui_slider_time_t* slider_time= (ui_slider_time_t*)list_item_object(list_item_time);
	ui_slider_t* slider_rpm = (ui_slider_t*)list_item_object(list_item_rpm);
	ui_slider_t* slider_temp = (ui_slider_t*)list_item_object(list_item_temp);

	screens_data().list_item_time_value = slider_time_value(slider_time) * 60; // slider_time.value has time in minutes, but we want to display seconds on the main_screen too, so we need to convert it to seconds by multiplying by 60
	screens_data().list_item_time_value_old = slider_time_value(slider_time) * 60;
	screens_data().list_item_rpm_value = slider_value(slider_rpm);
	screens_data().list_item_temp_value = slider_value(slider_temp);

    return true;
}



// =================== CONSTRUCTOR ===================

void ui_modes_screen_init(ui_modes_screen_t* modes_screen) {

	g_modes_screen = modes_screen;


	// ================= SCREEN ===================

	ui_screen_t* screen = &modes_screen->base;
	ui_screen_init(screen);

	screen->update_data = ui_modes_screen_update_data;




	// ================= HEADER ===================

	ui_header_t* header = &modes_screen->header;
	ui_header_init(header, 50);
	header_border_thickness(header) = 0;
	header_background_color(header) = ui_color_argb(255, 71, 71, 71);
	header_padding_left(header) = 10;
	header_padding_right(header) = 10;
	header_padding_top(header) = 10;
	header_padding_bottom(header) = 10;
	header_spacing(header) = 10;
	header_focusable(header) = false;


	// ================= FOOTER ===================

	ui_footer_t* footer = &modes_screen->footer;
	ui_footer_init(footer, 50);
	footer_border_thickness(footer) = 0;
	footer_background_color(footer) = ui_color_argb(255, 71, 71, 71);
	footer_padding_left(footer) = 10;
	footer_padding_right(footer) = 10;
	footer_padding_top(footer) = 10;
	footer_padding_bottom(footer) = 10;
	footer_spacing(footer) = 10;


	// ================= SECTOR ===================

	ui_vbox_t* sector = &modes_screen->sector;
	ui_vbox_init(sector, 0, header->base.base.base.height, LCD_WIDTH, LCD_HEIGHT - header->base.base.base.height - footer->base.base.base.height);
	vbox_border_thickness(sector) = 0;
	vbox_padding_left(sector) = 10;
	vbox_padding_right(sector) = 10;
	vbox_padding_top(sector) = 10;
	vbox_padding_bottom(sector) = 10;
	vbox_spacing(sector) = 10;
	vbox_stretch(sector) = UI_STRETCH_WIDTH;




	// ================= WIDGETS ===================

	// Header widgets:
	ui_label_t* label = &modes_screen->label;

	ui_label_init(label, 0, 0, 100, 50);
	label_text(label) = "MODES";
	label_text_font_color(label) = LCD_COLOR_WHITE;
	label_background_color(label) = header_background_color(header);
	label_border_color(label) = header_background_color(header);
	label_align_horizontal(label) = UI_ALIGN_CENTER_X;
	label_align_vertical(label) = UI_ALIGN_CENTER_Y;


	// Sector widgets:
	ui_list_item_t* list_item_time = &modes_screen->list_item_time;
	ui_list_item_t* list_item_rpm  = &modes_screen->list_item_rpm;
	ui_list_item_t* list_item_temp = &modes_screen->list_item_temp;

	ui_list_item_init(list_item_time, 0, 0, 200, 50);
	list_item_separator_x_offset(list_item_time) = 85;
	list_item_object_type(list_item_time, UI_LIST_ITEM_SLIDER_TIME);
	ui_label_t* list_item_time_label = &list_item_label(list_item_time);
	label_text(list_item_time_label) = "TIME";
	ui_slider_time_t* list_item_time_object = ((ui_slider_time_t*)list_item_object(list_item_time));
	slider_time_min(list_item_time_object) = 0;
	slider_time_max(list_item_time_object) = 240;
	slider_time_step(list_item_time_object) = 10;
	slider_time_auto_set_value(list_item_time_object);

	ui_list_item_init(list_item_rpm, 0, 0, 200, 50);
	list_item_separator_x_offset(list_item_rpm) = 85;
	list_item_object_type(list_item_rpm, UI_LIST_ITEM_SLIDER);
	ui_label_t* list_item_rpm_label = &list_item_label(list_item_rpm);
	label_text(list_item_rpm_label) = "SPEED";
	ui_slider_t* list_item_rpm_object = ((ui_slider_t*)list_item_object(list_item_rpm));
	slider_min(list_item_rpm_object) = 400;
	slider_max(list_item_rpm_object) = 1400;
	slider_step(list_item_rpm_object) = 100;
	slider_auto_set_value(list_item_rpm_object);
	slider_suffix(list_item_rpm_object) = "RPM";

	ui_list_item_init(list_item_temp, 0, 0, 200, 50);
	list_item_separator_x_offset(list_item_temp) = 85;
	list_item_object_type(list_item_temp, UI_LIST_ITEM_SLIDER);
	ui_label_t* list_item_temp_label = &list_item_label(list_item_temp);
	label_text(list_item_temp_label) = "TEMP";
	ui_slider_t* list_item_temp_object = ((ui_slider_t*)list_item_object(list_item_temp));
	slider_min(list_item_temp_object) = 20;
	slider_max(list_item_temp_object) = 90;
	slider_step(list_item_temp_object) = 10;
	slider_auto_set_value(list_item_temp_object);
	slider_suffix(list_item_temp_object) = "C";

	screens_data().list_item_time_value = slider_time_value(list_item_time_object) * 60; // slider_time.value has time in minutes, but we want to display seconds on the main_screen too, so we need to convert it to seconds by multiplying by 60
	screens_data().list_item_time_value_old = slider_time_value(list_item_time_object) * 60;
	screens_data().list_item_rpm_value  = slider_value(list_item_rpm_object);
	screens_data().list_item_temp_value = slider_value(list_item_temp_object);


	// Footer widgets:
	ui_button_t* button_back = &modes_screen->button_back;
	ui_button_t* button_apply = &modes_screen->button_apply;

	ui_button_init(button_back, 0, 0, 80, 50);
	button_label(button_back).text = "<-";
	button_on_click(button_back) = button_back_clicked;

	ui_button_init(button_apply, 0, 0, 80, 50);
	button_label(button_apply).text  = "APPLY";
	button_on_click(button_apply) = button_apply_clicked;




	// ======== CONTAINERS WIDGETS LISTS ===========

	ui_widget_t* header_widgets[] = {
		&label->base
	};

	uint8_t header_widgets_count = sizeof(header_widgets) / sizeof(header_widgets[0]);
	ui_header_add_widgets(header, header_widgets, header_widgets_count);


	ui_widget_t* sector_widgets[] = {
		&list_item_time->base,
		&list_item_rpm->base,
		&list_item_temp->base
	};

	uint8_t sector_widgets_count = sizeof(sector_widgets) / sizeof(sector_widgets[0]);
	ui_vbox_add_widgets(sector, sector_widgets, sector_widgets_count);


	ui_widget_t* footer_widgets[] = {
		&button_back->base,
		&button_apply->base
	};

	uint8_t footer_widgets_count = sizeof(footer_widgets) / sizeof(footer_widgets[0]);
	ui_footer_add_widgets(footer, footer_widgets, footer_widgets_count);




	// =========== SCREEN WIDGETS LIST ============

	ui_widget_t* screen_widgets[] = {
		&header->base.base.base,
		&sector->base.base,
		&footer->base.base.base
	};

	uint8_t screen_widgets_count = sizeof(screen_widgets) / sizeof(screen_widgets[0]);
	ui_screen_add_widgets(screen, screen_widgets, screen_widgets_count);
}



// ================ VIRTUAL FUNCTIONS ================

void ui_modes_screen_update_data(ui_screen_t* screen) {
    ui_modes_screen_t* modes_screen = MODES_SCREEN(screen);

    ui_list_item_t* list_item_time = &modes_screen->list_item_time;
    ui_slider_time_t* list_item_time_object = (ui_slider_time_t*)list_item_object(list_item_time);

    if (screens_data().list_item_sim_value) {
        slider_time_step(list_item_time_object) = 1;
        list_item_time_object->value = 0;
    } else {
        slider_time_step(list_item_time_object) = 10;
        slider_time_auto_set_value(list_item_time_object);
    }

	// We synchronized the screen state with the shared data by ui_screens_data,
	// so we need to mark the current screen as invalidated.
	// This tells the render loop that the screen has changed and must be redrawn.
	// Without this, widget value updates may stay in memory and not appear on the LCD.
    ui_screen_manager_get_current_screen()->base.invalidated = true;
}