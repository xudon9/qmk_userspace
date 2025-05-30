/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
1. nav mods in symbol layer? why?
*/

#include <stdint.h>

#include "action.h"
#include "action_layer.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "modifiers.h"
#include "quantum.h"
#include QMK_KEYBOARD_H
#include "layout.h"

enum layers {
    L_BASE,
    L_SYM,
    L_NAV,
    L_NUM,
    L_WIN,
    L_FUN,
    L_EXT,
};

enum custom_keycodes {
    ARROW = SAFE_RANGE,
    UPDIR,
    STDCC,
    USRNAME,
    TMUXESC,
    SRCHSEL,
    RGBNEXT,
    RGBHUP,
    RGBHRND,
    RGBDEF1,
    RGBDEF2,
    // Macros invoked through the Magic key.
    // M_DOCSTR,
    // M_EQEQ,
    // M_INCLUDE,
    // M_ION,
    // M_MENT,
    // M_MKGRVS,
    // M_QUEN,
    // M_THE,
    // M_TMENT,
    // M_UPDIR,
    // M_NBSP,
    // M_NOOP,
};

#define HR_A LALT_T(KC_A)
#define HR_S LT(L_SYM, KC_S)
#define HR_D LSFT_T(KC_D)
#define HR_F LT(L_NAV, KC_F)
#define HR_V LCTL_T(KC_V)
#define HR_Z LGUI_T(KC_Z)

#define HR_J LT(L_NUM, KC_J)
#define HR_K RSFT_T(KC_K)
#define HR_L LT(L_SYM, KC_L)
#define HR_SCLN RALT_T(KC_SCLN)
#define HR_M RCTL_T(KC_M)
#define HR_DOT LT(L_WIN, KC_DOT)
#define HR_SLSH RGUI_T(KC_SLSH)
#define EX_COL LT(L_EXT, KC_SCLN)

#define C_PGUP C(KC_PGUP)
#define C_PGDN C(KC_PGDN)
#define G_TAB G(KC_TAB)     // GUI+Tab
#define G_ENT G(KC_ENT)     // GUI+Enter
#define A_TAB A(KC_TAB)     // Alt+Tab
#define SA_TAB S(A(KC_TAB)) // Shift+Alt+Tab

#define KC_TODO _______ // Placeholder for TODO key
#define SELLINE _______ // Placeholder for selection line key

#define EXT_UNDS KC_UNDS // LT(L_EXT, KC_UNDS)

// clang-format off
#define LAYOUT_LR_THUMB(                \
    k00, k01, k02, k03, k04, k05, k06,  \
    k10, k11, k12, k13, k14, k15, k16,  \
    k20, k21, k22, k23, k24, k25,       \
                                        \
    k46, k45, k44, k43, k42, k41, k40,  \
    k56, k55, k54, k53, k52, k51, k50,  \
         k65, k64, k63, k62, k61, k60,  \
    k33, k34, k35,       k75, k74, k73) \
         LAYOUT_split_3x6_3_ex2(                                            \
    k00, k01, k02, k03, k04, k05, k06, k46, k45, k44, k43, k42, k41, k40,   \
    k10, k11, k12, k13, k14, k15, k16, k56, k55, k54, k53, k52, k51, k50,   \
    k20, k21, k22, k23, k24, k25,           k65, k64, k63, k62, k61, k60,   \
                   k33, k34, k35,           k75, k74, k73)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT_LR_THUMB(
        KC_GRV , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_MINS,
        KC_TAB , HR_A   , HR_S   , HR_D   , HR_F   , KC_G   , KC_EQL ,
        EX_COL , HR_Z   , KC_X   , KC_C   , HR_V   , KC_B   ,

        KC_LBRC, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        KC_RBRC, KC_H   , HR_J   , HR_K   , HR_L   , HR_SCLN, KC_QUOT,
                 KC_N   , HR_M   , KC_COMM, HR_DOT , HR_SLSH, _______,

        KC_UNDS, KC_ESC , KC_SPC ,          KC_ENT , KC_BSPC, LT(L_NAV, KC_0)
    ),

    [L_SYM] = LAYOUT_LR_THUMB(
        TMUXESC, KC_GRV , KC_LABK, KC_RABK, KC_MINS, KC_PIPE, _______,
        KC_LCTL, KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL , KC_AMPR, _______,
        STDCC  , KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC,

        _______, KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR , KC_TODO, _______,
        _______, KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_DQUO, KC_RCTL,
                 KC_AT  , KC_COLN, KC_COMM, KC_DOT , KC_QUOT, _______,

        _______, USRNAME, _______,          _______, _______, _______
    ),

    [L_NAV] = LAYOUT_LR_THUMB(
        _______, KC_WREF, C_PGUP , C_PGDN , XXXXXXX, XXXXXXX, _______,
        _______, KC_LALT, KC_LCTL, KC_LSFT, SELLINE, MS_BTN1, _______,
        _______, KC_LGUI, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX,

        _______, KC_PGUP, KC_HOME,   KC_UP,  KC_END, SRCHSEL, _______,
        _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , KC_BSLS,
                 KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,

        _______, KC_WBAK,  G_TAB ,           _______, QK_LLCK, _______
    ),

    [L_NUM] = LAYOUT_LR_THUMB(
        _______, KC_SLSH,    KC_9,    KC_8,    KC_7, KC_ASTR, _______,
        _______, KC_MINS,    KC_3,    KC_2,    KC_1, KC_PLUS, _______,
        _______, KC_X   ,    KC_6,    KC_5,    KC_4, KC_PERC,

        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, KC_E   , KC_RCTL, KC_LALT, _______,
                 XXXXXXX, XXXXXXX, KC_COMM, KC_DOT , KC_LGUI, _______,

        _______, _______, _______,          KC_0   , QK_LLCK, _______
    ),

    [L_WIN] = LAYOUT_LR_THUMB(
        _______, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, _______,
        _______, XXXXXXX, G(KC_3), G(KC_2), G(KC_1), G(KC_D), _______,
        _______, XXXXXXX, G(KC_6), G(KC_5), G(KC_4), G(KC_W),

        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, XXXXXXX, KC_RSFT, XXXXXXX, KC_LALT, XXXXXXX,
                 XXXXXXX, SA_TAB , A_TAB  , XXXXXXX, XXXXXXX, G_ENT  ,

        _______, _______, _______,          _______, QK_LLCK, _______
    ),

    [L_FUN] = LAYOUT_LR_THUMB(
        XXXXXXX, KC_F12 , KC_F9  , KC_F8  , KC_F7  , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_F10 , KC_F3  , KC_F2  , KC_F1  , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_F11 , KC_F6  , KC_F5  , KC_F4  , XXXXXXX,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RGUI, QK_RBT ,

        _______, _______, DB_TOGG,          _______, QK_LLCK, _______
    ),

    [L_EXT] = LAYOUT_LR_THUMB(
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______, _______,

        _______, _______, _______,          _______, QK_LLCK, _______
    )

    // [1] = LAYOUT_LR_THUMB(
    //     _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______,

    //     _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______,
    //              _______, _______, _______, _______, _______, _______,

    //     _______, _______, _______,          _______, _______, _______
    // ),
};
// clang-format on

