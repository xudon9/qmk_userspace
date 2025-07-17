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
#include "community_modules.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "modifiers.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

#include "layout.h"

enum layers {
    L_BASE,
    L_ALPHA,
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
    WPASS,
    HPASS,
    SRCHSEL,
    // RGBNEXT,
    // RGBHUP,
    // RGBHRND,
    // RGBDEF1,
    // RGBDEF2,
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

enum keycode_aliases {
    // Short aliases for home row mods
    // HRM: Index fingers
    HRM_F = LT(L_NAV, KC_F),
    HRM_J = LT(L_NUM, KC_J),
    // HRM: Middle fingers
    HRM_D = LSFT_T(KC_D),
    HRM_K = RSFT_T(KC_K),
    // HRM: Ring fingers
    HRM_S = LT(L_SYM, KC_S),
    HRM_L = LT(L_SYM, KC_L),
    // HRM: Pinky fingers
    HRM_A    = LGUI_T(KC_A),
    HRM_SCLN = RGUI_T(KC_SCLN),
    // HRM: Others
    HRM_V = LT(L_EXT, KC_V),
    HRM_M = LT(L_WIN, KC_M),
    //HRM_SLSH = LT(L_FUN, KC_SLSH),

    THMB_L3 = LT(L_NAV, KC_EQL),
    THMB_L2 = LALT_T(KC_MINS),
    THMB_L1 = LCTL_T(KC_SPC),
    THMB_R1 = RCTL_T(KC_ENT),
    THMB_R2 = RALT_T(KC_LBRC),
    THMB_R3 = LT(L_NAV, KC_RBRC),

    C_PGUP = C(KC_PGUP),
    C_PGDN = C(KC_PGDN),
    G_TAB  = G(KC_TAB),    // GUI+Tab
    G_ENT  = G(KC_ENT),    // GUI+Enter
    A_TAB  = A(KC_TAB),    // Alt+Tab
    A_F4   = A(KC_F4),     // Alt+F4
    SA_TAB = S(A(KC_TAB)), // Shift+Alt+Tab
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT_LR_THUMB(
        KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T    , KC_LEFT,
        KC_TAB , HRM_A  , HRM_S  , HRM_D  , HRM_F  , KC_G    , KC_RGHT,
        KC_GRV , KC_Z   , KC_X   , KC_C   , HRM_V  , KC_B    ,

        KC_KP_0, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P    , KC_BSPC,
        KC_COLN, KC_H   , HRM_J  , HRM_K  , HRM_L  , HRM_SCLN, KC_QUOT,
                 KC_N   , HRM_M  , KC_COMM, KC_DOT , KC_SLSH , KC_BSLS,

        THMB_L3, THMB_L2, THMB_L1,          THMB_R1, THMB_R2 , THMB_R3
    ),

    [L_ALPHA] = LAYOUT_LR_THUMB(
        KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T    , KC_LCTL,
        KC_TAB , KC_A   , KC_S   , KC_D   , KC_F   , KC_G    , KC_LSFT,
        KC_GRV , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B    ,

        KC_LALT, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P    , KC_BSPC,
        KC_LGUI, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN , KC_QUOT,
                 KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH , KC_BSLS,

        _______, _______, KC_SPC ,
        KC_ENT , LT(L_NUM, KC_LBRC) , _______
    ),

    [L_SYM] = LAYOUT_LR_THUMB(
        TMUXESC, KC_GRV , KC_LABK, KC_RABK, KC_MINS, KC_PIPE, _______,
        WPASS  , KC_EXLM, KC_ASTR, KC_SLSH, KC_EQL , KC_AMPR, _______,
        STDCC  , KC_TILD, KC_PLUS, KC_LBRC, KC_RBRC, KC_PERC,

        QK_LLCK, KC_CIRC, KC_LCBR, KC_RCBR, KC_DLR , ARROW  , _______,
        _______, KC_HASH, KC_LPRN, KC_RPRN, KC_SCLN, KC_DQUO, HPASS  ,
                 KC_AT  , KC_COLN, KC_COMM, KC_DOT , KC_QUOT, _______,

        _______, _______, USRNAME,          WPASS  , _______, _______
    ),

    [L_NAV] = LAYOUT_LR_THUMB(
        _______, KC_WREF, KC_HOME , KC_UP  , KC_END, KC_PGUP, _______,
        _______, KC_LALT, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
        _______, KC_LGUI, KC_PGUP, KC_PGDN, SELLINE, XXXXXXX,

        QK_LLCK, KC_PGUP, KC_HOME,   KC_UP,  KC_END, SRCHSEL, KC_DEL ,
        _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , KC_INS ,
                 C(KC_Z), SELWBAK, SELWORD, KC_APP , C(KC_R), _______,

        _______, KC_WBAK,  G_TAB ,          _______, _______, _______
    ),

    [L_NUM] = LAYOUT_LR_THUMB(
        _______, KC_SLSH,    KC_9,    KC_8,    KC_7, KC_ASTR, _______,
        _______, KC_MINS,    KC_3,    KC_2,    KC_1, KC_PLUS, _______,
        _______, KC_X   ,    KC_6,    KC_5,    KC_4, KC_PERC,

        QK_LLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI, _______,
                 XXXXXXX, XXXXXXX, KC_COMM, KC_DOT , _______, KC_RSFT,

        KC_DOT , KC_BSPC, KC_0   ,          KC_RCTL, _______, _______
    ),

