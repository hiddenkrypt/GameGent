
#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>
#include "gui/gui.h"
#include "dmg/dmg.h"
#include "settings.h"
#include "GameGent.h"

GameGentState GameGent;


/*!
 * @brief Initialize Everything!
 * Initializes the GameGent state, and calls all subsystem init functions.
 * @todo breakout settings to be initialized in another function, with default values and file stored user options
 */
GameGentState static init(){
	Settings_init();
	DMG_init();
	GameGentState GameGent;
	GameGent.quit = false;
	GameGent.inMenu = false;

	GameGent.renderer = GUI_init();
	if ( GameGent.renderer == NULL ) {
		printf("Window Initialization Failure!");
		GameGent.quit = true;
	}
	return GameGent;
}


/*!
 * @brief top level program cleanup
 *
 * Calls all subsystem cleanup/shutdown functions.
 */
void static shutdown(){
	GUI_shutdown();
};

/*!
 * @brief program entry, main loop
 *
 * Main is the program entry point. It calls all the initializers, runs the core program loop, and calls all the sleanup/shutdown functions.
 */
int main ( int argn, char* args[] ) {
	GameGent = init();
	SDL_Event e;
	while( !GameGent.quit ) {
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				GameGent.quit = true;
			}
			GUI_handleEvent( e );
		}
		GUI_draw( GameGent );
		DMG_tick();
	}

	shutdown();
	return 0;
}

/*!
 * @brief causes the program to shutdown.
 *
 * Calls all subsystem cleanup/shutdown functions.
 */
void GameGent_shutdown(){
	GameGent.quit = true;
};
