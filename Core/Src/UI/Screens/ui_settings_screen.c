#include "ui_settings_screen.h"
#include <stdbool.h>
#include "lcd.h"
#include "ui_color.h"
#include "ui_screen_manager.h"
#include "ui_screen.h"
#include "ui_screens_data.h"



static ui_settings_screen_t* g_settings_screen;



// ==================== CALLBACKS ====================

static bool button_back_clicked(void) {
	ui_screen_manager_set_current_screen_by_id(UI_MAIN_SCREEN);

    return true;
}

static bool button_apply_clicked(void) {
	ui_list_item_t* list_item_volume = &g_settings_screen->list_item_volume;
	ui_list_item_t* list_item_sound = &g_settings_screen->list_item_sound;
	ui_list_item_t* list_item_simulation = &g_settings_screen->list_item_simulation;

	ui_slider_t* slider_volume = (ui_slider_t*)list_item_object(list_item_volume);
	ui_toggle_t* toggle_sound = (ui_toggle_t*)list_item_object(list_item_sound);
	ui_toggle_t* toggle_sim = (ui_toggle_t*)list_item_object(list_item_simulation);

	screens_data().list_item_volume_value = slider_value(slider_volume);
	screens_data().list_item_sound_value = toggle_selected(toggle_sound);
	screens_data().list_item_sim_value = toggle_selected(toggle_sim);

    return true;
}



// =================== CONSTRUCTOR ===================

void ui_settings_screen_init(ui_settings_screen_t* settings_screen) {

	g_settings_screen = settings_screen;




	// ================= SCREEN ===================

	ui_screen_t* screen = &settings_screen->base;
	ui_screen_init(screen);




	// ================= HEADER ===================

	ui_header_t* header = &settings_screen->header;
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

	ui_footer_t* footer = &settings_screen->footer;
	ui_footer_init(footer, 50);
	footer_border_thickness(footer) = 0;
	footer_background_color(footer) = ui_color_argb(255, 71, 71, 71);
	footer_padding_left(footer) = 10;
	footer_padding_right(footer) = 10;
	footer_padding_top(footer) = 10;
	footer_padding_bottom(footer) = 10;
	footer_spacing(footer) = 10;


	// ================= SECTOR ===================

	ui_vbox_t* sector = &settings_screen->sector;
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
	ui_label_t* label = &settings_screen->label;

	ui_label_init(label, 0, 0, 100, 50);
	label_text(label) = "SETTINGS";
	label_text_font_color(label) = LCD_COLOR_WHITE;
	label_background_color(label) = header_background_color(header);
	label_border_color(label) = header_background_color(header);
	label_align_horizontal(label) = UI_ALIGN_CENTER_X;
	label_align_vertical(label) = UI_ALIGN_CENTER_Y;


	// Sector widgets:
	ui_list_item_t* list_item_volume = &settings_screen->list_item_volume;
	ui_list_item_t* list_item_sound = &settings_screen->list_item_sound;
	ui_list_item_t* list_item_simulation = &settings_screen->list_item_simulation;

	ui_list_item_init(list_item_volume, 0, 0, 200, 50);
	list_item_object_type(list_item_volume, UI_LIST_ITEM_SLIDER);
	ui_label_t* list_item_volume_label = &list_item_label(list_item_volume);
	label_text(list_item_volume_label) = "VOLUME";
	ui_slider_t* list_item_volume_object = ((ui_slider_t*)list_item_object(list_item_volume));
	slider_step(list_item_volume_object) = 5;
	slider_auto_set_value(list_item_volume_object);
	slider_suffix(list_item_volume_object) = "%";

	ui_list_item_init(list_item_sound, 0, 0, 200, 50);
	list_item_object_type(list_item_sound, UI_LIST_ITEM_TOGGLE);
	ui_label_t* list_item_sound_label = &list_item_label(list_item_sound);
	label_text(list_item_sound_label) = "SOUND";
	ui_toggle_t* list_item_sound_object = ((ui_toggle_t*)list_item_object(list_item_sound));

	ui_list_item_init(list_item_simulation, 0, 0, 200, 50);
	list_item_object_type(list_item_simulation, UI_LIST_ITEM_TOGGLE);
	ui_label_t* list_item_simulation_label = &list_item_label(list_item_simulation);
	label_text(list_item_simulation_label) = "SIM";
	ui_toggle_t* list_item_simulation_object = ((ui_toggle_t*)list_item_object(list_item_simulation));

	screens_data().list_item_volume_value  = slider_value(list_item_volume_object);
	screens_data().list_item_sound_value = toggle_selected(list_item_sound_object);
	screens_data().list_item_sim_value = toggle_selected(list_item_simulation_object);


	// Footer widgets:
	ui_button_t* button_back = &settings_screen->button_back;
	ui_button_t* button_apply = &settings_screen->button_apply;

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
		&list_item_volume->base,
		&list_item_sound->base,
		&list_item_simulation->base
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