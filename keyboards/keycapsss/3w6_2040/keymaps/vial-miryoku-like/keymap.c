// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum layers {
    _BASE = 0,
    _BUTTON,
    _NAV,
    _MOUSE,
    _MEDIA,
    _NUM,
    _SYM,
    _FUN,
};

#if !defined(RGBLIGHT_DEFAULT_VAL)
#    define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL
#endif

void set_default_rgblight(void) {
    rgblight_sethsv_range(RGBLIGHT_DEFAULT_HUE, RGBLIGHT_DEFAULT_SAT, RGBLIGHT_DEFAULT_VAL, 0, RGBLIGHT_LED_COUNT);
}

void set_hsvlight(uint8_t hue, uint8_t sat, uint8_t val) {
    rgblight_sethsv_range(hue, sat, val, 0, RGBLIGHT_LED_COUNT);
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    set_default_rgblight();
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t current_layer = get_highest_layer(state);
    switch (current_layer) {
        case _BUTTON:
            set_hsvlight(HSV_GOLDENROD);
            break;
        case _NAV:
            set_hsvlight(HSV_GREEN);
            break;
        case _MOUSE:
            set_hsvlight(HSV_PURPLE);
            break;
        case _MEDIA:
            set_hsvlight(HSV_TEAL);
            break;
        case _NUM:
            set_hsvlight(HSV_TURQUOISE);
            break;
        case _SYM:
            set_hsvlight(HSV_YELLOW);
            break;
        case _FUN:
            set_hsvlight(HSV_WHITE);
            break;
        case _BASE:
        default:
            set_default_rgblight();
            break;
    }
    return state;
}

#define RESET QK_CLEAR_EEPROM

#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off
    [_BASE] = LAYOUT_split_3x5_3(
        KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,
        LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              RSFT_T(KC_J),      RCTL_T(KC_K),      RALT_T(KC_L),      RGUI_T(KC_QUOT),
        LT(_BUTTON, KC_Z), ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    LT(_BUTTON, KC_SLSH),
                                              LT(_MEDIA, KC_TAB), LT(_NAV, KC_SPC),   LT(_FUN, KC_ENT), LT(_SYM, KC_ESC),   LT(_NUM, KC_BSPC),  LT(_FUN, KC_DEL)
    ),
    [_BUTTON] = LAYOUT_split_3x5_3(
        RESET,             DPI_RMOD,          DPI_MOD,           S_D_RMOD,          S_D_MOD,           S_D_RMOD,          S_D_MOD,           DPI_RMOD,          DPI_MOD,           RESET,
        KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           KC_NO,             KC_NO,             KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,
        U_NA,              DRGSCRL,           SNIPING,           U_NA,              U_NA,              U_NU,              U_NU,              SNIPING,           DRGSCRL,           U_NU,
                                              KC_BTN3,           KC_BTN2,           KC_BTN1,           KC_BTN1,           KC_BTN2,           KC_BTN3
    ),
    [_NAV] = LAYOUT_split_3x5_3(
        RESET,             U_NA,              U_NA,              U_NA,              U_NA,              U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,
        KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           KC_CAPS,
        U_NA,              KC_ALGR,           U_NA,              U_NA,              U_NA,              KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            KC_INS,
                                              U_NA,              U_NA,              U_NA,              KC_ENT,            KC_BSPC,           KC_DEL
    ),
    [_MOUSE] = LAYOUT_split_3x5_3(
        RESET,             DPI_RMOD,          DPI_MOD,           S_D_RMOD,          S_D_MOD,           U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,
        KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              KC_MS_L,           KC_MS_D,           KC_MS_U,           KC_MS_R,           U_NU,
        U_NA,              KC_ALGR,           U_NA,              U_NA,              U_NA,              KC_WH_L,           KC_WH_D,           KC_WH_U,           KC_WH_R,           U_NU,
                                              U_NA,              U_NA,              U_NA,              KC_BTN1,           KC_BTN3,           KC_BTN2
    ),
    [_MEDIA] = LAYOUT_split_3x5_3(
        RESET,             U_NA,              U_NA,              U_NA,              U_NA,              RGB_TOG,           RGB_MOD,           RGB_HUI,           RGB_SAI,           RGB_VAI,
        KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              KC_MPRV,           KC_VOLD,           KC_MUTE,           KC_VOLU,           KC_MNXT,
        U_NA,              KC_ALGR,           U_NA,              U_NA,              U_NA,              U_NU,              U_NU,              U_NU,              U_NU,              U_NU,
                                              U_NA,              U_NA,              U_NA,              KC_MSTP,           KC_MPLY,           KC_MUTE
    ),
    [_NUM] = LAYOUT_split_3x5_3(
        KC_LBRC,           KC_7,              KC_8,              KC_9,              KC_RBRC,           U_NA,              U_NA,              U_NA,              U_NA,              RESET,
        KC_SCLN,           KC_4,              KC_5,              KC_6,              KC_EQL,            U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,
        KC_GRV,            KC_1,              KC_2,              KC_3,              KC_BSLS,           U_NA,              U_NA,              U_NA,              KC_ALGR,           U_NA,
                                              KC_DOT,            KC_0,              KC_MINS,           U_NA,              U_NA,              U_NA
    ),
    [_SYM] = LAYOUT_split_3x5_3(
        KC_LCBR,           KC_AMPR,           KC_ASTR,           KC_LPRN,           KC_RCBR,           U_NA,              U_NA,              U_NA,              U_NA,              RESET,
        KC_COLN,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_PLUS,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,
        KC_TILD,           KC_EXLM,           KC_AT,             KC_HASH,           KC_PIPE,           U_NA,              U_NA,              U_NA,              KC_ALGR,           U_NA,
                                              KC_LPRN,           KC_RPRN,           KC_UNDS,           U_NA,              U_NA,              U_NA
    ),
    [_FUN] = LAYOUT_split_3x5_3(
        KC_F12,            KC_F7,             KC_F8,             KC_F9,             KC_PSCR,           U_NA,              U_NA,              U_NA,              U_NA,              U_NA,
        KC_F11,            KC_F4,             KC_F5,             KC_F6,             KC_SCRL,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,
        KC_F10,            KC_F1,             KC_F2,             KC_F3,             KC_PAUS,           U_NA,              U_NA,              U_NA,              KC_ALGR,           U_NA,
                                              KC_APP,            KC_SPC,            KC_TAB,            U_NA,              U_NA,              U_NA
    ),
    // clang-format on
};
