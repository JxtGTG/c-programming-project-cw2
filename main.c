#include "game.h"
#include "game.h"
#include "Load_store.h"
#include <stdio.h>
#include "utility.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
    
    char user[100]="my.txt";
    // strcpy(user,argv[1]);
    whole_game(user);
    return 0;
}