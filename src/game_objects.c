
/* game objects */
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "game_main.h"
#include "game_system.h"
#include "game_inputs.h"
#include "game_objects.h"

static ALLEGRO_FONT*    test_font = NULL;
static const char*      test_font_file = "test_font.ttf";

/* Tests to run to make sure that the input system is working */
void drawRight() {
    ALLEGRO_DISPLAY* display = al_get_current_display();
    float display_width = al_get_display_width(display) * 0.75f;
    float display_height = al_get_display_height(display) * 0.5f;

    al_draw_filled_rectangle(
        display_width - 16, display_height - 16,
        display_width + 16, display_height + 16,
        al_map_rgb(0, 255, 0)
    );
    
    al_draw_text(
        test_font, al_map_rgb(255, 255, 255),
        display_width, display_height, ALLEGRO_ALIGN_LEFT, "R"
    );
}

void drawLeft() {
    ALLEGRO_DISPLAY* display = al_get_current_display();
    float display_width = al_get_display_width(display) * 0.25f;
    float display_height = al_get_display_height(display) * 0.5f;

    al_draw_filled_rectangle(
        display_width - 16, display_height - 16,
        display_width + 16, display_height + 16,
        al_map_rgb(0, 255, 0)
    );
    
    al_draw_text(
        test_font, al_map_rgb(255, 255, 255),
        display_width, display_height, ALLEGRO_ALIGN_LEFT, "L"
    );
}

/******************************************************************************
 *	OBJECT -- TERMINATION
******************************************************************************/
void terminate_objects() {
    if (test_font)
        al_destroy_font(test_font);
    test_font = NULL;
}

/******************************************************************************
 *	OBJECT -- INITIALIZATION
******************************************************************************/
bool init_objects() {
    if (test_font)
        return true;

    test_font = al_load_ttf_font(test_font_file, 24, 0);
    if (!test_font) {
        printf(
            "An error occurred while loading the test font: %s. Aborting.\n",
            test_font_file
        );
        return false;
    }
    
    keyboard_set_callback(ALLEGRO_KEY_ESCAPE, true, &sys_signal_game_quit);
    keyboard_set_callback(ALLEGRO_KEY_D, true, &drawRight);
    keyboard_set_callback(ALLEGRO_KEY_A, true, &drawLeft);

    return true;
}

/******************************************************************************
 *	OBJECT -- GLOBAL UPDATING
******************************************************************************/
void update_game_objects(float time_elapsed) {
    ALLEGRO_DISPLAY* display = al_get_current_display();
    float display_width = al_get_display_width(display) * 0.5f;
    float display_height = al_get_display_height(display) * 0.25f;
    
    al_draw_textf(
        test_font, al_map_rgb(255, 255, 255),
        display_width, display_height, ALLEGRO_ALIGN_CENTRE,
        "Updates per second: %f", time_elapsed
    );
}
