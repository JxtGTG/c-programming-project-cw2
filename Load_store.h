
#ifndef _GUARD_lo 
#define _GUARD_lo
#include <stdio.h>
#include <stdio.h>
#include "utility.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "operate.h"
#include "game.h"
#include <SDL2/SDL_ttf.h>

extern int Width;
extern int High;
extern int delaytime;


//load the data from the specific file to create the world
//return the world pointer
int ** load(FILE* file);


//saves the database of the last world in the specified file
void store(FILE* file,int **cells);


#endif
