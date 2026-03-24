#ifndef UI_SETTINGS_SCREEN_H
#define UI_SETTINGS_SCREEN_H

#include "ui_screen.h"
#include "ui_container.h"
#include "ui_hbox.h"
#include "ui_vbox.h"
#include "ui_header.h"
#include "ui_footer.h"
#include "ui_label.h"
#include "ui_label_value.h"
#include "ui_button.h"
#include "ui_list_item.h"
#include "ui_slider.h"
#include "ui_slider_time.h"
#include "ui_progress_bar.h"
#include "ui_toggle.h"



// ====================== TYPES ======================

typedef struct {
    ui_screen_t base;

    // Sekcje:
    ui_header_t header;
    ui_footer_t footer;
    ui_vbox_t sector;

    // Widgety - header:
    ui_label_t label;

    // Widgety - sector:
	ui_list_item_t list_item_volume;
	ui_list_item_t list_item_sound;
	ui_list_item_t list_item_simulation;

	// Widgety - footer:
    ui_button_t button_back;
    ui_button_t button_apply;
} ui_settings_screen_t;



// =================== CONSTRUCTOR ===================

void ui_settings_screen_init(ui_settings_screen_t* settings_screen);

#endif /* UI_SETTINGS_SCREEN_H */
