#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define LYR1 1 // symbols
#define LYR2 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

/*
 * Keycodes: https://docs.qmk.fm/keycodes.html
 * Layer Switching: https://docs.qmk.fm/feature_advanced_keycodes.html#switching-and-toggling-layers
 *
 * 0-9 a-z                         : KC_0 - KC_9, KC_A - KC_Z
 * ↖ ↘   ⇟ ⇞  ▲ ▼ ◀  ▶             : KC_HOME, KC_END, KC_PGUP, KC_PGDN, KC_UP, KC_DOWN, KC_LEFT, KC_RGHT
 * - = , . / \ ; ' [ ]             : KC_MINS, KC_EQL, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, KC_SCLN, KC_QUOT, KC_LBRC, KC_RBRC
 * L⌘ , L⌃ , L⇧ , L⌥ , (+R⌘  etc.) : KC_LGUI, KC_LCTL, KC_LSFT, KC_LALT (+KC_RGUI etc.)
 * Space ⌫  ⌦  ↵  ⇥  ⎋             : KC_SPC, KC_BSPC, KC_DELT, KC_ENT, KC_TAB, KC_ESC
 *
 * MO(layer) - momentary switch to layer. As soon as you let go of the key, the layer is deactivated and you pop back out to the previous layer.
 * LT(layer, kc) - momentary switch to layer when held, and kc when tapped.
 * TG(layer) - toggles a layer on or off.
 * TO(layer) - Goes to a layer. This code is special, because it lets you go either up or down the stack -- just goes directly to the layer you want. So while other codes only let you go up the stack (from layer 0 to layer 3, for example), TO(2) is going to get you to layer 2, no matter where you activate it from -- even if you're currently on layer 5. This gets activated on keydown (as soon as the key is pressed).
 * TT(layer) - Layer Tap-Toggle. If you hold the key down, the layer becomes active, and then deactivates when you let go. And if you tap it, the layer simply becomes active (toggles on). It needs 5 taps by default, but you can set it by defining TAPPING_TOGGLE, for example, #define TAPPING_TOGGLE 2 for just two taps.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Reset  |   1  |   2  |   3  |   4  |   5  |  L2  |           |  L2  |   6  |   7  |   8  |   9  |   0  | Reset  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab ⇥  |   Q  |   W  |   E  |   R  |   T  |   (  |           |  )   |   Y  |   U  |   I  |   O  |   P  |   -    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  L⇧    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   |   '    |
 * |--------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+--------|
 * | Esc ⎋  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  /   |   \    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | F17  |      | L⌥   | L⌃   | L⌘   |                                       |  R⌃  | R⌥   |      |      | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | F17  |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | LAlt |       | LAlt |        |      |
 *                                 | R⇧   |  L1  |------|       |------|  ⌫     |Space |
 *                                 |      |      | LGui |       | LCtl |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
    // left hand
    RESET          , KC_1        , KC_2    , KC_3       , KC_4       , KC_5          , TG(LYR2)   ,
    KC_TAB         , KC_Q        , KC_W    , KC_E       , KC_R       , KC_T          , RSFT(KC_9) ,
    KC_RSFT        , KC_A        , KC_S    , KC_D       , KC_F       , KC_G          ,
    LCTL_T(KC_ESC) , CTL_T(KC_Z) , KC_X    , KC_C       , KC_V       , KC_B          , KC_LBRC    ,
    KC_F17         , _______     , KC_LALT , KC_LCTL    , KC_LGUI

    /* _______     , _______     , _______ , _______    , _______ */ , KC_F17        , _______
    /* _______     , _______     , _______ , _______    , _______    , _______ */    , KC_LALT
    /* _______     , _______     , _______ , _______ */ , KC_RSFT    , MO(LYR1)      , KC_LGUI    ,

    // right hand
    TG(LYR2)      , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , RESET   ,
    RSFT(KC_0)    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_MINS
                  , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT ,
    KC_RBRC       , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_BSLS
                  , KC_RSFT , KC_RALT , _______ , _______ , KC_FN1  ,

    _______       , _______ ,
    KC_LALT       ,
    KC_LCTL       , KC_BSPC , KC_SPC
    ),
/* Keymap 1: Hyper Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |   7  |   8  |   9  |      |      |           |      |  ↖   |  ⇟   |  ⇞   |  ↘   |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   0  |   4  |   5  |   6  |      |------|           |------|  ◀   |  ▼   |  ▲   |  ▶   |  =   |   `    |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   0  |   1  |   2  |   3  |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|  ⌦   |  ↵   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Layer 1
[LYR1] = LAYOUT_ergodox(
    // left hand
    VRSN    , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_TRNS ,
    KC_TRNS , KC_EXLM , KC_7    , KC_8    , KC_9    , KC_PIPE , KC_TRNS ,

    KC_TRNS , KC_0    , KC_4    , KC_5    , KC_6    , KC_GRV  ,
    KC_TRNS , KC_0    , KC_1    , KC_2    , KC_3    , KC_TILD , KC_TRNS ,
       EPRM , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS

     /* _______ , _______ , _______ , _______    , _______ */ , KC_TRNS         , KC_TRNS
     /* _______ , _______ , _______ , _______    , _______    , _______      */ , KC_TRNS
     /* _______ , _______ , _______ , _______ */ , KC_TRNS    , KC_TRNS         , KC_TRNS ,


    // right hand
    KC_TRNS   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
    KC_TRNS   , KC_HOME , KC_PGDN , KC_PGUP , KC_END  , KC_ASTR , KC_F12
              , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , KC_EQL  , KC_GRV  ,
    KC_TRNS   , KC_AMPR , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS
              , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,

    RGB_TOG   , RGB_SLD ,
    KC_TRNS   ,
    KC_TRNS   , KC_DEL  , KC_ENT

),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[LYR2] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(LYR1)                // FN1 - Momentary Layer 1 (Hyper layer)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
