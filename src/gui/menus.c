#include <SDL.h>
#include <stdio.h>
#include "gamegent_state.h"
#include "tilemap.h"
#include "menus.h"
#include "mainMenu.h"

static int menuIndex = 0;

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
            MainMenu_draw( renderer, menuIndex );
            break;
        default: break; //noop
    }
    if (menuIndex < 5) menuIndex++; // dirty index scrolling hack to show/test effects
}
