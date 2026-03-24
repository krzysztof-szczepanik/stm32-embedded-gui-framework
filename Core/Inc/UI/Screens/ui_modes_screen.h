#ifndef UI_MODES_SCREEN_H
#define UI_MODES_SCREEN_H

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

    // Widegty - sector:
	ui_list_item_t list_item_time;
	ui_list_item_t list_item_rpm;
	ui_list_item_t list_item_temp;

	// Widgety - footer:
    ui_button_t button_back;
    ui_button_t button_apply;
} ui_modes_screen_t;



// =================== CONSTRUCTOR ===================

void ui_modes_screen_init(ui_modes_screen_t* modes_screen);



// ================ VIRTUAL FUNCTIONS ================

void ui_modes_screen_update_data(ui_screen_t* screen);



// ===================== MACROS ======================

// Rzutowanie:
#define MODES_SCREEN(screen) ((ui_modes_screen_t*)(screen))

#endif /* UI_MODES_SCREEN_H */
