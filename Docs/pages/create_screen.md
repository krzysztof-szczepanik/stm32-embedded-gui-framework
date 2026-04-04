# Creating a new screen

<br>

## Description
This tutorial explains how to create and integrate a new UI screen into the framework.

A screen in this framework is a structured collection of widgets organized into sections (header, content, footer) and managed by the screen manager.

<br>

Each screen:
- extends `ui_screen_t`
- defines its own widgets
- implements initialization logic
- can optionally react to shared data updates

<br>

> [!NOTE]
> All examples in this tutorial are based on a sample screen named `ui_test_screen`.
> 
> The naming convention, file names, and code snippets follow this example, but you can replace it with any screen name in your project.

<br>

---

## 1. Create screen files

Create two files:

```
Core/Inc/UI/Screens/ui_test_screen.h
Core/Src/UI/Screens/ui_test_screen.c
```

<br>

---

## 2. Define screen structure (.h)

For clarity, this tutorial uses a minimal example screen (`ui_test_screen`) to demonstrate the concepts.  

The example screen includes:
- Three main sections: **header**, **sector**, **footer**
- One **button** inside the vbox container

This keeps the example simple while illustrating how to structure and initialize a screen, add widgets, and integrate it with the screen manager.

<br>

> [!TIP]
> For your convenience, you can start by copying an existing screen (for example: ui_main_screen.h).  
> This makes it easier to create a new screen because you can reuse the structure and initialization logic.
> 
> Be sure to:
> - Update all screen and type names to match your new screen.
> - Modify existing widgets if needed.
> - Add any new widgets specific to your screen.

<br>

> [!NOTE]
> Widgets are stored as struct fields - this is how the framework accesses and manages them.

<br>

### Example Header (`ui_test_screen.h`):

```cpp
#ifndef UI_TEST_SCREEN_H
#define UI_TEST_SCREEN_H

#include "ui_screen.h"
#include "ui_header.h"
#include "ui_footer.h"
#include "ui_vbox.h"
#include "ui_button.h"

// Include only the widgets used by this screen (you may include all for convenience)

typedef struct {
    ui_screen_t base;

    // Sections:
    ui_header_t header;
    ui_footer_t footer;
    ui_vbox_t sector;

    // Header widgets:
    // Add more widgets here

    // Sector widgets:
    ui_button_t button;

    // Footer widgets:
    // Add more widgets here

} ui_test_screen_t;

// Constructor:
void ui_test_screen_init(ui_test_screen_t* test_screen);

// Virtual function:
void ui_test_screen_update_data(ui_screen_t* screen);

// Casting macro:
#define TEST_SCREEN(screen) ((ui_test_screen_t*)(screen))

#endif
```

<br>

> [!IMPORTANT]
> base must exist - required by the framework for every screen.

<br>

---

## 3. Define screen implementation (.c)

This section shows how to implement a minimal screen (`ui_test_screen`) for demonstration purposes.

Typical steps:

1. Initialize the base screen
2. Assign virtual functions
3. Create sections (header, sector, footer)
4. Initialize widgets
5. Add widgets to containers
6. Register containers in the screen

<br>

### Example (`ui_test_screen.c`):

```cpp
#include "ui_test_screen.h"
#include "lcd.h"
#include "tim.h"
#include "ui_screen.h"

void ui_test_screen_init(ui_test_screen_t* test_screen) {
    
    // Initialize base screen:
    ui_screen_t* screen = &test_screen->base;
    ui_screen_init(screen);

    // Assign virtual function:
    screen->base.update_data = ui_test_screen_update_data;

    // Initialize sector container:
    ui_vbox_t* sector = &test_screen->sector;
	ui_vbox_init(sector, 0, 50, LCD_WIDTH, LCD_HEIGHT - 100);

    // Initialize button
    ui_button_t* button = &test_screen->button;
    ui_button_init(button, 10, 10, 100, 50);

    // Add button to sector:
    ui_widget_t* sector_widgets[] = {
        &button->base
	};

	uint8_t sector_widgets_count = sizeof(sector_widgets) / sizeof(sector_widgets[0]);
	ui_vbox_add_widgets(sector, sector_widgets, sector_widgets_count);

    // Add sector to screen:
    ui_widget_t* screen_widgets[] = {
        &sector->base.base
	};

	uint8_t screen_widgets_count = sizeof(screen_widgets) / sizeof(screen_widgets[0]);
	ui_screen_add_widgets(screen, screen_widgets, screen_widgets_count);
}
```

