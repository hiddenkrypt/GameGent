#include <SDL.h>
#include <stdio.h>
#include "gamegent_state.h"
#include "tilemap.h"
#include "menus.h"
#include "main.h"

static int menuIndex = 0;
void drawMenu( SDL_Renderer*  renderer );
void Menus_draw(SDL_Renderer*  renderer, gamegent_state currentState){
    char menuTitle[4][11] = {
        { 148, 159, 159, 159, 159, 159, 159, 159, 159, 149, 0 },
        { 158, 144, 145, 'a', 'm', 'e',  32, 146, 147, 158, '\0' },
        { 158, 152, 153, 'e', 'n', 't',  32, 154, 155, 158, '\0' },
        { 156, 159, 159, 159, 159, 159, 159, 159, 159, 157, 0 }
    };
    tiles_paintStringAt(10-5, 0, menuTitle[0],  renderer );
    tiles_paintStringAt(10-5, 1, menuTitle[1],  renderer );
    tiles_paintStringAt(10-5, 2, menuTitle[2],  renderer );
    tiles_paintStringAt(10-5, 3, menuTitle[3],  renderer );
    switch( currentState ){
        case state_main_menu:
            drawMenu( renderer );
            break;
        default: break; //noop
    }
}
const char mainMenuItemStrings[7][20]= {
    "Continue",
    "Load ROM...",
    "Load State",
    "Save State",
    "State Number:",
    "Options...",
    "EXIT"
};
void drawMenu( SDL_Renderer*  renderer ){
    for(int i = 0; i < 7; i++){
        tiles_paintStringAt(1, 10+i, mainMenuItemStrings[i], renderer );
    }
    //paint background of selected menuitem
    //draw each item in a row
}




void MainMenu_Exit(){
    shutdown();
}
