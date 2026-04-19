// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _DEAD 50

#define _DOWN_TRESHOLD (0+_DEAD)
#define _UP_TRESHOLD (0-_DEAD)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌────┬────┬────┬────┬────┬────┐
     * │  7 │  8 │  9 │  0 │  - │  = │
     * ├────┼────┼────┼────┼────┼────┤
     * │ Tab│ F1 │ F2 │ F3 │ F4 │ End│
     * ├────┼────┼────┼────┼────┼────┤
     * │  ^ │ F5 │ F6 │ F7 │ F8 │ Del│
     * ├────┼────┼────┼────┼────┼────┤
     * │Ctrl│ F9 │ F10│ F11│ F12| Ins│
     * └────┴────┴────┴────┴────┴────┘
     */
    [0] = LAYOUT(
        KC_7,      KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,
        KC_TAB,    KC_F1,   KC_F2,   KC_F3,    KC_F4,    KC_END,
        KC_LSFT,   KC_F5,   KC_F6,   KC_F7,    KC_F8,    KC_DEL,
        KC_LCTL,   KC_F9,   KC_F10,  KC_F11,   KC_F12,   KC_INS
    )
};


joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(F4, 0, 512, 1023),
    JOYSTICK_AXIS_IN(F5, 0, 512, 1023)
};

    int16_t xPos = 0;
    int16_t yPos = 0;

    bool yDownHeld = false;
    bool yUpHeld = false;
    bool xLeftHeld = false;
    bool xRightHeld = false;

    void matrix_scan_user(void){
        yPos = joystick_read_axis(1);
        if (!yDownHeld && yPos >= _DOWN_TRESHOLD) {
            register_code(KC_UP);
            yDownHeld = true;
        } else if (yDownHeld && yPos <= _DOWN_TRESHOLD) {
            yDownHeld = false;
            unregister_code(KC_UP);
        } else if (!yUpHeld && yPos <= _UP_TRESHOLD){
            yUpHeld = true;
            register_code(KC_DOWN);
        }  else if (yUpHeld && yPos > _UP_TRESHOLD){
            yUpHeld = false;
            unregister_code(KC_DOWN);
        }

        xPos = joystick_read_axis(0);
        if (!xLeftHeld && xPos >= _DOWN_TRESHOLD) {
            register_code(KC_RGHT);
            xLeftHeld = true;
        } else if (xLeftHeld && xPos < _DOWN_TRESHOLD) {
            xLeftHeld = false;
            unregister_code(KC_RGHT);
        } else if (!xRightHeld && xPos <= _UP_TRESHOLD){
            xRightHeld = true;
            register_code(KC_LEFT);
        }  else if (xRightHeld && xPos > _UP_TRESHOLD){
            xRightHeld = false;
            unregister_code(KC_LEFT);
        }
    }