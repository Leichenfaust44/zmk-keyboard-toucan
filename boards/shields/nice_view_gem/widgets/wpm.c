#include <zephyr/kernel.h>
#include "wpm.h"

void draw_wpm_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_rect_dsc_t rect_white_dsc;
    init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);
    lv_draw_rect_dsc_t rect_black_dsc;
    init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);

    // Hintergrund des WPM-Bereichs löschen
    lv_canvas_draw_rect(canvas, 0, 47, SCREEN_WIDTH, 30, &rect_black_dsc);

    // 10 Balken, je 13px breit, 1px Abstand, max Höhe 28px
    // Gesamtbreite: 10*13 + 9*1 = 139px, zentriert auf 144px → x-offset = 2
    for (int i = 0; i < 10; i++) {
        uint8_t wpm = state->wpm[i];
        if (wpm > 100) wpm = 100;

        int bar_h = (wpm * 28) / 100;
        if (bar_h < 1 && wpm > 0) bar_h = 1;

        // Balken wachsen von unten (y=77) nach oben
        lv_canvas_draw_rect(canvas,
            2 + i * 14,     // x: 2px offset, je 14px (13px Balken + 1px Abstand)
            77 - bar_h,     // y: von unten wachsend
            13,             // breite
            bar_h,          // höhe
            &rect_white_dsc);
    }
}
