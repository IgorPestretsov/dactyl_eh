// Copyright 2021 Andrzej Kotulski (@akotulski)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define THIRD MO(_THIRD)
#define MOUSE MO(_MOUSE)

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _MOUSE,
    _THIRD

};

enum custom_keycodes {
    ACEJUMP_PYCHARM = SAFE_RANGE,
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ACEJUMP_PYCHARM:
        if (record->event.pressed) {
            register_code(KC_SPACE);
            unregister_code(KC_SPACE);
            register_code(KC_SPACE);
            unregister_code(KC_SPACE);
            register_code(KC_S);
            unregister_code(KC_S);
        } else {
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (qwerty)
     * +-----------------------------------------+                             +-----------------------------------------+
     * | ESC  |   q  |   w  |   e  |   r  |   t  |                             |   y  |   u  |   i  |   o  |   p  |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | TAB  |   a  |   s  |   d  |   f  |   g  |                             |   h  |   j  |   k  |   l  |   ;  |      |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | SHFT |   z  |   x  |   c  |   v  |   b  |                             |:w   n  |   m  |   ,  |   .  |   /  |      |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |  [   |   ]  |                                                         |      |      |
     *               +-------------+-------------+                             +-------------+-------------+
     *                             |      |      |                             |      |      |
     *                             |------+------|                             |------+------|
     *                             |      |      |                             |      |      |
     *                             +-------------+                             +-------------+
     *                                           +-------------+ +-------------+
     *                                           |      |      | |      |      |
     *                                           |------+------| |------+------|
     *                                           |      |      | |      |      |
     *                                           +-------------+ +-------------+
     */
    [_BASE] = LAYOUT(
        LGUI(KC_S),      KC_Q,    KC_W,      KC_E,       KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,         KC_O,       KC_P,       KC_BSLASH,
        LCTL(KC_TAB),    KC_A,    KC_S,      KC_D,       KC_F,    KC_G,                                          KC_H,    KC_J,    KC_K,         KC_L,       KC_SCLN,    KC_QUOT,
        RCTL(KC_GRAVE),  KC_Z,    KC_X,      KC_C,       KC_V,    KC_B,                                          KC_N,    KC_M,    KC_COMM,      KC_DOT,     KC_SLSH,    LT(MOUSE, OSM(MOD_MEH)),
                                  KC_GRAVE,  OSM(MOD_LCTL),                                                                        KC_LBRACKET,  KC_RBRACKET,
                                            KC_SPC,         LSFT_T(KC_DELETE),   LT(LOWER, KC_TAB),              LT(THIRD, KC_ESC),     LT(RAISE, KC_ENTER),      RSFT_T(KC_BSPACE),
                                            OSM(MOD_HYPR) , RESET,                                               RESET,    KC_LGUI
    ),

    [_LOWER] = LAYOUT(
        _______,    KC_PGDOWN,      KC_PGUP,        KC_INSERT,      KC_HOME,        KC_END,                       KC_RBRC,      KC_7,       KC_8,       KC_9,       _______,        _______,
        _______,    RCTL(KC_KP_1),  RCTL(KC_KP_2),  RCTL(KC_KP_3),  RCTL(KC_KP_4) , RCTL(KC_KP_5),                _______,      KC_4,       KC_5,       KC_6,       _______,        _______,
        _______,    RCTL(KC_KP_6),  KC_LALT,        KC_LCTL,        RCTL(KC_KP_7),  RCTL(KC_KP_8),                _______,      KC_1,       KC_2,       KC_3,       _______,        _______,
                                    _______,        _______,                                                                                KC_0,       KC_DOT,
                                                    _______,        _______,        _______,                      _______,      _______,    _______,
                                                    _______,        _______,                                                    _______,    _______
    ),

    [_RAISE] = LAYOUT(
        _______,        KC_EQUAL,       LSFT(KC_EQUAL),         _______,         _______,        _______,                     _______,        _______,        _______,        KC_MINUS,       LSFT(KC_MINUS),     _______,
        _______,        LSFT(KC_1),     LSFT(KC_2),             LSFT(KC_3),      LSFT(KC_4),     LSFT(KC_5),                  LSFT(KC_6),     LSFT(KC_7),     LSFT(KC_8),     LSFT(KC_9),     LSFT(KC_0),         _______,
        _______,        KC_F1,          KC_F2,                  KC_F3,           KC_F4,          KC_F5,                       KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,             KC_VOLD,
                                        _______, _______,                                                                                                     KC_F11,  KC_F12,
                                  _______, _______,  _______,                                                                    _______, _______, _______,
                                            _______, _______,                                                                    _______, _______
    ),

    [_THIRD] = LAYOUT(
        RGB_MODE_RAINBOW,       _______,        LGUI(KC_W) ,        _______,        _______,        RCS(KC_UP),                      LSA(KC_F10),       LSA(KC_F9),         KC_CAPSLOCK,        _______,         _______,       KC_VOLU,
        KC_MS_UP,               _______,        _______,            _______,        _______,        RCS(KC_DOWN),                    KC_LEFT,           KC_DOWN,            KC_UP,              KC_RIGHT,        _______,       KC_MUTE,
        _______,                _______,        LGUI(KC_X),         _______,        _______,        _______,                         RALT(KC_HOME),     KC_APPLICATION,     KC_RCTRL,           KC_RALT,         _______,       KC_VOLD,
                                                _______,            _______,                                                                                                RCS(KC_F12),        _______,
                                                _______,            _______,        ACEJUMP_PYCHARM,                                 _______,           _______,            _______,
                                                _______,            _______,                                                         _______,           _______

    ),


    [_MOUSE] = LAYOUT(
        _______, _______, _______, KC_MS_UP, _______, _______,               _______, _______, KC_MS_UP, _______,  _______, _______,
        _______, _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______,      _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______,_______,
        _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, TG(MOUSE),
                          _______, _______,                                                    _______,  _______,
                                  _______, KC_MS_BTN1,  KC_MS_BTN2,             KC_ACL0, KC_ACL1, KC_ACL2,
                                            KC_MS_WH_UP, KC_MS_WH_DOWN,                   _______, _______

    ),
};

