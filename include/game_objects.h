
/* game objects */

#ifndef __GAME_OBJECTS_H__
#define __GAME_OBJECTS_H__

#include "game_main.h"

bool init_objects(); /* Only for testing at the moment */
void terminate_objects();
void update_game_objects(float time_elapsed);

#endif /* __GAME_OBJECTS_H__ */