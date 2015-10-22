#include "action_util.h"
#include "action_layer.h"
#define KC_SW0 KC_FN0
#define DEBUG_ACTION

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

     KEYMAP(  // layer 0: normal cc123 layout
        // left hand
        ESC ,   1,   2,   3,   4,   5,   LBRC,
        TAB ,QUOT,COMM, DOT,   P,   Y,   BSLS,    
        BSLS,   A,   O,   E,   U,   I,
        LSFT,SCLN,   Q,   J,   K,   X,   EQL,
        LCTL, GRV, BSLS,LALT,FN3,				// FN3 Mouse Layer
                                      LGUI,MPRV,
                                           MNXT,
                                 BSPC,DEL ,MPLY,FN16,// FN16 invisikey
        // right hand
             FN17,6,   7,   8,   9,   0,   RBRC,// FN17=Left Led on - FN4=Teensy
             GRV ,F,   G,   C,   R,   L,   SLSH,
                  D,   H,   T,   N,   S,   MINS,
             BSLS,B,   M,   W,   V,   Z,   RSFT,
                       LEFT,RGHT,UP  ,DOWN,RCTL,
        PGUP,FN5,								// FN14 Toggle Left Hand Off
        PGDN,
        FN2,ENT,SPC								// FN2 Movement Layer
    ),
	
    KEYMAP(  // layer 1 : debugging, no left hand - rearranged to access magic functions
        // left hand
        NO  ,   NO,  NO,  NO,  NO,  NO,  NO,
        NO  ,   NO,  NO,  NO,  NO,  NO,  NO,    // FN4 Teensy
        NO  ,   NO,  NO,  NO,  NO,  NO,
        NO  ,   NO,  NO,  NO,  NO,  NO,  NO,
        NO  ,   NO,  NO,  NO,  NO,				// FN2 Movement Layer
                                      NO , NO,
                                          NO,
								  NO,  NO , FN15,FN16, // FN0 Turn Left Hand Off
        // right hand
             ESC, 6,   7,   8,   9,   0,   PAUS,
             RBRC,Y,   U,   I,   O,   P,   LBRC,
                  H,   N,   K,   L,   SCLN,LSFT,
             TRNS,X,   M,   COMM,DOT, SLSH,RSFT,
                       LEFT,RGHT,UP  ,DOWN,RCTL,
        FN14,FN5,
        PGUP,
        FN2 ,ENT ,SPC
    ),
 
    KEYMAP(  // layer 2: customized dvorak
        // left hand
        ESC, 1,   2,   3,   4,   5,   BSLS,
        TAB, QUOT,COMM,DOT, P,   Y,   FN2,
        LSFT,A,   O,   E,   U,   I,
        LCTL,SCLN,Q,   J,   K,   X,   DEL,
        FN3, FN1, LCTL,LALT,LGUI,
                                      FN5, HOME,
                                           END,
                                 BSPC,LSFT,LGUI,TRNS,
        // right hand
             MINS,6,   7,   8,   9,   0,   EQL,
             FN3, F,   G,   C,   R,   L,   SLSH,
                  D,   H,   T,   N,   S,   RSFT,
             DEL, B,   M,   W,   V,   Z,   RCTL,
                       LEFT,DOWN,UP,  RGHT,FN2,
        PGUP,MPLY,
        PGDN,
        ENT, FN1, SPC
    ),

    // PLOVER (SPECIAL CASE)

    KEYMAP(  // layout: layer 3: Steno for Plover
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,  
        NO,  1,   2,   3,   4,   5,   NO,  
        NO,  Q,   W,   E,   R,   T,  
        NO,  A,   S,   D,   F,   G,   NO,
        NO,  NO,  NO,  NO,  NO,  
                                      NO,  NO,  
                                           NO,  
                                 C,   V,   FN15,FN16,// FN15 Turn Left Thumbs Off (Momentarily)
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             NO,  6,   7,   8,   9,   0,   TRNS,
                  Y,   U,   I,   O,   P,   LBRC,
             NO,  H,   J,   K,   L,   SCLN,QUOT,
                       TRNS,TRNS,NO,  NO,  NO,  
        TRNS,FN5,  
        TRNS,  
        NO,  N,   M   
    ),

    KEYMAP(  // layer 4: reserved
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    // MODIFIERS THAT MIGHT BE STICKY

    KEYMAP(  // layout: layer 5: mouse + numpad
        // left hand
        FN0, NO,  NO,  NO,  NO,  PAUS,PSCR,
        TRNS,NO,  WH_U,MS_U,WH_D,BTN2,TRNS,
        TRNS,NO,  MS_L,MS_D,MS_R,BTN1,
        TRNS,NO,  NO,  NO,  NO,  BTN3,TRNS,
        TRNS,FN13,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,TRNS,
        // right hand
             SLCK,NLCK,EQL, PSLS,PAST,PMNS,TRNS,
             TRNS,NO,  P7,  P8,  P9,  PMNS,BSPC,
                  NO,  P4,  P5,  P6,  PPLS,PENT,
             TRNS,NO,  P1,  P2,  P3,  PPLS,PENT,
                       P0,  PDOT,PDOT,PENT,PENT,
        TRNS,TRNS,
        TRNS,
        ENT, TRNS,BSPC
    ),

    KEYMAP(  // layout: layer 6: F-keys + cursor
        // left hand
        FN0, F1,  F2,  F3,  F4,  F5,  F6,
        TRNS,NO,  PGUP,UP,  PGDN,NO,  TRNS,
        TRNS,HOME,LEFT,DOWN,RGHT,END, 
        TRNS,NO,  NO,  END, HOME,NO,  TRNS,
        TRNS ,TRNS,TRNS,FN10,FN2,
                                      TRNS,TRNS,
                                           TRNS,
                                 LCTL,LSFT,TRNS,TRNS,
        // right hand
             F7,  F8,  F9,  F10, F11, F12, MINS,
             TRNS,ESC, PGUP,UP,  PGDN, NO,  FN4,
                  HOME,LEFT,DOWN,RGHT,END, TRNS,
             TRNS,NO,  ENT, NO,  NO,  NO,  TRNS,
                       RGUI,RALT,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,TRNS,RSFT,RCTL
    ),

    KEYMAP(  // layer 7: "BlueShift"
        // left hand
        FN0, F1,  F2,  F3,  F4,  F5,  F6,
        TRNS,GRV, FN12,FN12,PSCR,BSLS,TRNS,  // the FN12 entries are for inverted brace/bracket keys
        TRNS,APP, TAB, EQL, TRNS,INS, 
        TRNS,TRNS,TRNS,TRNS,CAPS,TRNS,TRNS,
        FN13,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 ESC, TRNS,TRNS,TRNS,
        // right hand
             F7,  F8,  F9,  F10, F11, F12, MINS,
             TRNS,PGUP,HOME,UP,  END, SLSH,RBRC,
                  PGDN,LEFT,DOWN,RGHT,MINS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       RGUI,RALT,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    // MODIFIERS THAT WON'T BE STICKY

    KEYMAP(  // layer 8: Special function-driven commands (any-key)
        // left hand
        FN8, FN8, FN8, FN8, FN8, FN8, FN8, 
        FN8, FN8, FN8, FN8, FN8, FN8, FN8, 
        LSFT,FN8, FN8, FN8, FN8, FN8, 
        FN8, FN8, FN8, FN8, FN8, FN8, FN8, 
        FN8, FN8, FN8, FN8, FN8, 
                                      FN8, FN8, 
                                           FN8, 
                                 FN8, FN10,FN8,TRNS,
        // right hand
             FN8, FN8, FN8, FN8, FN8, FN8, FN8, 
             FN8, FN8, FN8, FN8, FN8, FN8, FN8, 
                  FN8, FN8, FN8, FN8, FN8, RSFT,
             FN8, FN8, FN8, FN8, FN8, FN8, FN8, 
                       FN8, FN8, FN8, FN8, FN8, 
        FN8, FN8, 
        FN8, 
        FN8, FN8, FN8
    ),

    KEYMAP(  // layout: layer 9: F-keys only
        // left hand
        FN0, NO,  NO,  NO,  NO,  NO,  NO,  
        TRNS,F13, F14, F15, F16, NO,  TRNS,
        TRNS,F17, F18, F19, F20, NO,  
        TRNS,F21, F22, F23, F24, NO,  TRNS,
        FN13,FN13,TRNS,LALT,LGUI,
                                      TRNS,TRNS,
                                           TRNS,
                                 LCTL,LSFT,TRNS,TRNS,
        // right hand
             NO,  NO,  F10, F11, F12, NO,  TRNS,
             TRNS,NO,  F7,  F8,  F9,  NO,  TRNS,
                  NO,  F4,  F5,  F6,  NO,  TRNS,
             TRNS,NO,  F1,  F2,  F3,  NO,  TRNS,
                       RGUI,RALT,RCTL,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,RSFT,RCTL
    ),

    KEYMAP(  // layout: layer 10: reserved
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layout: layer 11: disabled left thumb
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
									NO,NO,
										NO,
									NO,NO,FN15,FN16,

        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
         TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    // TEMPLATES

/*
    KEYMAP(  // layout: layer N: transparent on edges, all others are empty
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,  
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,NO,  NO,  NO,  NO,  NO,  
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,TRNS,TRNS,LALT,LGUI,
                                      TRNS,TRNS,
                                           TRNS,
                                 LCTL,LSFT,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                       RGUI,RALT,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,RSFT,RCTL
    ),
    KEYMAP(  // layout: layer N: fully transparent
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
*/

};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
    ANY_KEY,
    PLOVER_SWITCH,
    SHIFT_SWITCH,
    FKEY_SWITCH,
	DUMBTHUMBS,
	DUMBTHUMBSMOMENTARY,
	INVISIKEY,
	LEFTLED,
};

enum macro_id {
    MACRO_PASSWORD1,
    MACRO_PASSWORD2,
    MACRO_PASSWORD3,
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    ACTION_LAYER_SET(0, ON_PRESS),                  // FN0 - set layer0 only
    ACTION_LAYER_TAP_TOGGLE(7),                     // FN1 - switch to BlueShift
    ACTION_LAYER_TAP_TOGGLE(6),                     // FN2 - Fkeys & Cursor tap/toggle
    ACTION_LAYER_TAP_TOGGLE(5),                     // FN3 - mouse + numpad
    ACTION_FUNCTION(TEENSY_KEY),                    // FN4 - Teensy key
    ACTION_FUNCTION(PLOVER_SWITCH),                 // FN5 - enable Plover
    ACTION_FUNCTION(PLOVER_SWITCH),                 // ** FN6 - suspend Plover (OUT OF USE)
    ACTION_LAYER_MOMENTARY(8),                      // FN7 - Trigger the AnyKey layer
    ACTION_FUNCTION(ANY_KEY),                       // FN8 - AnyKey functional layer
    ACTION_MODS_TAP_TOGGLE(MOD_LSFT),               // ** FN9 - tap toggle shift (OUT OF USE)
    ACTION_MACRO(MACRO_PASSWORD1),                  // FN10 - password1
    ACTION_MACRO(MACRO_PASSWORD2),                  // FN11 - password2
    ACTION_FUNCTION(SHIFT_SWITCH),                  // FN12 - symbolized number row
    ACTION_FUNCTION(FKEY_SWITCH),                   // FN13 - trigger Fkey layer and get rid of it appropriately
	ACTION_FUNCTION(DUMBTHUMBS),					// FN14 - activate/disable left hand for testing
//	ACTION_LAYER_MOMENTARY(11),						// FN15 - disable left thumbs
	ACTION_FUNCTION(DUMBTHUMBSMOMENTARY),			// FN15 - disable left thumbs
	ACTION_FUNCTION(INVISIKEY),						// FN16 - invisikey
	ACTION_FUNCTION(LEFTLED),						// FN17 - turn left-led on
};

void simon_hotkey(keyrecord_t *record, action_t action)
{
    keyevent_t event = record->event;

    switch (action.kind.id) {
        /* Key and Mods */
        case ACT_LMODS:
        case ACT_RMODS:
            {
                uint8_t mods = (action.kind.id == ACT_LMODS) ?  action.key.mods :
                                                                action.key.mods<<4;
                if (event.pressed) {
                    if (mods) {
                        add_weak_mods(mods);
                        send_keyboard_report();
                    }
                    register_code(action.key.code);
                } else {
                    unregister_code(action.key.code);
                    if (mods) {
                        del_weak_mods(mods);
                        send_keyboard_report();
                    }
                }
            }
            break;
        default:
            print("not supported.\n");
            break;
    }
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;

    // print("action_function called\n");
    // print("id  = "); phex(id); print("\n");
    // print("opt = "); phex(opt); print("\n");
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
    else if (id == DUMBTHUMBS) {
        if (event.pressed) {
            if (layer_state & 1<<11) { // layer 11 is already on
                print("enabling left thumbs...\n");
                layer_off(11);
            } else {
                print("disabling left thumbs...\n");
                layer_on(11);
            }
        }		
    }
    else if (id == DUMBTHUMBSMOMENTARY) {
        if (event.pressed) {
            /* if (layer_state & 1<<11) */ { // layer 11 is already on
                print("DUMBTHUMBSMOMENTARY disabling left thumbs momentarily... and top left led ON\n");
                layer_on(11);
				ergodox_left_led_1_on();
            }
        } else {
                print("enabling left thumbs momentarily... and top left led off\n");
                layer_off(11);
				ergodox_left_led_1_off();
		}
    }
    else if (id == INVISIKEY) {
        if (event.pressed) {
			{
                print("INVISIKEY pressed, disabling left thumbs momentarily... and top left led ON\n");
				ergodox_left_led_1_on();
                layer_on(11);
				ergodox_left_leds_update();
			}
        } else {
                print("INVISIKEY released, enabling left thumbs momentarily... and top left led off\n");
				ergodox_left_led_1_off();
				layer_off(11);
				ergodox_left_leds_update();
		}
    }
    else if (id == LEFTLED) {
        if (event.pressed) {
			{
                print("LEFTLED pressed, turning top left led ON\n");
				ergodox_left_led_1_on();
				ergodox_left_leds_update();
			}
        } else {
                print("LEFTLED released, turning top left led off\n");
				ergodox_left_led_1_off();
				ergodox_left_leds_update();
		}
    }
    else if (id == PLOVER_SWITCH) {
        if (event.pressed) {
            if (layer_state & 1<<3) { // plover is already on
                print("switching off plover layout...\n");
                action_macro_play(MACRO( D(A), D(W), D(P), D(F), D(SCLN), D(LBRC), D(QUOT), D(D), D(A), D(L), U(W), U(P), U(F), U(SCLN), U(LBRC), U(QUOT), U(D), U(L), END));
                layer_off(3);
            } else {
                print("switching on plover layout...\n");
                action_macro_play(MACRO(D(LANG5), U(LANG5), D(W), D(P), D(F), D(SCLN), D(LBRC), D(QUOT), D(D), D(A), U(W), U(P), U(F), U(SCLN), U(LBRC), U(QUOT), U(D), END));
                layer_on(3);
            }
        }
    }
    else if (id == ANY_KEY) {
        uint8_t col = event.key.col;
        uint8_t row = event.key.row;

        action_t action = { .code = ACTION_NO };

        if (col == 3 && row == 10) { // W
            action.code = ACTION_MODS_KEY(MOD_LALT, KC_F4);
        }
        if (col == 4 && row == 12) { // Alt+tab
            action.code = ACTION_MODS_KEY(MOD_LALT, KC_TAB);
        }
        if (action.code != ACTION_NO) {
            simon_hotkey(record, action);
        }
        else
        {
            print("col = "); pdec(col); print("\n");
            print("row = "); pdec(row); print("\n");
        }
    }
    else if (id == SHIFT_SWITCH) {
        uint8_t col = event.key.col;
        uint8_t row = event.key.row;
        uint8_t savedmods = get_mods();
        uint8_t shiftpressed = (savedmods & (MOD_LSFT | MOD_RSFT));
        uint8_t othermodspressed = (savedmods & (MOD_LGUI | MOD_RGUI | MOD_LCTL | MOD_RCTL | MOD_LALT | MOD_RALT ));

        action_t action = { .code = ACTION_NO };
        uint8_t keycode = KC_NO;

        if (col == 0) { // Number row
            switch (row) {
                case 1:
                    keycode = KC_1;
                    break;
                case 2:
                    keycode = KC_2;
                    break;
                case 3:
                    keycode = KC_3;
                    break;
                case 4:
                    keycode = KC_4;
                    break;
                case 5:
                    keycode = KC_5;
                    break;
                case 8:
                    keycode = KC_6;
                    break;
                case 9:
                    keycode = KC_7;
                    break;
                case 10:
                    keycode = KC_8;
                    break;
                case 11:
                    keycode = KC_9;
                    break;
                case 12:
                    keycode = KC_0;
                    break;
                default:
                    break;
            }
        }
        if (col == 1) { // next row
            switch (row) {
                case 2:
                    keycode = KC_LBRC;
                    break;
                case 3:
                    keycode = KC_RBRC;
                    break;
                default:
                    break;
            }
        }
        if (keycode != KC_NO) {
            action.code = ACTION_MODS_KEY(MOD_LSFT, keycode);
        }
        if (action.code != ACTION_NO) {
            if (othermodspressed) {
                action.key.mods = 0;
            }
            else if (shiftpressed) {
                action.key.mods = 0;
                del_mods(MOD_LSFT | MOD_RSFT);
            }
            simon_hotkey(record, action);
            if (shiftpressed) {
                set_mods(savedmods);
            }
        }
    }
    else if (id == FKEY_SWITCH) {
        uint8_t row = event.key.row;
        if (event.pressed) {
            layer_on(12);
        }
        else {
            if ((row == 0) && (layer_state & 1<<6)) { // left button and from numpad; out-of-order release
                layer_off(6);
            }
            else if ((row == 1) && (layer_state & 1<<8)) { // right button and from BlueShift; out-of-order release
                layer_off(8);
            }
            else {
                layer_off(12);
            }
        }
    }
}

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;

    switch (id) {
/*#include "keymap_simon_passwords.h" */
        default:
                return MACRO( END );
    }
    return MACRO_NONE;
}

