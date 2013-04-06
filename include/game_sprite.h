/* 
 * File:   game_sprite.h
 * Author: hammy
 *
 * Created on April 2, 2013, 2:34 AM
 */

#ifndef __GAME_SPRITE_H__
#define	__GAME_SPRITE_H__

#include <allegro5/allegro.h>

typedef struct {
    int numFrames;
    ALLEGRO_BITMAP* frames;
} sprite_t;

bool sprite_load( sprite_t*, const char* filename );
void sprite_unload( sprite_t* );
void sprite_draw( const sprite_t*, int frame );

#endif	/* __GAME_SPRITE_H__ */

