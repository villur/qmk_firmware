/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 8

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
enum custom_layers {
    _BL,
    _CS,
    _FL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: Base Layer (Default Layer)
   */
[_BL] = LAYOUT_65_iso_blocker(
  QK_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_PSCR,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_INS,
  KC_F13,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,   KC_DEL,
  KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(_FL),    KC_LEFT,  KC_DOWN,  KC_RGHT),

  [_CS] = LAYOUT_65_iso_blocker(
  QK_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_PSCR,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,            KC_INS,
  KC_F13,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,   KC_DEL,
  KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_END,
  KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(_FL),    KC_LEFT,  KC_DOWN,  KC_RGHT),

  /* Keymap _FL: Function Layer
   */
[_FL] = LAYOUT_65_iso_blocker(
  KC_TILDE,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,    _______,  KC_INS,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,             _______,
  KC_CAPS,  TO(_BL),  TO(_CS),  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
  _______,  _______,  RGB_HUI,  RGB_HUD,  RGB_SPD,  RGB_SPI,  KC_MUTE,  KC_VOLU,  KC_VOLD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  _______,   RGB_VAI,  KC_HOME,
  _______,  _______,  _______,                                QK_BOOT,                                _______,  _______,  RGB_RMOD,  RGB_VAD,  RGB_MOD)
};


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

       switch(get_highest_layer(layer_state)){  // special handling per layer
            case 1:  //layer 1
                rgb_matrix_set_color_all(0, 255, 0);
            break;
            case 2:  //layer 2
                rgb_matrix_set_color_all(255, 153, 255);
            break;
            default: //layer 0
                rgb_matrix_set_color_all(255, 255, 255);
                break;
            break;
}
return false;
}

// https://www.camerondugan.com/blog/my-old-keyboard-is-basically-cheating
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (get_highest_layer(layer_state) == 1) {
        static bool aHeld = false;
        static bool dHeld = false;
        static bool wHeld = false;
        static bool sHeld = false;
        switch (keycode) {
            case KC_A:
                aHeld = record->event.pressed;
                if (dHeld && aHeld) {
                    unregister_code(KC_D);
                } else if (dHeld && !aHeld) {
                    unregister_code(KC_A);
                    register_code(KC_D);
                    return false; // don't send original key pressed
                }
                return true;
            case KC_D:
                dHeld = record->event.pressed;
                if (aHeld && dHeld) {
                    unregister_code(KC_A);
                } else if (aHeld && !dHeld) {
                    unregister_code(KC_D);
                    register_code(KC_A);
                    return false; // don't send original key pressed
                }
                return true;
            case KC_W:
                wHeld = record->event.pressed;
                if (sHeld && wHeld) {
                    unregister_code(KC_S);
                } else if (sHeld && !wHeld) {
                    unregister_code(KC_W);
                    register_code(KC_S);
                    return false; // don't send original key pressed
                }
                return true;
            case KC_S:
                sHeld = record->event.pressed;
                if (wHeld && sHeld) {
                    unregister_code(KC_W);
                } else if (wHeld && !sHeld) {
                    unregister_code(KC_S);
                    register_code(KC_W);
                    return false; // don't send original key pressed
                }
                return true;
            default:
                return true; // Process all other keycodes normally
        }
    }
    else {
        return true;
    }
}
