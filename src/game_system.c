
// Game Systems

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "game_main.h"
#include "game_settings.h"
#include "game_inputs.h"
#include "game_system.h"
#include "game_objects.h"

static ALLEGRO_EVENT_QUEUE* system_event_queue = NULL;
static ALLEGRO_TIMER* system_timer = NULL;
static bool system_is_running = true;
static ALLEGRO_DISPLAY* system_display = NULL;

/******************************************************************************
 *  Display Initialization
******************************************************************************/
bool system_init_display(void) {
    int width, height;
    al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE); /* disables vsync */
    al_set_new_display_flags( ALLEGRO_OPENGL );

    settings_getDisplaySize(&width, &height);
    system_display = al_create_display(width, height);

    if (!system_display)
        return false;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    return true;
}

/******************************************************************************
 *  Event Initialization
******************************************************************************/
bool system_init_events(void) {

    return true;
}

/******************************************************************************
 * SYSTEM -- GAME INITIALIZATION
******************************************************************************/
bool init_system(void) {
    /* Initialize the main display */
    if (!system_init_display()) {
        printf("An error occurred while initializing the display.\n");
        return false;
    }

    /* Initialize the system timer */
    system_timer = al_create_timer(1.0 / settings_getTargetFps());
    if (!system_timer) {
        printf("An error occurred while initializing the game timer.\n");
        return false;
    }
    
    system_event_queue = al_create_event_queue();
    if (!system_event_queue)
        return false;

    /* Register events from the display */
    al_register_event_source(
        system_event_queue, al_get_display_event_source(system_display)
    );

    /* register the keyboard timer */
    al_register_event_source(
        system_event_queue, al_get_keyboard_event_source()
    );

    /* register the system timer */
    al_register_event_source(
        system_event_queue, al_get_timer_event_source(system_timer)
    );

    printf("Successfully initialized the game's subsystems.\n");
    return true;
}

/******************************************************************************
 * SYSTEM -- GAME TERMINATION
******************************************************************************/
void system_shutdown(void) {
    (void) settings_save();
    al_destroy_event_queue(system_event_queue);
    al_destroy_display(system_display);
    al_destroy_timer(system_timer);
}

/******************************************************************************
 * SYSTEM -- SIGNAL PROGRAM TERMINATION
******************************************************************************/
void system_signal_game_quit(void) {
    system_is_running = false;
}

/******************************************************************************
 * SYSTEM -- GAME LOOP
******************************************************************************/
void system_do_main_loop(void) {
    /* Game Tick Counting */
    double prev_time_count = 0.0;
    double curr_time_count = 0.0;
    double system_tick_time = 0.0;
    system_is_running = true; /* Determines when to quit */
    bool redraw = true; /* Determines when to update the display */
    ALLEGRO_EVENT system_event;

    al_start_timer(system_timer);

    /* game loop */
    while (system_is_running) {
        al_wait_for_event(system_event_queue, &system_event);
        al_set_target_backbuffer( system_display );
        
        switch(system_event.type) {
            /* Determine if a redraw should be performed */
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
            /* Send keyboard information to the input system */
            case ALLEGRO_EVENT_KEY_CHAR:
            case ALLEGRO_EVENT_KEY_DOWN:
                keyboard_notify(system_event.keyboard.keycode, true);
                break;
            case ALLEGRO_EVENT_KEY_UP:
                keyboard_notify(system_event.keyboard.keycode, false);
                break;
            /* Handle all display events */
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                system_is_running = false;
                break;
        }
        
        /* place all game update code here */
        if (redraw == true && al_is_event_queue_empty(system_event_queue)) {
            /* update the game tick time */
            prev_time_count = curr_time_count;
            curr_time_count = al_get_time();
            system_tick_time = curr_time_count - prev_time_count;
            
            /* Update the engine's inputs */
            update_game_inputs();
            
            /* Update the game-specific code */
            update_game_objects(system_tick_time);
            
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            redraw = false;
        }
    }
    /* End game loop */
}
