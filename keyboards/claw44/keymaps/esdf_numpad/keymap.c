/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
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

#include QMK_KEYBOARD_H
#include "keymap_jp.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum custom_layers {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
      KC_TAB , JP_Q   , JP_W   , JP_E   , JP_R   , JP_T   ,     JP_Y   , JP_U   , JP_I   , JP_O   , JP_P   , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_LCTL, JP_A   , JP_S   , JP_D   , JP_F   , JP_G   ,     JP_H   , JP_J   , JP_K   , JP_L   , JP_SCLN, JP_UNDS,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_LSFT, JP_Z   , JP_X   , JP_C   , JP_V   , JP_B   ,     JP_N   , JP_M   , JP_COMM, JP_DOT , JP_SLSH, KC_RSFT,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                        KC_LGUI, LOWER  , KC_SPC , KC_ESC ,     KC_ESC , KC_ENT , RAISE  , KC_LOPT
  //                 `---------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_LOWER] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
      _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,     XXXXXXX, JP_7   , JP_8   , JP_9   , JP_PLUS, KC_DEL ,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,     XXXXXXX, JP_4   , JP_5   , JP_6   , JP_MINS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, XXXXXXX,     JP_0   , JP_1   , JP_2   , JP_3   , JP_UNDS, JP_YEN,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                        _______, _______, _______, _______,     _______, _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_RAISE] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
      _______, JP_EXLM, JP_AT  , KC_UP  , JP_HASH, JP_DLR ,     JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, KC_DEL ,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, JP_PERC,     JP_PLUS, JP_MINS, JP_LCBR, JP_RCBR, JP_PIPE, JP_GRV,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, KC_PGDN, KC_HOME, XXXXXXX, KC_END , XXXXXXX,     XXXXXXX, JP_EQL , JP_LBRC, JP_RBRC, XXXXXXX, JP_TILD,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                        _______, _______, _______, _______,     _______, _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),

  [_ADJUST] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------.   ,--------+--------+--------+--------+--------+--------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, JP_QUOT, JP_DQUO, JP_COLN, JP_SCLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //`--------+--------+--------+--------+--------+--------/   \--------+--------+--------+--------+--------+--------'
                        _______, _______, _______, _______,     _______, _______, _______, _______
  //                  `--------+--------+--------+--------'   `--------+--------+--------+--------'
  ),
};


// QMK Firmware で Raise/Lower と変換/無変換を同じキーに割り当てる
// https://okapies.hateblo.jp/entry/2019/02/02/133953

static bool lower_pressed = false;
static bool raise_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (lower_pressed) {
          // 英数 (Mac)
          tap_code(KC_LANG2);
          // 無変換 (Win)
          tap_code(JP_MHEN);
        }
        lower_pressed = false;
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (raise_pressed) {
          // かな (Mac)
          tap_code(KC_LANG1);
          // 変換 (Win)
          tap_code(JP_HENK);
        }
        raise_pressed = false;
      }
      return false;
      break;

    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;

    default:
      if (record->event.pressed) {
        lower_pressed = false;
        raise_pressed = false;
      }
  }

  return true;
};