<br>

---

## 4. Register screen ID

Each screen in the framework must have a unique ID.  
This ID is used by the **screen manager** to identify, switch, and manage screens.

<br>

Add your screen to:

```
ui_screens.h
```

Example:

```cpp
typedef enum {
    UI_MAIN_SCREEN,
    UI_MODES_SCREEN,
    UI_SETTINGS_SCREEN,
    UI_TEST_SCREEN,
    UI_COUNT_SCREEN  // do not remove this line
} ui_screen_id_t;
```

<br>

> [!IMPORTANT]
> The UI_COUNT_SCREEN entry helps the framework know the total number of screens. Do not remove it.

<br>

---

## 5. Initialize and register screen (main.c)

**1. Include header:**

```cpp
#include "ui_test_screen.h"
```

<br>

**2. Create and initialize:**

```cpp
static ui_test_screen_t test_screen;
ui_test_screen_init(&test_screen);
```

<br>

**3. Register in screen manager (main.c):**

```cpp
ui_screen_manager_register_screen(UI_TEST_SCREEN, &test_screen.base);
```

<br>

---

## 6. Switch to screen

You can activate the screen using:

```cpp
ui_screen_manager_set_current_screen(&test_screen.base);
```

or:

```cpp
ui_screen_manager_set_current_screen_by_id(UI_TEST_SCREEN);
```

<br>

---

## 7. Advanced / Optional

The sections below are not required, but they are useful for more advanced cases or a better understanding of the framework.

<br>

---

### Global screen access

You can store a global pointer to your screen instance. This allows you to access the screen and its widgets from any function in the same file.  

This is useful for updating widgets from callbacks, timers, or other parts of the code without passing the screen pointer around.

```cpp
// Declare global pointer
static ui_test_screen_t* g_test_screen;

// In init function:
void ui_test_screen_init(ui_test_screen_t* test_screen) {
    g_test_screen = test_screen; // store global pointer
    
    ui_screen_t* screen = &test_screen->base;
    ui_screen_init(screen);

    screen->base.update_data = ui_test_screen_update_data;

    // etc.
}
```

<br>

---

### Shared data handling

If your screen needs to react to shared state changes:

- implement `update_data()`
- assign it in constructor:

```cpp
screen->base.update_data = ui_test_screen_update_data;
```

<br>

#### Example:

```cpp
void ui_test_screen_update_data() {
    ui_test_screen_t* test_screen = g_test_screen;

    ui_button_t* button = &test_screen->button;

    // Update button label based on a shared variable:
    if (ui_screens_data.some_flag) {
        ui_button_label(button).text = "ON";
    } else {
        ui_button_label(button).text = "OFF";
    }

    // We synchronized the screen state with the shared data by ui_screens_data,
	// so we need to mark the current screen as invalidated.
	// This tells the render loop that the screen has changed and must be redrawn.
	// Without this, widget value updates may stay in memory and not appear on the LCD.
    ui_screen_manager_get_current_screen()->base.invalidated = true;
}
```

<br>

---

### Handling input (callbacks)

Widgets can react to events using callbacks.

Example (button):

```cpp
static bool button_clicked(void) {
    ui_screen_manager_set_current_screen_by_id(UI_MAIN_SCREEN);
    return true;
}
```

Assign callback:

```cpp
ui_button_t* button = &test_screen->button;
button_on_click(button) = button_clicked;
```

<br>

> [!IMPORTANT]
> It is necessary to include:
> - stdbool.h // for bool
> - ui_screen_manager.h // for ui_screen_manager_set_current_screen_by_id()

<br>

---

## 8. Extra

### Screen Manager - how it works

The screen manager:

- stores all screens in an internal registry
- tracks current screen
- routes events to active screen
- calls `update_data()` when needed
- triggers redraw

<br>

Important behavior:

```cpp
ui_screen_manager_set_current_screen(...)
```

- sets current screen
- calls `update_data()`
- resets navigation direction
- focuses first widget

<br>

---