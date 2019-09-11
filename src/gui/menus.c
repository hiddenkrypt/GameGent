#include <SDL.h>
#include <stdio.h>
#include "gamegent_state.h"
#include "tilemap.h"
#include "menus.h"


void Menus_draw(SDL_Renderer*  renderer, gamegent_state currentState){
    switch( currentState ){
        case state_main_menu:
            drawMainMenu( renderer );
            break;
        default: break; //noop
    }
}

void drawMainMenu( SDL_Renderer*  renderer ){
    char menuStringLine1[8] = { 144, 145, 'a', 'm', 'e', 146, 147, '\0' };
    char menuStringLine2[8] = { 152, 153, 'e', 'n', 't', 154, 155, '\0' };
    tiles_paintStringAt(10-3, 1, menuStringLine1,  renderer );
    tiles_paintStringAt(10-3, 2, menuStringLine2,  renderer );
    //tiles_paintCharAt(10-3,1,255,renderer);
    //draw title first
    //then each item in a row
}

