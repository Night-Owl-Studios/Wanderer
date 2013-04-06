
/* Game Inputs */

#include <assert.h>
#include "game_main.h"
#include "game_inputs.h"

typedef struct {
    bool stored_state;
    bool desired_state;
    void (*cb_func)();
} input_t;

static bool     kb_in_text_mode = false;
static input_t  kb_callbacks[ ALLEGRO_KEY_MAX ];

/******************************************************************************
 * INPUTS -- NITIFICATIONS
 * Designed to run the moment a key is pressed/released
******************************************************************************/
void keyboard_notify(unsigned keycode, bool state) {
    assert(keycode < ALLEGRO_KEY_MAX);
    kb_callbacks[keycode].stored_state = state;
    
    if (    kb_in_text_mode
    &&      kb_callbacks[keycode].desired_state == state
    &&      kb_callbacks[keycode].cb_func != NULL
    ) {
        kb_callbacks[keycode].cb_func();
    }
}

/******************************************************************************
 * INPUTS -- CALLBACKS
******************************************************************************/
void keyboard_set_callback(unsigned keycode, bool state_action, void (*func)()) {
    assert(keycode < ALLEGRO_KEY_MAX);
    kb_callbacks[keycode].desired_state = state_action;
    kb_callbacks[keycode].cb_func = func;
}

/******************************************************************************
 * INPUTS -- ACQUIRING THE KEYBOARD STATE
******************************************************************************/
bool keyboard_get_state(unsigned key) {
    assert(key < ALLEGRO_KEY_MAX);
    return kb_callbacks[key].stored_state;
}

/******************************************************************************
 * INPUTS -- KEYBOARD TEXT MODE
******************************************************************************/
bool keyboard_is_in_text_mode(void)     { return kb_in_text_mode; }
void keyboard_enable_text_mode()        { kb_in_text_mode = true; }
void keyboard_disable_text_mode()       { kb_in_text_mode = false; }

/******************************************************************************
 * INPUTS -- UPDATING
 * Designed to run just before the display is updated
******************************************************************************/
void update_game_inputs() {
    if (kb_in_text_mode)
        return;
    
    /* call the corresponding keyboard action if state matches key_state */
    for (unsigned i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        if (    kb_callbacks[i].stored_state == kb_callbacks[i].desired_state
        &&      kb_callbacks[i].cb_func != NULL
        ) {
            kb_callbacks[ i ].cb_func();
        }
    }
}
