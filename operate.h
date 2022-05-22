#ifndef _GUARD_o
#define _GUARD_o

#include <SDL2/SDL.h>

#include <stdbool.h>
#include<stdio.h>
#include"utility.h"
#include "Load_store.h"
//function for user to create the world in a input way
//return the pointer of the world if it is created correctly
int **input_create();


//get the user's expectative world size
void getsize();


//for user to click for world creation
//return the pointer of the created world
int **click_create();


//function for the visualization of the world
void show(SDL_Renderer* sdlRenderer,SDL_Window* sdlWindow,SDL_Texture* sdlTexture,int** cells);


void showlabel(SDL_Renderer* sdlRenderer,SDL_Window* sdlWindow,SDL_Texture* sdlTexture,int** cells,SDL_Surface *sdlsurface,SDL_Texture * texture,SDL_Rect dstrect);
//copy a world data to create a new world
//return the newly created world pointer
int ** copy(int **cells);


//Judge if the input two world are the same
//return 1 if they are different
//return 0 if they are same
int judge(int **cells,int **lastcells);


//function to update the input world to the next generation
void updateWithoutInput(int **cells);


//free the allocated space for world
void freecell(int **cells);


//close the SDL related element
void close(SDL_Window* sdlWindow,SDL_Texture*sdlTexture,SDL_Renderer * sdlRenderer);


//delete the input string's space
void  mydelete(char *str);

//change the cell to be alive state
void changeblack(int x,int y,int**cells);


//change the cell to be dead state
void changewhite(int x,int y,int**cells);

//click to change the board
void changecell(int **cell);


#endif
