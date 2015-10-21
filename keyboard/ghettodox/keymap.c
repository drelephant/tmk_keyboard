/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"


/* GH60 keymap definition macro
 * K2C, K31 and  K3C are extra keys for ISO
 */
#define KEYMAP( \
  K00, K01, K02, K03, K04, K05, K06, K07, \
  K10, K11, K12, K13, K14, K15, K16, K17, \
  K20, K21, K22, K23, K24, K25, K26, K27, \
  K30, K31, K32, K33, K34, K35, K36, K37, \
  K40, K41, K42, K43, K44, K45, K46, K47, \
  K50, K51, K52, K53, K54, K55, K56, K57, \
  K60, K61, K62, K63, K64, K65, K66, K67, \
  K70, K71, K72, K73, K74, K75, K76, K77, \
  K80, K81, K82, K83, K84, K85, K86, K87, \
  K90, K91, K92, K93, K94, K95, K96, K97 \
) { \
  { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
  { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
  { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
  { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
  { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, \
  { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
  { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
  { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
  { KC_##K80, KC_##K81, KC_##K82, KC_##K83, KC_##K84, KC_##K85, KC_##K86, KC_##K87 }, \
  { KC_##K90, KC_##K91, KC_##K92, KC_##K93, KC_##K94, KC_##K95, KC_##K96, KC_##K97 } \
}

/* ANSI valiant. No extra keys for ISO */
#define KEYMAP_ANSI( \
  K00, K01, K02, K03, K04, K05, K06, K07, \
  K10, K11, K12, K13, K14, K15, K16, K17, \
  K20, K21, K22, K23, K24, K25, K26, K27, \
  K30, K31, K32, K33, K34, K35, K36, K37, \
  K40, K41, K42, K43, K44, K45, K46, K47, \
  K50, K51, K52, K53, K54, K55, K56, K57, \
  K60, K61, K62, K63, K64, K65, K66, K67, \
  K70, K71, K72, K73, K74, K75, K76, K77, \
  K80, K81, K82, K83, K84, K85, K86, K87, \
  K90, K91, K92, K93, K94, K95, K96, K97 \
) KEYMAP( \
  K00, K01, K02, K03, K04, K05, K06, K07, \
  K10, K11, K12, K13, K14, K15, K16, K17, \
  K20, K21, K22, K23, K24, K25, K26, K27, \
  K30, K31, K32, K33, K34, K35, K36, K37, \
  K40, K41, K42, K43, K44, K45, K46, K47, \
  K50, K51, K52, K53, K54, K55, K56, K57, \
  K60, K61, K62, K63, K64, K65, K66, K67, \
  K70, K71, K72, K73, K74, K75, K76, K77, \
  K80, K81, K82, K83, K84, K85, K86, K87, \
  K90, K91, K92, K93, K94, K95, K96, K97 \
)
 
/* #define KEYMAP( \
  K00, K01, K02, K03, K04, K05, K06, K07, \
  K10, K11, K12, K13, K14, K15, K16, K17, \
  K20, K21, K22, K23, K24, K25, K26, K27, \
  K30, K31, K32, K33, K34, K35, K36, K37, \
  K40, K41, K42, K43, K44, K45, K46, K47, \
  K50, K51, K52, K53, K54, K55, K56, K57, \
  K60, K61, K62, K63, K64, K65, K66, K67, \
  K70, K71, K72, K73, K74, K75, K76, K77, \
  K80, K81, K82, K83, K84, K85, K86, K87, \
  K90, K91, K92, K93, K94, K95, K96, K97 \
) { \
  { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
  { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
  { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
  { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
  { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, \
  { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
  { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
  { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
  { KC_##K80, KC_##K81, KC_##K82, KC_##K83, KC_##K84, KC_##K85, KC_##K86, KC_##K87 }, \
  { KC_##K90, KC_##K91, KC_##K92, KC_##K93, KC_##K94, KC_##K95, KC_##K96, KC_##K97 } \
} */


#if defined(KEYMAP_PLAIN)
    #include "keymap_plain.h"
/* #elif defined(KEYMAP_POKER)
    #include "keymap_poker.h"
#elif defined(KEYMAP_POKER_SET)
    #include "keymap_poker_set.h"
#elif defined(KEYMAP_POKER_BIT)
    #include "keymap_poker_bit.h" */
#else
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Funky
     */
    /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn3|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|Fn2|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl|Gui |Alt |      Space             |Alt |Fn4 |Fn4 |Fn1 |
     * `-----------------------------------------------------------'
     */
/*     KEYMAP_ANSI(
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN2, QUOT,     ENT,  \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN1,           FN9,  \
        LCTL,LGUI,LALT,          SPC,                     RALT,FN3, FN3, FN0,  \
		A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A
		), */
		
	KEYMAP_ANSI(
        A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, \
        A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, \
        A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, \
        A,B
		),
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(4),
    [1] = ACTION_LAYER_TAP_KEY(5, KC_SLASH),
    [2] = ACTION_LAYER_TAP_KEY(6, KC_SCLN),
    [3] = ACTION_LAYER_MOMENTARY(6),
    [4] = ACTION_LAYER_MOMENTARY(7),   // to Layout selector
    [5] = ACTION_DEFAULT_LAYER_SET(0),  // set qwerty layout
    [6] = ACTION_DEFAULT_LAYER_SET(1),  // set colemak layout
    [7] = ACTION_DEFAULT_LAYER_SET(2),  // set dvorak layout
    [8] = ACTION_DEFAULT_LAYER_SET(3),  // set workman layout
    [9] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_GRV),
};
#endif



#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, key_t key)
{
    if (layer < KEYMAPS_SIZE) {
        return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
    } else {
        // XXX: this may cuaes bootlaoder_jump inconsistent fail.
        //debug("key_to_keycode: base "); debug_dec(layer); debug(" is invalid.\n");
        // fall back to layer 0
        return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]);
    }
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    } else {
        action.code = ACTION_NO;
    }
    return action;
}
