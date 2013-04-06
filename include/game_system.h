
/* System Handler */

#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#include "game_main.h"


bool init_system(void);
void system_shutdown(void);

void system_do_main_loop(void);

void system_signal_game_quit(void);

#endif /* __GAME_SYSTEM_H__ */
