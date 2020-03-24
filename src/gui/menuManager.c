#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include "../../GameGent.h"
#include "keyCommands.h"
#include "tilemap.h"
#include "menus/menu.h"
#include "menus/mainMenu.h"
#include "menuManager.h"

static int menuCursorIndex = 0;
static menu currentMenu;


/** \brief starts the MenuManager
 *
 * initializes the main menu and, currently, sets up the main menu on program start.
 * @todo probably? like maybe? have the option to launch right into the emulator with a game loaded?
 *
 */

void MenuManager_init(){
	currentMenu = MainMenu_getMenu();
	menuCursorIndex = 0;
}

/** \brief draw the current menu
 *
 * draws a menu based on the current state variable.
 * @param renderer the renderer tied to the window we want to put the menu on
 * @param the current state of the program
 *
 */
void MenuManager_draw( SDL_Renderer*  renderer ){
	char menuTitle[4][11] = {
		{ 148, 159, 159, 159, 159, 159, 159, 159, 159, 149, 0 },
		{ 158, 144, 145, 'a', 'm', 'e',  32, 146, 147, 158, '\0' },
		{ 158, 152, 153, 'e', 'n', 't',  32, 154, 155, 158, '\0' },
		{ 156, 159, 159, 159, 159, 159, 159, 159, 159, 157, 0 }
	};
	Tiles_paintStringAt( 10 - 5, 0, menuTitle[0],  renderer );
	Tiles_paintStringAt( 10 - 5, 1, menuTitle[1],  renderer );
	Tiles_paintStringAt( 10 - 5, 2, menuTitle[2],  renderer );
	Tiles_paintStringAt( 10 - 5, 3, menuTitle[3],  renderer );

	for( int i = 0; i < currentMenu.itemCount(); i++ ) {
		char itemLabel[20];
		currentMenu.getLabel(i, itemLabel);
		if( i == menuCursorIndex ){
			SDL_Rect cursorRect = {
				0,
				( 17 - currentMenu.itemCount( ) + menuCursorIndex ) * 8,
				( strlen( itemLabel ) * 8 ) + 8,
				8
			};
			SDL_SetRenderDrawColor( renderer, 0xff, 0xff, 0xff, 0xaf );
			SDL_RenderFillRect( renderer, &cursorRect );
			Tiles_paintCharAt( 0, 17 - currentMenu.itemCount()+menuCursorIndex, 138 + ( menuCursorIndex % 4 ), renderer );
		}
		Tiles_paintStringAt( 1, 17 - currentMenu.itemCount() + i, itemLabel, renderer );
	}
}


/** \brief menu item cursor go down
 *
 * increments, with bounds looping, the menu index, selecting the "next" menu item
 *
 */
void MenuManager_incrementMenuIndex(){
	if (menuCursorIndex >= currentMenu.itemCount()-1){
		menuCursorIndex = 0;
	} else {
		menuCursorIndex++;
	}
}
/** \brief menu item cursor go up
 *
 * decrements, with bounds looping, the menu index, selecting the "previous" menu item
 *
 */
void MenuManager_decrementMenuIndex(){
	if ( menuCursorIndex <= 0){
		menuCursorIndex = currentMenu.itemCount();
	}
	menuCursorIndex--;
}

/** \brief do the thing that the selected menu item does
 *
 * tells the current menu to activate the current menu item.
 */
void MenuManager_activateCurrentMenuItem(){
	currentMenu.activateItem( menuCursorIndex );
}
void MenuManager_setMenu( menu newMenu ){
	currentMenu = newMenu;
	menuCursorIndex = 0;
}
void MenuManager_handleCommand( keyCommand command ){
	if( command == UP ){
		MenuManager_decrementMenuIndex();
	}
	if( command == DOWN ){
		MenuManager_incrementMenuIndex();
	}
	if( command == A ){
		MenuManager_activateCurrentMenuItem();
	}
}
