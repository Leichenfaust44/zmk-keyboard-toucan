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
#define FRAME_INTERVAL_MS 100

static lv_obj_t *img_obj = NULL;
static int current_frame = 0;

// Work item — runs in system work queue, safe for LVGL
static void anim_work_handler(struct k_work *work);
static K_WORK_DEFINE(anim_work, anim_work_handler);

static void anim_work_handler(struct k_work *work) {
    if (!show_sleep_screen || img_obj == NULL) {
        return;
    }
    current_frame = (current_frame + 1) % ZERO_TWO_FRAME_COUNT;
    lv_img_set_src(img_obj, zero_two_frames[current_frame]);
    lv_refr_now(NULL);
}

// Timer only submits work — never touches LVGL directly
static void animation_timer_cb(struct k_timer *timer) {
    k_work_submit(&anim_work);
}

K_TIMER_DEFINE(sleep_anim_timer, animation_timer_cb, NULL);

bool is_sleep_screen_active(void) {
    return show_sleep_screen;
}

void set_sleep_screen_active(bool active) {
    show_sleep_screen = active;

    if (img_obj == NULL) {
        return;
    }

    if (active) {
        current_frame = 0;
        lv_img_set_src(img_obj, zero_two_frames[0]);
        lv_obj_clear_flag(img_obj, LV_OBJ_FLAG_HIDDEN);
        lv_refr_now(NULL);
        k_timer_start(&sleep_anim_timer, K_MSEC(FRAME_INTERVAL_MS), K_MSEC(FRAME_INTERVAL_MS));
    } else {
        k_timer_stop(&sleep_anim_timer);
        k_work_cancel(&anim_work);
        lv_obj_add_flag(img_obj, LV_OBJ_FLAG_HIDDEN);
    }
}

void draw_sleep_screen(lv_obj_t *canvas) {
    // Handled by img_obj overlay — canvas stays black.
}

void init_sleep_animation(lv_obj_t *parent) {
    img_obj = lv_img_create(parent);
    lv_img_set_src(img_obj, zero_two_frames[0]);
    lv_obj_set_pos(img_obj, 0, 0);
    lv_obj_add_flag(img_obj, LV_OBJ_FLAG_HIDDEN);
}
