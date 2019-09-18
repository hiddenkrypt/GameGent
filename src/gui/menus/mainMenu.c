#include <SDL.h>
#include <string.h>
#include "tilemap.h"
#include "mainMenu.h"
#include "menu.h"


const static int MAIN_MENU_ITEMS = 7;
const static char mainMenuStrings[7][20]= {
    "Continue",
    "Load ROM...",
    "Load State",
    "Save State",
    "State Number:",
    "Options...",
    "EXIT"
};

void static activateItem(int itemIndex){
    switch ( itemIndex ){
    case 0: // Continue
        break;
    case 1: // Load Rom
        break;
    case 2: // Load State
        break;
    case 3: // Save State
        break;
    case 4: // State Number
        break;
    case 5: // Options Menu
        break;
    case 6: // exit
        GameGent_shutdown();
        break;
    }
};

void static draw( SDL_Renderer* renderer, int menuCursorIndex ){
    SDL_Rect cursorRect = { 0, (10+menuCursorIndex)*8, (strlen(mainMenuStrings[menuCursorIndex])*8)+8, 8 };
    SDL_SetRenderDrawColor( renderer, 0xff, 0xff, 0xff, 0xaf );
    SDL_RenderFillRect( renderer, &cursorRect );

    Tiles_paintCharAt(0, 10+menuCursorIndex, 138 + (menuCursorIndex%4), renderer );

    for(int i = 0; i < 7; i++){
        Tiles_paintStringAt(1, 10+i, mainMenuStrings[i], renderer );
    }
}

Menu MainMenu_getMenu(){
    Menu mainMenu;
    mainMenu.itemCount = MAIN_MENU_ITEMS;
    mainMenu.activate = &activateItem;
    mainMenu.draw = &draw;

    return mainMenu;
}
