#include <SDL.h>
#include <stdio.h>
#include "GameGent.h"
#include "tilemap.h"
#include "menuManager.h"
#include "mainMenu.h"
#include "menu.h"

static int menuIndex = 0;
static Menu currentMenu;

void MenuManager_init(){
    currentMenu = MainMenu_getMenu();
    menuIndex = 0;
}
/** \brief draw the current menu
 *
 * draws a menu based on the current state variable.
 * @param renderer the renderer tied to the window we want to put the menu on
 * @param the current state of the program
 *
 */
void MenuManager_draw(SDL_Renderer*  renderer){
    char menuTitle[4][11] = {
        { 148, 159, 159, 159, 159, 159, 159, 159, 159, 149, 0 },
        { 158, 144, 145, 'a', 'm', 'e',  32, 146, 147, 158, '\0' },
        { 158, 152, 153, 'e', 'n', 't',  32, 154, 155, 158, '\0' },
        { 156, 159, 159, 159, 159, 159, 159, 159, 159, 157, 0 }
    };
    Tiles_paintStringAt(10-5, 0, menuTitle[0],  renderer );
    Tiles_paintStringAt(10-5, 1, menuTitle[1],  renderer );
    Tiles_paintStringAt(10-5, 2, menuTitle[2],  renderer );
    Tiles_paintStringAt(10-5, 3, menuTitle[3],  renderer );

    currentMenu.draw( renderer, menuIndex );
}


/** \brief menu item cursor go down
 *
 * increments the menu index, selecting the "next" menu item
 *
 */
void MenuManager_incrementMenuIndex(){
    if (menuIndex >= currentMenu.itemCount-1){
        menuIndex = 0;
    } else {
        menuIndex++;
    }
}
/** \brief menu item cursor go up
 *
 * decrements the menu index, selecting the "previous" menu item
 *
 */
void MenuManager_decrementMenuIndex(){
    if ( menuIndex <= 0){
        menuIndex = currentMenu.itemCount;
    }
    menuIndex--;
}

void MenuManager_activateCurrentMenuItem(){
    currentMenu.activate(menuIndex);
}
