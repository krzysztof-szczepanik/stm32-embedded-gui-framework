#include "ui_main_screen.h"
#include <stdbool.h>
#include "lcd.h"
#include "tim.h"
#include "ui_color.h"
#include "ui_screen_manager.h"
#include "ui_screen.h"
#include "ui_screens_data.h"



// ==================== VARIABLES ====================

static ui_main_screen_t* g_main_screen;



// ==================== CALLBACKS ====================

static bool button_modes_clicked(void) {
	ui_screen_manager_set_current_screen_by_id(UI_MODES_SCREEN);

    return true;
}

static bool button_settings_clicked(void) {
	ui_screen_manager_set_current_screen_by_id(UI_SETTINGS_SCREEN);

    return true;
}

static bool button_start_stop_clicked(void) {
	ui_main_screen_t* main_screen = g_main_screen;

	timer_state_t* timer_state = &screens_data().timer_state;

	ui_button_t* button_start_stop = &main_screen->button_start_stop;
	ui_label_t* button_start_stop_label = &button_label(button_start_stop);

	ui_button_t* button_reset = &main_screen->button_reset;

	if (*timer_state == TIMER_STOPPED) {
		// Change timer state:
		*timer_state = TIMER_RUNNING;

		label_text_format(button_start_stop_label, "STOP");
		label_text_font_color(button_start_stop_label) = ui_color_argb(255, 248, 248, 248);
		button_border_color(button_start_stop) = ui_color_argb(255, 178, 85, 82);
		button_background_color(button_start_stop) = ui_color_argb(255, 227, 134, 131);
		button_focus_border_color(button_start_stop) = ui_color_argb(255, 158, 65, 62);
		button_focus_background_color(button_start_stop) = ui_color_argb(255, 207, 114, 111);

		button_focusable(button_reset) = false;

		// Start the hardware timer:
		HAL_TIM_Base_Start_IT(&htim9);
	} else {
		// Change timer state:
		*timer_state = TIMER_STOPPED;

		label_text_format(button_start_stop_label, "START");
		label_text_font_color(button_start_stop_label) = ui_color_argb(255, 248, 248, 248);
		button_border_color(button_start_stop) = ui_color_argb(255, 82, 178, 85);
		button_background_color(button_start_stop) = ui_color_argb(255, 131, 227, 134);
		button_focus_border_color(button_start_stop) = ui_color_argb(255, 62, 158, 65);
		button_focus_background_color(button_start_stop) = ui_color_argb(255, 111, 207, 114);

		button_focusable(button_reset) = true;

		// Stop the hardware timer:
		HAL_TIM_Base_Stop_IT(&htim9);
	}

    return true;
}

static bool button_reset_clicked(void) {
	ui_main_screen_t* main_screen = g_main_screen;

	// ================ TIME LABEL =================

	ui_label_value_t* label_value_time = &main_screen->label_value_time;
	ui_label_t* label_value_time_right_label = &label_value_right_label(label_value_time);

	int32_t time = screens_data().list_item_time_value_old;
	screens_data().list_item_time_value = time;

    label_text_format(label_value_time_right_label, "%02d:%02d:%02d", time / 3600, (time % 3600) / 60, time % 60);


    // =============== PROGRESS_BAR ================

    ui_progress_bar_t* progress_bar = &main_screen->progress_bar;
    progress_bar_set_value(progress_bar, 0);

    ui_screen_manager_get_current_screen()->base.invalidated = true;

    return true;
}



// =================== CONSTRUCTOR ===================

