#include <SDL.h>
#include <string.h>
#include "tilemap.h"
#include "mainMenu.h"



const char mainMenuStrings[7][20]= {
    "Continue",
    "Load ROM...",
    "Load State",
    "Save State",
    "State Number:",
    "Options...",
    "EXIT"
};

void MainMenu_draw( SDL_Renderer* renderer, int menuCursorIndex ){

    SDL_Rect cursorRect = { 0, (10+menuCursorIndex)*8, (strlen(mainMenuStrings[menuCursorIndex])*8)+8, 8 };
    SDL_SetRenderDrawColor( renderer, 0xff, 0xff, 0xff, 0xaf );
    SDL_RenderFillRect( renderer, &cursorRect );
    tiles_paintCharAt(0, 10+menuCursorIndex, 138 + (menuCursorIndex%4), renderer );
    for(int i = 0; i < 7; i++){
        tiles_paintStringAt(1, 10+i, mainMenuStrings[i], renderer );
    }
}
