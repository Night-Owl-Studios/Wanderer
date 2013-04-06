/* 
 * File:   util_functions.h
 * Author: hammy
 *
 * Created on April 3, 2013, 10:06 PM
 */

#ifndef __GAME_UTILS_H__
#define	__GAME_UTILS_H__

#include <stdbool.h>

/******************************************************************************
		MACROS
******************************************************************************/
#ifndef NULL
	#define NULL ((void*)0)
#endif

#ifndef NEW_OBJECT
    #define NEW_OBJECT( type ) (type*)malloc( sizeof(type) )
#endif

#ifndef NEW_ARRAY
    #define NEW_ARRAY( type, amount ) (type*)calloc( amount, sizeof(type)*amount )
#endif

#ifndef FREE_MEMORY
    #define FREE_MEMORY( x ) free( x ); x = NULL
#endif

/******************************************************************************
		INLINE FUNCTIONS
******************************************************************************/
static inline int get_max_i( int x, int y ) {
	return x > y ? x : y;
}

static inline int get_min_i( int x, int y ) {
	return x < y ? x : y;
}

static inline float get_max_f( float x, float y ) {
	return x > y ? x : y;
}

static inline float get_min_f( float x, float y ) {
	return x < y ? x : y;
}

/******************************************************************************
 ERROR PRINTING
******************************************************************************/
/* Prints to the console */
void print_log( const char* str, ... );
void print_msg( const char* str, ... );

/* Prints to a message box */
void print_err( const char* str, ... );
void print_ok( const char* str, ... );

bool file_exists( const char* filename );

#endif	/* __GAME_UTILS_H__ */

