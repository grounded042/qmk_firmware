// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(HID)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

RGB rgb_matrix_led_state[DRIVER_LED_TOTAL];

#define ORANGE {RGB_ORANGE}
#define WHITE {RGB_WHITE}
#define RED {RGB_RED}

#ifdef _______
#undef _______
#define _______ {0, 0, 0}

uint8_t ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = {
        WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
        WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
        WHITE, WHITE, RED, WHITE, RED, WHITE, RED, WHITE, RED, RED, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
        WHITE, WHITE, RED, RED, RED, WHITE, RED, WHITE, RED, WHITE, RED, WHITE, WHITE,
        WHITE, WHITE, RED, WHITE, RED, WHITE, RED, WHITE, RED, RED, WHITE, WHITE, WHITE,
        WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE
    },
};

#undef _______
#define _______ KC_TRNS
#endif

char rgb_position(char r, char g, char b, int pos) {
    switch (pos) {
        case 0:
            return r;
        case 1:
            return g;
        case 2:
            return b;
    }

    return 0x00;
}

static void HID_init(effect_params_t* params) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        RGB rgb = {
            .r = ledmap[0][i][0],
            .g = ledmap[0][i][1],
            .b = ledmap[0][i][2],
        };
        if (rgb.r || rgb.g || rgb.b) {
            rgb_matrix_led_state[i] = rgb;
            // rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    // rgb_matrix_led_state[0].r = rgb_position(RGB_RED, 0);
    // rgb_matrix_led_state[0].g = rgb_position(RGB_RED, 1);
    // rgb_matrix_led_state[0].b = rgb_position(RGB_RED, 2);
}

static bool HID_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i,
            rgb_matrix_led_state[i].r,
            rgb_matrix_led_state[i].g,
            rgb_matrix_led_state[i].b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

static bool HID(effect_params_t* params) {
     if (params->init) HID_init(params);
     return HID_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
