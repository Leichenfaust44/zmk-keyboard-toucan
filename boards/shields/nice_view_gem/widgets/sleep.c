#include <zephyr/kernel.h>
#include <stdio.h>
#include <string.h>

#include "sleep.h"
#include "../assets/custom_fonts.h"

static bool show_sleep_screen = false;

/* Zero Two animation frames — defined in art.c */
extern const lv_img_dsc_t zero_two_0;
extern const lv_img_dsc_t zero_two_1;
extern const lv_img_dsc_t zero_two_2;
extern const lv_img_dsc_t zero_two_3;
extern const lv_img_dsc_t zero_two_4;
extern const lv_img_dsc_t zero_two_5;
extern const lv_img_dsc_t zero_two_6;
extern const lv_img_dsc_t zero_two_7;
extern const lv_img_dsc_t zero_two_8;
extern const lv_img_dsc_t zero_two_9;
extern const lv_img_dsc_t zero_two_10;
extern const lv_img_dsc_t zero_two_11;
extern const lv_img_dsc_t zero_two_12;
extern const lv_img_dsc_t zero_two_13;
extern const lv_img_dsc_t zero_two_14;
extern const lv_img_dsc_t zero_two_15;
extern const lv_img_dsc_t zero_two_16;
extern const lv_img_dsc_t zero_two_17;
extern const lv_img_dsc_t zero_two_18;
extern const lv_img_dsc_t zero_two_19;

static const lv_img_dsc_t *zero_two_frames[] = {
    &zero_two_0, &zero_two_1, &zero_two_2, &zero_two_3, &zero_two_4,
    &zero_two_5, &zero_two_6, &zero_two_7, &zero_two_8, &zero_two_9,
    &zero_two_10, &zero_two_11, &zero_two_12, &zero_two_13, &zero_two_14,
    &zero_two_15, &zero_two_16, &zero_two_17, &zero_two_18, &zero_two_19,
};
#define ZERO_TWO_FRAME_COUNT 20

static lv_obj_t *anim_img_obj = NULL;

bool is_sleep_screen_active(void) {
    return show_sleep_screen;
}

void set_sleep_screen_active(bool active) {
    show_sleep_screen = active;

    if (anim_img_obj != NULL) {
        if (active) {
            lv_obj_clear_flag(anim_img_obj, LV_OBJ_FLAG_HIDDEN);
            lv_animimg_set_repeat_count(anim_img_obj, LV_ANIM_REPEAT_INFINITE);
            lv_animimg_start(anim_img_obj);
        } else {
            lv_animimg_set_repeat_count(anim_img_obj, 0);
            lv_obj_add_flag(anim_img_obj, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

void draw_sleep_screen(lv_obj_t *canvas) {
    // Sleep screen is handled by the animimg overlay — nothing to draw on canvas.
    // The canvas is left blank (filled black by fill_background in screen.c).
}

void init_sleep_animation(lv_obj_t *parent) {
    // Frames are 87x64px, display is 144px wide.
    // Center horizontally: (144 - 87) / 2 = 28
    // Center vertically: (168 - 64) / 2 = 52
    anim_img_obj = lv_animimg_create(parent);
    lv_animimg_set_src(anim_img_obj, (const void **)zero_two_frames, ZERO_TWO_FRAME_COUNT);
    lv_animimg_set_duration(anim_img_obj, 2000);
    lv_animimg_set_repeat_count(anim_img_obj, LV_ANIM_REPEAT_INFINITE);
    lv_obj_set_pos(anim_img_obj, 0, 0);
    lv_obj_add_flag(anim_img_obj, LV_OBJ_FLAG_HIDDEN); // hidden until sleep
}
