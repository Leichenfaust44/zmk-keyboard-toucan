#pragma once

#include <lvgl.h>
#include "util.h"

/**
 * Draw a sleep screen showing the keyboard is in sleep mode.
 * In practice this is a no-op — the animation overlay handles display.
 */
void draw_sleep_screen(lv_obj_t *canvas);

/**
 * Check if the sleep screen should be shown.
 */
bool is_sleep_screen_active(void);

/**
 * Set the sleep screen active state.
 * Shows/hides and starts/stops the Zero Two animation.
 */
void set_sleep_screen_active(bool active);

/**
 * Initialize the Zero Two animation overlay.
 * Must be called once during screen init, passing the widget parent object.
 * The animation is hidden until set_sleep_screen_active(true) is called.
 */
void init_sleep_animation(lv_obj_t *parent);
