
/* game setttings */

#include "game_main.h"
#include "game_settings.h"

const int DEFAULT_SETTING_DISPLAY_WIDTH = 640;
const int DEFAULT_SETTING_DISPLAY_HEIGHT = 480;
const int DEFAULT_SETTING_TARGET_FPS = 60;
const char* DEFAULT_SETTING_RESOURCE_DIR = "resources/";
const char* DEFAULT_SETTING_FILE = "settings.ini";
const char* GAME_SETTINGS_SECTION = "[GAME SETTINGS]";

static struct {
    int display_width;
    int display_height;
    int target_fps;
} game_settings;

/******************************************************************************
 * Convenience Utility Functions
******************************************************************************/
int load_int_from_cfg( ALLEGRO_CONFIG*, const char* key, int defaultValue );
void save_int_to_cfg(const int* value, ALLEGRO_CONFIG* cfg, const char* key);

/******************************************************************************
 * Utility -- loading integral values from an allegro config
******************************************************************************/
int load_int_from_cfg(
    ALLEGRO_CONFIG* cfg,
    const char* key,
    int defaultValue
) {
    const char* buffer = al_get_config_value(cfg, GAME_SETTINGS_SECTION, key);
    if (buffer)
        return atoi(buffer);
    else
        return defaultValue;
}

/******************************************************************************
 * Utility -- Saving integral values from an allegro config
******************************************************************************/
void save_int_to_cfg(const int* value, ALLEGRO_CONFIG* cfg, const char* key) {
    char buffer[ 15 ] = {0};
    sprintf(buffer, "%i", *value);
    al_set_config_value(cfg, GAME_SETTINGS_SECTION, key, buffer);
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
    game_settings.display_width = load_int_from_cfg(
        cfgData, "displayWidth", DEFAULT_SETTING_DISPLAY_WIDTH
    );

    /* Display Height */
    game_settings.display_height = load_int_from_cfg(
        cfgData, "displayHeight", DEFAULT_SETTING_DISPLAY_HEIGHT
    );

    /* Target FPS */
    game_settings.target_fps = load_int_from_cfg(
        cfgData, "targetFps", DEFAULT_SETTING_TARGET_FPS
    );

    al_fclose(cfgFile);
    al_destroy_config(cfgData);
    
    game_settings.display_width = DEFAULT_SETTING_DISPLAY_WIDTH;
    game_settings.display_height = DEFAULT_SETTING_DISPLAY_HEIGHT;
    game_settings.target_fps = DEFAULT_SETTING_TARGET_FPS;
    
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
    al_add_config_comment(cfgData, NULL, "Global Game Settings");
    al_add_config_section(cfgData, GAME_SETTINGS_SECTION);

    save_int_to_cfg(&game_settings.display_width, cfgData, "displayWidth");
    save_int_to_cfg(&game_settings.display_height, cfgData, "displayHeight");
    save_int_to_cfg(&game_settings.target_fps, cfgData, "targetFps");

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
void settings_get_display_size(int* width, int* height) {
    *width = game_settings.display_width;
    *height = game_settings.display_height;
}

/******************************************************************************
 * GAME_SETTINGS -- SET DISPLAY SIZE
******************************************************************************/
void settings_set_display_size(int width, int height) {
    game_settings.display_width = width;
    game_settings.display_height = height;
}

/******************************************************************************
 * GAME_SETTINGS -- GET TARGET FPS
******************************************************************************/
int settings_get_target_fps(void) {
    return game_settings.target_fps;
}

/******************************************************************************
 * GAME_SETTINGS -- SET TARGET FPS
******************************************************************************/
void settings_set_target_fps(int fps) {
    game_settings.target_fps = fps;
}

/******************************************************************************
 * GAME_SETTINGS -- GET GAME RESOURCE DIRECTORY
******************************************************************************/
const char* settings_get_resource_dir(void) {
    return DEFAULT_SETTING_RESOURCE_DIR;
}