void ui_main_screen_init(ui_main_screen_t* main_screen) {

	g_main_screen = main_screen;
	screens_data().timer_state = TIMER_STOPPED;


	// ================= SCREEN ===================

	ui_screen_t* screen = &main_screen->base;
	ui_screen_init(screen);

	screen->update_data = ui_main_screen_update_data;




	// ================= HEADER ===================

	ui_header_t* header = &main_screen->header;
	ui_header_init(header, 50);
	header_border_thickness(header) = 0;
	header_background_color(header) = ui_color_argb(255, 71, 71, 71);
	header_padding_left(header) = 10;
	header_padding_right(header) = 10;
	header_padding_top(header) = 10;
	header_padding_bottom(header) = 10;
	header_spacing(header) = 10;


	// ================= FOOTER ===================

	ui_footer_t* footer = &main_screen->footer;
	ui_footer_init(footer, 50);
	footer_border_thickness(footer) = 0;
	footer_background_color(footer) = ui_color_argb(255, 71, 71, 71);
	footer_padding_left(footer) = 10;
	footer_padding_right(footer) = 10;
	footer_padding_top(footer) = 10;
	footer_padding_bottom(footer) = 10;
	footer_spacing(footer) = 10;
	footer_stretch(footer) = UI_STRETCH_HEIGHT;


	// ================= SECTOR ===================

	ui_vbox_t* sector = &main_screen->sector;
	ui_vbox_init(sector, 0, header->base.base.base.height, LCD_WIDTH, LCD_HEIGHT - header->base.base.base.height - footer->base.base.base.height);
	vbox_border_thickness(sector) = 0;
	vbox_padding_left(sector) = 10;
	vbox_padding_right(sector) = 10;
	vbox_padding_top(sector) = 10;
	vbox_padding_bottom(sector) = 10;
	vbox_spacing(sector) = 10;
	vbox_stretch(sector) = UI_STRETCH_WIDTH;
	vbox_focusable(sector) = false;




	// ================= WIDGETS ===================

	// Header widgets:
	ui_button_t* button_modes = &main_screen->button_modes;
	ui_button_t* button_settings = &main_screen->button_settings;

	ui_button_init(button_modes, 0, 0, 80, 50);
	button_label(button_modes).text = "MODES";
	button_on_click(button_modes) = button_modes_clicked;

	ui_button_init(button_settings, 0, 0, 80, 50);
	button_label(button_settings).text  = "SETUP";
	button_on_click(button_settings) = button_settings_clicked;


	// Sector widgets:
	ui_progress_bar_t* progress_bar = &main_screen->progress_bar;
	ui_vbox_t* vbox = &main_screen->vbox;
	ui_label_value_t* label_value_time = &main_screen->label_value_time;
	ui_label_value_t* label_value_rpm = &main_screen->label_value_rpm;
	ui_label_value_t* label_value_temp = &main_screen->label_value_temp;

	ui_progress_bar_init(progress_bar, 0, 0, 200, 35);
	progress_bar_suffix(progress_bar) = "%";

	ui_vbox_init(vbox, 0, 0, 200, LCD_HEIGHT - header->base.base.base.height - footer->base.base.base.height - 20 - progress_bar->base.height - 10);
	vbox_border_thickness(vbox) = 2;
	vbox_padding_left(vbox) = 10;
	vbox_padding_right(vbox) = 10;
	vbox_padding_top(vbox) = 10;
	vbox_padding_bottom(vbox) = 10;
	vbox_spacing(vbox) = 10;
	vbox_stretch(vbox) = UI_STRETCH_BOTH;
	vbox_focusable(vbox) = false;

	ui_label_value_init(label_value_time, 0, 0, 200, 50);
	label_value_separator_x_offset(label_value_time) = 70;
	ui_label_t* label_value_time_left_label = &label_value_left_label(label_value_time);
	label_text(label_value_time_left_label) = "TIME";
	ui_label_t* label_value_time_right_label = &label_value_right_label(label_value_time);
	label_text_format(label_value_time_right_label, "%02d:%02d:%02d", screens_data().list_item_time_value / 3600, (screens_data().list_item_time_value % 3600) / 60, screens_data().list_item_time_value % 60);

	ui_label_value_init(label_value_rpm, 0, 0, 200, 50);
	label_value_separator_x_offset(label_value_rpm) = 70;
	ui_label_t* label_value_rpm_left_label = &label_value_left_label(label_value_rpm);
	label_text(label_value_rpm_left_label) = "RPM";
	ui_label_t* label_value_rpm_right_label = &label_value_right_label(label_value_rpm);
	label_text_format(label_value_rpm_right_label, "%dRPM", screens_data().list_item_rpm_value);

	ui_label_value_init(label_value_temp, 0, 0, 200, 50);
	label_value_separator_x_offset(label_value_temp) = 70;
	ui_label_t* label_value_temp_left_label = &label_value_left_label(label_value_temp);
	label_text(label_value_temp_left_label) = "TEMP";
	ui_label_t* label_value_temp_right_label = &label_value_right_label(label_value_temp);
	label_text_format(label_value_temp_right_label, "%dC", screens_data().list_item_temp_value);


	// Footer widgets:
	ui_button_t* button_start_stop = &main_screen->button_start_stop;
	ui_button_t* button_reset = &main_screen->button_reset;

	ui_button_init(button_start_stop, 0, 0, 170, 50);
	ui_label_t* button_start_stop_label = &button_label(button_start_stop);
	label_text_format(button_start_stop_label, "START");
	label_text_font_color(button_start_stop_label) = ui_color_argb(255, 248, 248, 248);
	button_border_color(button_start_stop) = ui_color_argb(255, 82, 178, 85);
	button_background_color(button_start_stop) = ui_color_argb(255, 131, 227, 134);
	button_focus_border_color(button_start_stop) = ui_color_argb(255, 62, 158, 65);
	button_focus_background_color(button_start_stop) = ui_color_argb(255, 111, 207, 114);
	button_on_click(button_start_stop) = button_start_stop_clicked;

	ui_button_init(button_reset, 0, 0, 40, 50);
	ui_label_t* button_reset_label = &button_label(button_reset);
	label_text_format(button_reset_label, "R");
	label_text_font_color(button_reset_label) = ui_color_argb(255, 248, 248, 248);
	button_border_color(button_reset) = ui_color_argb(255, 178, 85, 82);
	button_background_color(button_reset) = ui_color_argb(255, 227, 134, 131);
	button_focus_border_color(button_reset) = ui_color_argb(255, 158, 65, 62);
	button_focus_background_color(button_reset) = ui_color_argb(255, 207, 114, 111);
	button_on_click(button_reset) = button_reset_clicked;




	// ======== CONTAINERS WIDGETS LISTS ===========

	ui_widget_t* vbox_widgets[] = {
		&label_value_time->base,
		&label_value_rpm->base,
		&label_value_temp->base
	};

	uint8_t vbox_widgets_count = sizeof(vbox_widgets) / sizeof(vbox_widgets[0]);
	ui_vbox_add_widgets(vbox, vbox_widgets, vbox_widgets_count);


	ui_widget_t* header_widgets[] = {
		&button_modes->base,
		&button_settings->base
	};

	uint8_t header_widgets_count = sizeof(header_widgets) / sizeof(header_widgets[0]);
	ui_header_add_widgets(header, header_widgets, header_widgets_count);


	ui_widget_t* sector_widgets[] = {
		&progress_bar->base,
		&vbox->base.base
	};

	uint8_t sector_widgets_count = sizeof(sector_widgets) / sizeof(sector_widgets[0]);
	ui_vbox_add_widgets(sector, sector_widgets, sector_widgets_count);


	ui_widget_t* footer_widgets[] = {
		&button_start_stop->base,
		&button_reset->base
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

void ui_main_screen_update_data(ui_screen_t* screen) {
	ui_main_screen_t* main_screen = MAIN_SCREEN(screen);

	ui_label_value_t* label_value_rpm = &main_screen->label_value_rpm;
	ui_label_value_t* label_value_temp = &main_screen->label_value_temp;
	ui_label_value_t* label_value_time = &main_screen->label_value_time;

	ui_label_t* label_value_rpm_right_label = &label_value_right_label(label_value_rpm);
	ui_label_t* label_value_temp_right_label = &label_value_right_label(label_value_temp);
	ui_label_t* label_value_time_right_label = &label_value_right_label(label_value_time);

    label_text_format(label_value_rpm_right_label,  "%dRPM", screens_data().list_item_rpm_value);
    label_text_format(label_value_temp_right_label, "%dC",   screens_data().list_item_temp_value);
    label_text_format(label_value_time_right_label, "%02d:%02d:%02d", screens_data().list_item_time_value / 3600, (screens_data().list_item_time_value % 3600) / 60, screens_data().list_item_time_value % 60);

	// We synchronized the screen state with the shared data by ui_screens_data,
	// so we need to mark the current screen as invalidated.
	// This tells the render loop that the screen has changed and must be redrawn.
	// Without this, widget value updates may stay in memory and not appear on the LCD.
    ui_screen_manager_get_current_screen()->base.invalidated = true;
}



// ==================== FUNCTIONS ====================

static void ui_main_screen_timer_finished() {
	button_start_stop_clicked();
	button_reset_clicked();
}

void ui_main_screen_update_time() {
	ui_main_screen_t* main_screen = g_main_screen;


	// ================ TIME LABEL =================

	ui_label_value_t* label_value_time = &main_screen->label_value_time;
	ui_label_t* label_value_time_right_label = &label_value_right_label(label_value_time);

	int32_t time_remaining = screens_data().list_item_time_value;
	int32_t time_total = screens_data().list_item_time_value_old;

	// Update time text:
    label_text_format(label_value_time_right_label, "%02d:%02d:%02d", time_remaining / 3600, (time_remaining % 3600) / 60, time_remaining % 60);


    // =============== PROGRESS_BAR ================

	ui_progress_bar_t* progress_bar = &main_screen->progress_bar;

    if (time_total > 0) {

    	int32_t elapsed = time_total - time_remaining; // how many seconds have passed since the timer started

    	float ratio = (float)elapsed  / (float)time_total; // 0.0 - 1.0
    	int32_t progress = (int32_t)(ratio * 100.0f); // conversion to 0-100%

    	if (progress < 0) { progress = 0; }
    	if (progress > 100) { progress = 100; }

	    progress_bar_set_value(progress_bar, progress);
    }


    // ============== TIME END CHECK ===============

    if (time_remaining <= 0 && screens_data().timer_state == TIMER_RUNNING) {
    	ui_main_screen_timer_finished();
    }

	// We synchronized the screen state with the shared data by ui_screens_data,
	// so we need to mark the current screen as invalidated.
	// This tells the render loop that the screen has changed and must be redrawn.
	// Without this, widget value updates may stay in memory and not appear on the LCD.
    ui_screen_manager_get_current_screen()->base.invalidated = true;
}