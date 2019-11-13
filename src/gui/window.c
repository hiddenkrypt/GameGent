
#include <SDL.h>
#include <stdio.h>
#include "window.h"

#define RENDERER_COLLECTION_SIZE 50
static SDL_Window* mainWindow = NULL;
static SDL_Renderer* rendererCollection[RENDERER_COLLECTION_SIZE];

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
void Window_init(){
    mainWindow = SDL_CreateWindow( "GameGent", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE  );
    if ( mainWindow == NULL ) {
        printf( "Window could not be created. SDL Error: %s\n", SDL_GetError() );
        return;
    }
    for(int i=0; i < RENDERER_COLLECTION_SIZE; i++){
        rendererCollection[i] = NULL;
    }
}


SDL_Renderer* Window_getNewRenderer(){
    int i = 0;
    while ( i < RENDERER_COLLECTION_SIZE && rendererCollection[i] != NULL ) {
        i++;
    }
    if ( i == RENDERER_COLLECTION_SIZE ) {
       printf( "WINDOW ERROR: Max renderers allocated!");
       return NULL;
    }
    SDL_Renderer* newRenderer = SDL_CreateRenderer( mainWindow, -1, SDL_RENDERER_ACCELERATED );
    if ( newRenderer == NULL ) {
        printf( "Renderer could not be created. SDL Error: %s\n", SDL_GetError() );
        return NULL;
    }
    rendererCollection[i] = newRenderer;
	return newRenderer;
}
/*!
 * @brief cleans up memory objects related to the window
 *
 * Closes and frees the window, and it's tied renderer
 */
void Window_shutdown(){
	SDL_DestroyWindow( mainWindow );
    for(int i=0; i < RENDERER_COLLECTION_SIZE; i++){
        SDL_DestroyRenderer( rendererCollection[i] );
    }
}
