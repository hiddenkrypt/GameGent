
#include <SDL.h>
#include <stdio.h>
#include "window.h"

#define RENDERER_COLLECTION_SIZE 50 // currently arbitrary
SDL_Window *mainWindow = NULL;
SDL_Renderer *rendererCollection[RENDERER_COLLECTION_SIZE];
int virtualScreenHeight = 18;
int virtualScreenWidth = 20;
int windowTileMultiplier = 4;
int windowHeight = 8*18*4;
int windowWidth = 8*20*4;

void bestFit();
void resize();

/**
 * @brief Initializes and creates a window
 *
 * Currently initializes SDL for video, tries to opens a window, and reports any error. Also initializes the renderer Collection to all NULL pointers.
 * @todo auto-detect scree resolution and choose appropriate initial window size.
 * @todo choose window size from settings, including auto-detect
 */
void Window_init(){
	mainWindow = SDL_CreateWindow( "GameGent", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
	if ( mainWindow == NULL ) {
		printf( "Window could not be created. SDL Error: %s\n", SDL_GetError() );
		return;
	}
	for(int i=0; i < RENDERER_COLLECTION_SIZE; i++){
		rendererCollection[i] = NULL;
	}
	resize();
}

/**
 * @brief Get a new renderer tied to the window
 *
 * Checks the renderer collection to make sure that it isn't full, and in the process finds the first empty slot.
 * Creates a renderer tied to the window and stores it in the collection for later cleanup.
 * @return SDL_Renderer tied to the window if successful, NULL if any error occurred or the renderer collection is full.
 *
 */
SDL_Renderer *Window_getNewRenderer(){
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
/**
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
void resize(){
	printf( "Resized %dx%d tiles to %dx%d pixels, multiplier:%d\n",virtualScreenWidth,virtualScreenHeight, virtualScreenWidth*8*windowTileMultiplier, virtualScreenHeight*8*windowTileMultiplier,windowTileMultiplier);
	SDL_SetWindowSize(mainWindow, virtualScreenWidth*8*windowTileMultiplier, virtualScreenHeight*8*windowTileMultiplier);
}

/**
 * @brief makes the window as big as can reasonably work
 *
 * Resizes the window to take up as much space in the current screen resolution as possible while maintaining integer multiples of tile sizes
 */
void bestFit(){
	SDL_DisplayMode current;
	int windowDisplayIndex = SDL_GetWindowDisplayIndex(mainWindow);
	int retval= SDL_GetCurrentDisplayMode(windowDisplayIndex, &current);
	if(retval != 0){
	  SDL_Log("Could not get display mode for video display #%d: %s", retval, SDL_GetError());
	} else{
		int scaledWidth = current.w;
		int scaledHeight = (scaledWidth*virtualScreenHeight)/virtualScreenWidth;
		if(scaledHeight > current.h){
			scaledHeight = current.h;
			scaledWidth = (scaledHeight*virtualScreenWidth)/virtualScreenHeight;
		}
		windowTileMultiplier = scaledWidth/160;
		resize();
	}

}

/** \brief react to passed events
 * currently just makes sure to bestFit the screen when the window is moved.
 */
void Window_handleEvent(const SDL_Event * event){
	if( event->window.event == SDL_WINDOWEVENT_MOVED ){
		bestFit();
	}
}
