
#include <SDL.h>
#include <stdio.h>
#include "window.h"

static SDL_Window* mainWindow = NULL;
static SDL_Renderer* mainRenderer = NULL;

static const int LCD_HEIGHT = 144;
static const int LCD_WIDTH = 160;
static int windowWidth = 160*3;
static int windowHeight = 144*3;

/*!
 * @brief Initializes and creates a window
 *
 * Currently initializes SDL for video, opens a window, and creates a renderer tied to the window
 * @todo auto-detect scree resolution and choose appropriate window size.
 * @todo choose window size from settings, including auto-detect
 * @todo add handling for window resize events
 */
SDL_Renderer* Window_init(){
    mainWindow = SDL_CreateWindow( "GameGent", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE  );
    if ( mainWindow == NULL ) {
        printf( "Window could not be created. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
    mainRenderer = SDL_CreateRenderer( mainWindow, -1, SDL_RENDERER_ACCELERATED );
    if ( mainRenderer == NULL ) {
        printf( "Renderer could not be created. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
	return mainRenderer;
}

/*!
 * @brief cleans up memory objects related to the window
 *
 * Closes and frees the window, and it's tied renderer
 */
void Window_shutdown(){
	SDL_DestroyWindow( mainWindow );
	SDL_DestroyRenderer( mainRenderer );
}
