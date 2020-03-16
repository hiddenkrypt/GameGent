#include <SDL.h>
#include <string.h>
#include "tilemap.h"
#include "mainMenu.h"
#include "menu.h"
#include "menuItem.h"
#include "GameGent.h"
#include "dmg.h"

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
void noop(){}
bool always(){return true;}
bool continueCondition(){
    return DMG_isEmulating();
}
char* continueLabel(){
    return "Continue";
}
char* loadRomLabel(){
    return "Load ROM";
}
char* loadStateLabel(){
    return "Load State";
}
char* saveStateLabel(){
    return "Save State";
}
char* stateNumberLabel(){
    return "State Number:"; // append current state number
}
char* optionsLabel(){
    return "Options...";
}
char* exitLabel(){
    return "EXIT";
}
static menuItem menuItems[7] = {
    {&noop,&DMG_isEmulating,&continueLabel},
    {&noop,&always,&loadRomLabel},
    {&noop,&DMG_isEmulating,&loadStateLabel},
    {&noop,&DMG_isEmulating,&saveStateLabel},
    {&noop,&DMG_isEmulating,&stateNumberLabel},
    {&noop,&always,&optionsLabel},
    {&GameGent_shutdown,&always,&exitLabel}
};
static int itemsCount = 7;


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

void static draw( SDL_Renderer* renderer, int menuCursorIndex ) {

    SDL_Rect cursorRect = { 0, (10+menuCursorIndex)*8, (strlen(mainMenuStrings[menuCursorIndex])*8)+8, 8 };
    SDL_SetRenderDrawColor( renderer, 0xff, 0xff, 0xff, 0xaf );
    SDL_RenderFillRect( renderer, &cursorRect );
    Tiles_paintCharAt(0, 10+menuCursorIndex, 138 + (menuCursorIndex%4), renderer );

    for( int i = itemsCount-1; i>0; i-- ) {
        if( menuItems[i].activeCondition() ) {
            Tiles_paintStringAt(1, 17-i, menuItems[i].getLabel(), renderer );
        }
    }
//    for(int i = 0; i < 7; i++){
//        Tiles_paintStringAt(1, 10+i, mainMenuStrings[i], renderer );
//    }
}

Menu MainMenu_getMenu(){
    Menu mainMenu;
    mainMenu.itemCount = MAIN_MENU_ITEMS;
    mainMenu.activate = &activateItem;
    mainMenu.draw = &draw;

    return mainMenu;
}