bool is_layer_locked(uint8_t layer) {
    // Check if the layer is locked by checking if the layer bit is set in the
    // layer state.
    return (bool)(layer_state & ((layer_state_t)0x1 << layer));
}

///////////////////////////////////////////////////////////////////////////////
// User macro callbacks (https://docs.qmk.fm/feature_macros)
///////////////////////////////////////////////////////////////////////////////

const uint16_t caps_combo[] PROGMEM = {KC_C, KC_COMM, COMBO_END};
const uint16_t fn_combo[] PROGMEM   = {KC_H, HR_J, COMBO_END};
combo_t        key_combos[]         = {
    COMBO(caps_combo, CW_TOGG),  // C and , => Activate Caps Word
    COMBO(fn_combo, OSL(L_FUN)), // H and J => L_FUN Layer
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Track whether the left home ring and index keys are held, ignoring layer.
    static bool left_home_ring_held  = false;
    static bool left_home_index_held = false;
    if (record->event.key.row == LEFT_HOME_ROW) {
        switch (record->event.key.col) {
        case LEFT_HOME_RING_COL:
            left_home_ring_held = record->event.pressed;
            break;
        case LEFT_HOME_INDEX_COL:
            left_home_index_held = record->event.pressed;
            break;
        }

        // NAV stays on while layer locked or while either ring or index is held.
        if (!(is_layer_locked(L_NAV) || left_home_ring_held || left_home_index_held)) {
            layer_off(L_NAV);
        }
    }

    const uint8_t mods     = get_mods();
    const uint8_t all_mods = (mods | get_weak_mods()
#ifndef NO_ACTION_ONESHOT
                              | get_oneshot_mods()
#endif // NO_ACTION_ONESHOT
    );
    const uint8_t shift_mods = all_mods & MOD_MASK_SHIFT;
    const bool    alt        = all_mods & (MOD_BIT_LALT | MOD_BIT_RALT);
    switch (keycode) {
    case EX_COL:
        if (record->tap.count) {
            if (record->event.pressed) {
                if (shift_mods) {
                    del_weak_mods(MOD_MASK_SHIFT);
                    unregister_mods(MOD_MASK_SHIFT);
                    tap_code_delay(KC_SCLN, TAP_CODE_DELAY);
                    set_mods(mods);
                } else {
                    tap_code16_delay(KC_COLN, TAP_CODE_DELAY);
                }
            }
            return false;
        }
        return true;
    }

    if (record->event.pressed) {
        switch (keycode) {
        case UPDIR:
            SEND_STRING_DELAY("../", TAP_CODE_DELAY);
            return false;
        case STDCC:
            SEND_STRING_DELAY("std::", TAP_CODE_DELAY);
            return false;
        case TMUXESC:
            // TODO
            return false;
        case USRNAME:
            SEND_STRING_DELAY("xudon9", TAP_CODE_DELAY);
            return false;
        case ARROW: {
            char const *string = alt ? (shift_mods ? "<==>" : "<->") : (shift_mods ? "=>" : "->");
            SEND_STRING_DELAY(string, TAP_CODE_DELAY);
            return false;
        }
        }
    }

    return true;
}
