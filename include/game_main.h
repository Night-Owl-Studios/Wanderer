
#ifndef __GAME_MAIN_H__
#define __GAME_MAIN_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include "game_utils.h"

#ifndef NULL
    #define NULL (void*)0
#endif

#ifdef DEBUG
    #define DEBUG_TRACE printf(\
        "DEBUG_INFO:\n\tFunction: %s\n\tLine: %i\n\tFile: %s\n",\
        __func__, __LINE__, __FILE__\
    )
#endif

#endif /* __GAME_MAIN_H__ */