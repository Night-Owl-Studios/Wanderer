
/* Global Game Settings */

#ifndef __GAME_SETTINGS_H__
#define __GAME_SETTINGS_H__

#include "game_main.h"

enum {
    GAME_LOAD_SUCCESS,
    GAME_LOAD_ERROR,
    GAME_SAVE_SUCCESS,
    GAME_SAVE_ERROR
};

bool init_settings(void);

int settings_save(void);

void settings_get_display_size(int* width, int* height);
void settings_set_display_size(int width, int height);

int settings_get_target_fps(void);
void settings_set_target_fps(int fps);

const char* settings_get_resource_dir(void);

#endif /* __GAME_SETTINGS_H__ */
