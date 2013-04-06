
#ifndef __GAME_INPUTS_H__
#define __GAME_INPUTS_H__

#include "game_main.h"

/* KEYBOARD MANAGEMENT */
void keyboard_notify(unsigned keycode, bool state);
void keyboard_set_callback(unsigned keycode, bool state_action, void (*func)());
bool keyboard_get_state(unsigned keycode);
bool keyboard_is_in_text_mode(void);
void keyboard_enable_text_mode(); /* Callback Convenience */
void keyboard_disable_text_mode(); /* Callback Convenience */

/* INPUT UPDATING */
void update_game_inputs();

#endif /* __GAME_INPUTS_H__ */