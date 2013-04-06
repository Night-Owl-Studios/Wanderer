
/* simple game using allegro */

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "game_main.h"
#include "game_settings.h"
#include "game_system.h"
#include "game_objects.h"

static const char* game_name = "Test Game";
static const char* game_organization = "Night Owl Studios";

/******************************************************************************
 *  ENGINE INITIALIZATION
******************************************************************************/
bool init( void ) {
    /* Initialize Allegro */
    if (!al_init()) {
        printf("An error occurred while initializing Allegro.\n");
        return false;
    }

    /* Initialize Allegro's primitives addon */
    if (!al_init_primitives_addon()) {
        printf("An Error occurred while initializing primitives.\n");
        return false;
    }

    /* Initialize Allegro's font addons */
    al_init_font_addon();
    if (!al_init_ttf_addon()) {
        printf("An Error occurred while initializing font addons.\n");
        return false;
    }

    /* Initialize the keyboard driver */
    if (!al_install_keyboard()) {
        printf("An error occurred while installing the keyboard driver.\n");
        return false;
    }

    /* Initialize the game's settings */
    if (!init_settings()) {
        printf(
            "An error occurred while loading the game startup config file. "\
			"The game will initialize with default settings.\n"
        );
        return false;
    }

    /* Initialize the main event system */
    if (!init_system()) {
        printf("An error occurred while starting the games's subsystems.\n");
        return false;
    }

    if (!init_objects()) {
        printf(
            "An error occurred while initializing the game objects. "\
			"Aborting the program.\n"
        );
        return false;
    }

    printf("Successfully initialized the game engine.\n");
    return true;
}

/******************************************************************************
 *  main()
******************************************************************************/
int main(void) {
    al_set_org_name(game_organization);
    al_set_app_name(game_name);

    if (!init())
        return -1;

    sys_do_main_loop();

    /* cleanup */
    terminate_objects();
    terminate_system();

    return 0;
}
