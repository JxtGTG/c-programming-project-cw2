#ifndef _GUARD_g
#define _GUARD_g

#include "Load_store.h"
#include <stdio.h>
#include "utility.h"
#include <stdbool.h>

//function to create the world
//return the world pointer if the world created correctly
int **create();


//game evolve to the terminal
//return 1 if the world is not end when exit
//return 0 when the world is end
int run_terminal(int**cells);


//input world to evolve for input steps
//return 1 if the world is not end when exit
//return 0 when the world is end
int run_step(int **cells,int y);


//function of  whole process of a world's evolution
//return 1 if the world is not end when exit
//return 0 when the world is end
int  game(int ** cell);


//The whole game system
void  whole_game(char * filename);


#endif