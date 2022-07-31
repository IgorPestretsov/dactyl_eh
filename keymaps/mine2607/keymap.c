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
    PAST_FROM_ZERO_VIM,
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
    case PAST_FROM_ZERO_VIM:
        if (record->event.pressed) {
            register_code(KC_LSFT);
            register_code(KC_QUOT);
            unregister_code(KC_QUOT);
            unregister_code(KC_LSFT);
            register_code(KC_0);
            unregister_code(KC_0);
            register_code(KC_P);
            unregister_code(KC_P);
        } else {
        }
        break;
    }
    return true;
};

typedef enum {
            TD_NONE,
            TD_UNKNOWN,
            TD_SINGLE_TAP,
            TD_SINGLE_HOLD,
            TD_DOUBLE_TAP,
            TD_DOUBLE_HOLD,
            TD_DOUBLE_SINGLE_TAP, // Send two single taps
            TD_TRIPLE_TAP,
            TD_TRIPLE_HOLD
        } td_state_t;
        typedef struct {
            bool is_press_action;
            td_state_t state;
        } td_tap_t;

        // Tap dance enums
        enum {
                console,
                gui_shortcut
        };

        td_state_t cur_dance(qk_tap_dance_state_t *state);

        // For the x tap dance. Put it here so it can be used in any keymap

        void tild_finished(qk_tap_dance_state_t *state, void *user_data);
        void tild_reset(qk_tap_dance_state_t *state, void *user_data);

        void gui_finished(qk_tap_dance_state_t *state, void *user_data);
        void gui_reset(qk_tap_dance_state_t *state, void *user_data);

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
        TD(gui_shortcut),      KC_Q,    KC_W,      KC_E,       KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,         KC_O,       KC_P,       KC_BSLASH,
        LCTL(KC_TAB),    KC_A,    KC_S,      KC_D,       KC_F,    KC_G,                                          KC_H,    KC_J,    KC_K,         KC_L,       KC_SCLN,    KC_QUOT,
        TD(console),  KC_Z,    KC_X,      KC_C,       KC_V,    KC_B,                                          KC_N,    KC_M,    KC_COMM,      KC_DOT,     KC_SLSH,    LT(MOUSE, OSM(MOD_MEH)),
                                  KC_GRAVE,  OSM(MOD_LCTL),                                                                        KC_LBRACKET,  KC_RBRACKET,
                                            KC_SPC,         LSFT_T(KC_DELETE),   LT(LOWER, KC_TAB),              LT(THIRD, KC_ESC),     LT(RAISE, KC_ENTER),      RSFT_T(KC_BSPACE),
                                            OSM(MOD_HYPR) , _______,                                             _______,    KC_LGUI
    ),

    [_LOWER] = LAYOUT(
        RESET,      KC_PGDOWN,      KC_PGUP,        KC_INSERT,      KC_HOME,        KC_END,                       KC_RBRC,      KC_7,       KC_8,       KC_9,       _______,        RESET,
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
        RGB_MODE_RAINBOW,       _______,        LGUI(KC_W) ,        _______,        _______,        _______,                      LSA(KC_F10),       LSA(KC_F9),         KC_CAPSLOCK,        _______,         PAST_FROM_ZERO_VIM,       KC_VOLU,
        KC_MS_UP,               _______,        _______,            _______,        _______,        _______,                      KC_LEFT,           KC_DOWN,            KC_UP,              KC_RIGHT,        _______,       KC_MUTE,
        _______,                _______,        LGUI(KC_X),         _______,        _______,        _______,                      RALT(KC_HOME),     KC_APPLICATION,     KC_RCTRL,           KC_RALT,         _______,       KC_VOLD,
                                                _______,            _______,                                                                                                RCS(KC_F12),        _______,
                                                _______,            _______,        ACEJUMP_PYCHARM,                                 _______,           _______,            _______,
                                                _______,            _______,                                                         _______,           _______

    ),


    [_MOUSE] = LAYOUT(
        _______, _______, _______, KC_MS_UP, _______, _______,               _______, _______, _______, _______,  _______, _______,
        _______, _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______,      _______, _______, _______, _______, _______,_______,
        _______, _______, _______, _______, _______, _______,                _______, _______, _______, _______, _______, _______,
                          _______, _______,                                                    _______,  _______,
                                  _______, KC_MS_BTN1,  KC_MS_BTN2,             KC_ACL0, KC_ACL1, KC_ACL2,
                                            KC_MS_WH_UP, KC_MS_WH_DOWN,                   _______, _______

    ),
};
            qk_tap_dance_action_t tap_dance_actions[] = {
                [console] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tild_finished, tild_reset),
                [gui_shortcut] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gui_finished, gui_reset),

            };


        td_state_t cur_dance(qk_tap_dance_state_t *state) {
            if (state->count == 1) {
                if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
                // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
                else return TD_SINGLE_HOLD;
            } else if (state->count == 2) {
                // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
                // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
                // keystrokes of the key, and not the 'double tap' action/macro.
                if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
                else if (state->pressed) return TD_DOUBLE_HOLD;
                else return TD_DOUBLE_TAP;
            }

            // Assumes no one is trying to type the same letter three times (at least not quickly).
            // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
            // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and defiGne that enum just like 'TD_DOUBLE_SINGLE_TAP'
            if (state->count == 3) {
                if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
                else return TD_TRIPLE_HOLD;
            } else return TD_UNKNOWN;
        }

        // Create an instance of 'td_tap_t' for the 'x' tap dance.

        static td_tap_t tildtap_state = {
            .is_press_action = true,
            .state = TD_NONE
        };

        static td_tap_t gui_state = {
            .is_press_action = true,
            .state = TD_NONE
        };
        void tild_finished(qk_tap_dance_state_t *state, void *user_data) {
                tildtap_state.state = cur_dance(state);
                switch (tildtap_state.state) {
                case TD_SINGLE_TAP: register_code(KC_RCTL); register_code(KC_GRAVE); break;
                case TD_NONE:  break;
                case TD_UNKNOWN:  break;
                case TD_TRIPLE_TAP: break;
                case TD_TRIPLE_HOLD: break;
                case TD_SINGLE_HOLD: register_code(KC_F12); break;
                case TD_DOUBLE_TAP:  break;
                case TD_DOUBLE_HOLD:  break;
                // Last case is for fast typing. Assuming your key is `f`:
                // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
                // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
                case TD_DOUBLE_SINGLE_TAP: break;
            }
        }

        void tild_reset(qk_tap_dance_state_t *state, void *user_data) {
                switch (tildtap_state.state) {
                case TD_SINGLE_TAP: unregister_code(KC_RCTL);unregister_code(KC_GRAVE); break;
                case TD_NONE:  break;
                case TD_UNKNOWN:  break;
                case TD_TRIPLE_TAP: break;
                case TD_TRIPLE_HOLD: break;
                case TD_SINGLE_HOLD: unregister_code(KC_F12); break;
                case TD_DOUBLE_TAP:  break;
                case TD_DOUBLE_HOLD: break;
                case TD_DOUBLE_SINGLE_TAP: break;
            }
                tildtap_state.state = TD_NONE;
        }

        void gui_finished(qk_tap_dance_state_t *state, void *user_data) {
                gui_state.state = cur_dance(state);
                switch (gui_state.state) {
                case TD_SINGLE_TAP: register_code(KC_LGUI); register_code(KC_SPC); break;
                case TD_NONE:  break;
                case TD_UNKNOWN:  break;
                case TD_TRIPLE_TAP: break;
                case TD_TRIPLE_HOLD: break;
                case TD_SINGLE_HOLD: register_code(KC_LGUI); register_code(KC_S); break;
                case TD_DOUBLE_TAP:  break;
                case TD_DOUBLE_HOLD:  break;
                // Last case is for fast typing. Assuming your key is `f`:
                // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
                // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
                case TD_DOUBLE_SINGLE_TAP: break;
            }
        }

        void gui_reset(qk_tap_dance_state_t *state, void *user_data) {
                switch (gui_state.state) {
                case TD_SINGLE_TAP: unregister_code(KC_LGUI);unregister_code(KC_SPC); break;
                case TD_NONE:  break;
                case TD_UNKNOWN:  break;
                case TD_TRIPLE_TAP: break;
                case TD_TRIPLE_HOLD: break;
                case TD_SINGLE_HOLD: unregister_code(KC_LGUI);unregister_code(KC_S); break;
                case TD_DOUBLE_TAP:  break;
                case TD_DOUBLE_HOLD: break;
                case TD_DOUBLE_SINGLE_TAP: break;
            }
                tildtap_state.state = TD_NONE;
        }
