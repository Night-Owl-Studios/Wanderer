
/* System Handler */

#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#include "game_main.h"

bool init_system(void);

void terminate_system(void);

void sys_do_main_loop(void);

void sys_signal_game_quit(void);

#endif /* __GAME_SYSTEM_H__ */
