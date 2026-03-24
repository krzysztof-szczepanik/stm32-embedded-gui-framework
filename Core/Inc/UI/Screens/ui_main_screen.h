#ifndef UI_MAIN_SCREEN_H
#define UI_MAIN_SCREEN_H

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
    ui_button_t button_modes;
    ui_button_t button_settings;

    // Widgety - sector:
    ui_progress_bar_t progress_bar;
    ui_vbox_t vbox;
    ui_label_value_t label_value_time;
    ui_label_value_t label_value_rpm;
    ui_label_value_t label_value_temp;

	// Widgety - footer:
    ui_button_t button_start_stop;
    ui_button_t button_reset;
} ui_main_screen_t;



// =================== CONSTRUCTOR ===================

void ui_main_screen_init(ui_main_screen_t* main_screen);



// ================ VIRTUAL FUNCTIONS ================

void ui_main_screen_update_data(ui_screen_t* screen);



// ==================== FUNCTIONS ====================

void ui_main_screen_update_time();



// ===================== MACROS ======================

// Rzutowanie:
#define MAIN_SCREEN(screen) ((ui_main_screen_t*)(screen))

#endif /* UI_MAIN_SCREEN_H */
