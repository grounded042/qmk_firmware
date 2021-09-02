#pragma once

#include <raw_hid.h>


enum ctrl_hid_codes {
    // Signals end of message. Not really that useful.
    CTRL_HID_EOM = 0x00,
    CTRL_HID_OK,
    CTRL_HID_NOK,

    /**
     * to hid: CTRL_HID_LED, led_id, r, g, b
     * from hid: CTRL_HID_LED, CTRL_HID_OK, CTRL_HID_EOM
     * on error: CTRL_HID_LED, CTRL_HID_NOK, num_leds, CTRL_HID_EOM
     *
     * Sets the specific led to r, g, b. It's only visible when the hid_effect mode is active.
     **/
    CTRL_HID_LED,
};

// used to send data back
extern uint8_t raw_hid_buffer[RAW_EPSIZE];

// Defined in rgb_matrix_user.inc
// It's 119 for Massdrop CTRL, 0 - 118.
extern RGB rgb_matrix_led_state[DRIVER_LED_TOTAL];

// Defined in keymap.c
extern uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3];

void raw_hid_perform_send(void);
