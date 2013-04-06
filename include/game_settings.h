
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

void settings_getDisplaySize(int* width, int* height);
void settings_setDisplaySize(int width, int height);

int settings_getTargetFps(void);
void settings_setTargetFps(int fps);

const char* settings_getResourceDir(void);

const char* settings_getSettingsFileName(void);

#endif /* __GAME_SETTINGS_H__ */
