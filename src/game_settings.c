
/* game setttings */

#include "game_main.h"
#include "game_settings.h"

const int DEFAULT_SETTING_DISPLAY_WIDTH = 640;
const int DEFAULT_SETTING_DISPLAY_HEIGHT = 480;
const int DEFAULT_SETTING_TARGET_FPS = 60;
const char* DEFAULT_SETTING_RESOURCE_DIR = "resources/";
const char* DEFAULT_SETTING_FILE = "settings.ini";

static struct {
    int displayWidth;
    int displayHeight;
    int targetFps;
} game_settings;

/******************************************************************************
 * Convenience Utility Functions
******************************************************************************/
void loadIntFromConfig(
    int* value, ALLEGRO_CONFIG* cfg, const char* key, int defaultValue
);
void saveIntToConfig(const int* value, ALLEGRO_CONFIG* cfg, const char* key);

/******************************************************************************
 * Utility -- loading integral values from an allegro config
******************************************************************************/
void loadIntFromConfig(
    int* value, ALLEGRO_CONFIG* cfg, const char* key, int defaultValue
) {
    const char* buffer = al_get_config_value(cfg, "GAME_SETTINGS", key);
    if (buffer)
        *value = atoi(buffer);
    else
        *value = defaultValue;

    if (!(*value))
        *value = defaultValue;
}

/******************************************************************************
 * Utility -- Saving integral values from an allegro config
******************************************************************************/
void saveIntToConfig(const int* value, ALLEGRO_CONFIG* cfg, const char* key) {
    char buffer[ 15 ] = {0};
    sprintf(buffer, "%i", *value);
    al_set_config_value(cfg, "GAME_SETTINGS", key, buffer);
}

/******************************************************************************
 * GAME_SETTINGS -- RESETTING
******************************************************************************/
bool init_settings(void) {
    ALLEGRO_CONFIG* cfgData = NULL;
    ALLEGRO_FILE* cfgFile = al_fopen(DEFAULT_SETTING_FILE, "r");
    if (cfgFile == NULL) {
        printf(
            "ERROR: Unable to load the game config file %s.\n",
            DEFAULT_SETTING_FILE
        );
        return false;
    }

    cfgData = al_load_config_file_f(cfgFile);
    if (cfgData == NULL) {
        printf(
            "ERROR: Unable to load the game config data %s.\n",
            DEFAULT_SETTING_FILE
        );
        return false;
    }

    /* Read in the game settings, one by one */
    /* Display Width */
    loadIntFromConfig(
        &game_settings.displayWidth, cfgData,
        "displayWidth", DEFAULT_SETTING_DISPLAY_WIDTH
    );

    /* Display Height */
    loadIntFromConfig(
        &game_settings.displayHeight, cfgData,
        "displayHeight", DEFAULT_SETTING_DISPLAY_HEIGHT
    );

    /* Target FPS */
    loadIntFromConfig(
        &game_settings.targetFps, cfgData,
        "targetFps", DEFAULT_SETTING_TARGET_FPS
    );

    al_fclose(cfgFile);
    al_destroy_config(cfgData);
    
    game_settings.displayWidth = DEFAULT_SETTING_DISPLAY_WIDTH;
    game_settings.displayHeight = DEFAULT_SETTING_DISPLAY_HEIGHT;
    game_settings.targetFps = DEFAULT_SETTING_TARGET_FPS;
    
    return true;
}

/******************************************************************************
 * GAME_SETTINGS -- SAVING
******************************************************************************/
int settings_save(void) {
    ALLEGRO_CONFIG* cfgData = NULL;
    ALLEGRO_FILE* cfgFile = NULL;
    bool ret = false;

    cfgData = al_create_config();
    if (cfgData == NULL) {
        printf(
            "ERROR: Unable to create the game config data: %s.\n",
            DEFAULT_SETTING_FILE
        );
        return false;
    }
    al_add_config_section(cfgData, "GAME_SETTINGS");
    al_add_config_comment(cfgData, "GAME_SETTINGS", "Global Game Settings");

    saveIntToConfig(&game_settings.displayWidth, cfgData, "displayWidth");
    saveIntToConfig(&game_settings.displayHeight, cfgData, "displayHeight");
    saveIntToConfig(&game_settings.targetFps, cfgData, "targetFps");

    cfgFile = al_fopen(DEFAULT_SETTING_FILE, "w");
    if (cfgFile == NULL) {
        printf(
            "ERROR: Unable to open the game config output stream: %s.\n",
            DEFAULT_SETTING_FILE
        );
        al_destroy_config(cfgData);
        return false;
    }
    if (al_save_config_file_f(cfgFile, cfgData) == 0) {
        printf(
            "ERROR: Unable to save the game config file: %s.\n",
            DEFAULT_SETTING_FILE
        );
        ret = false;
    }

    al_fclose(cfgFile);
    al_destroy_config(cfgData);

    return ret;
}

/******************************************************************************
 * GAME_SETTINGS -- GET DISPLAY SIZE
******************************************************************************/
void settings_getDisplaySize(int* width, int* height) {
    *width = game_settings.displayWidth;
    *height = game_settings.displayHeight;
}

/******************************************************************************
 * GAME_SETTINGS -- SET DISPLAY SIZE
******************************************************************************/
void settings_setDisplaySize(int width, int height) {
    game_settings.displayWidth = width;
    game_settings.displayHeight = height;
}

/******************************************************************************
 * GAME_SETTINGS -- GET TARGET FPS
******************************************************************************/
int settings_getTargetFps(void) {
    return game_settings.targetFps;
}

/******************************************************************************
 * GAME_SETTINGS -- SET TARGET FPS
******************************************************************************/
void settings_setTargetFps(int fps) {
    game_settings.targetFps = fps;
}

/******************************************************************************
 * GAME_SETTINGS -- GET GAME RESOURCE DIRECTORY
******************************************************************************/
const char* settings_getResourceDir(void) {
    return DEFAULT_SETTING_RESOURCE_DIR;
}

/******************************************************************************
 * GAME_SETTINGS -- GET SETTINGS FILE NAME
******************************************************************************/
const char* settings_getSettingsFileName(void) {
    return DEFAULT_SETTING_FILE;
}