    [L_WIN] = LAYOUT_LR_THUMB(
        _______, A_F4   , KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, _______,
        _______, XXXXXXX, G(KC_3), G(KC_2), G(KC_1), G(KC_D), _______,
        _______, XXXXXXX, G(KC_6), G(KC_5), G(KC_4), G(KC_W),

        QK_LLCK, XXXXXXX, XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX, A_F4   ,
        _______, XXXXXXX, KC_MPRV, KC_VOLD, KC_MNXT, KC_LALT, XXXXXXX,
                 XXXXXXX, SA_TAB , A_TAB  , XXXXXXX, XXXXXXX, G_ENT  ,

        _______, _______, KC_MPLY,          KC_MPLY, _______, _______
    ),

    [L_FUN] = LAYOUT_LR_THUMB(
        XXXXXXX, KC_F12 , KC_F9  , KC_F8  , KC_F7  , XXXXXXX, XXXXXXX,
        KC_CAPS, KC_F10 , KC_F3  , KC_F2  , KC_F1  , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_F11 , KC_F6  , KC_F5  , KC_F4  , XXXXXXX,

        QK_LLCK, XXXXXXX, XXXXXXX, KC_INS , XXXXXXX, XXXXXXX, QK_BOOT,
        XXXXXXX, XXXXXXX, KC_PSCR, KC_DEL , XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_RBT ,

        _______, _______, DB_TOGG,          _______, QK_LLCK, _______
    ),

    [L_EXT] = LAYOUT_LR_THUMB(
        _______, _______, _______, _______, _______, _______, _______,
        XXXXXXX, RM_HUEU, RM_SATU, RM_VALU, _______, _______, _______,
        QK_BOOT, RM_HUED, RM_SATD, RM_VALD, _______, _______,

        QK_LLCK, OM_W_U , OM_BTN1, OM_U   , OM_BTN2, SRCHSEL, CG_TOGG,
        _______, OM_W_D , OM_L   , OM_D   , OM_R   , OM_SLOW, _______,
                 _______, _______, _______, _______, _______, _______,

        RM_PREV, RM_NEXT, RM_TOGG,          OM_BTN1, QK_LLCK, _______
    ),
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

// Check if the layer is locked by checking if the layer bit is set in the
// layer state.
#define M_is_layer_locked(layer) ((bool)(layer_state & ((layer_state_t)0x1 << (layer))))

///////////////////////////////////////////////////////////////////////////////
// User macro callbacks (https://docs.qmk.fm/feature_macros)
///////////////////////////////////////////////////////////////////////////////

const uint16_t caps_combo[] PROGMEM = {KC_C, KC_COMM, COMBO_END};
const uint16_t fn_combo[] PROGMEM   = {KC_H, HRM_J, COMBO_END};
const uint16_t alpha_combo[] PROGMEM   = {KC_Z, KC_SLSH, COMBO_END};
combo_t key_combos[] = {
    COMBO(caps_combo, CW_TOGG), // C and , => Activate Caps Word
    COMBO(fn_combo, OSL(L_FUN)), // H and J => L_FUN Layer
    COMBO(alpha_combo, TG(L_ALPHA)), // Z and / => Toggle L_ALPHA Layer
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
        if (!(M_is_layer_locked(L_NAV) || left_home_ring_held || left_home_index_held)) {
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
    // switch (keycode) {
    // case EX_COL:
    //     if (record->tap.count) {
    //         if (record->event.pressed) {
    //             if (shift_mods) {
    //                 del_weak_mods(MOD_MASK_SHIFT);
    //                 unregister_mods(MOD_MASK_SHIFT);
    //                 tap_code_delay(KC_SCLN, TAP_CODE_DELAY);
    //                 set_mods(mods);
    //             } else {
    //                 tap_code16_delay(KC_COLN, TAP_CODE_DELAY);
    //             }
    //         }
    //         return false;
    //     }
    //    return true;
    //}

    if (record->event.pressed) {
        switch (keycode) {
        case WPASS:
            SEND_STRING_DELAY(WPASS_STR, TAP_CODE_DELAY);
            return false;
        case HPASS:
            SEND_STRING_DELAY(HPASS_STR, TAP_CODE_DELAY);
            return false;
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
            char const *string = alt ? (shift_mods ? "<=>" : "<->") : (shift_mods ? "=>" : "->");
            SEND_STRING_DELAY(string, TAP_CODE_DELAY);
            return false;
        case SRCHSEL: // Searches the current selection in a new tab.
            // Mac users, change LCTL to LGUI.
            SEND_STRING_DELAY(SS_LCTL("ct") SS_DELAY(100) SS_LCTL("v") SS_TAP(X_ENTER), TAP_CODE_DELAY);
            return false;
        }
        }
    }

    return true;
}

bool select_word_host_is_mac(void) {
    return mod_config(MOD_LGUI) == MOD_LCTL; // GUI/Ctrl swapped => Mac.
}

#if defined(OS_DETECTION_ENABLE)
bool process_detected_host_os_user(os_variant_t os) {
    if (os == OS_MACOS) {
        keymap_config.swap_lctl_lgui = true;
        keymap_config.swap_rctl_rgui = true;
    } else {
        keymap_config.swap_lctl_lgui = false;
        keymap_config.swap_rctl_rgui = false;
    }
    return true;
}
#endif // OS_DETECTION_ENABLE
