
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <SDL.h>

#include "tilemap.h"


const char* CHARACTER_MAP_PATH = "img/CharacterTileMap.bmp";
SDL_Texture* charMap = NULL;

/** \brief sets up the tilemap module
 * loads the tilemap bitmap as a SLD texture, and holds it for later use
 * @note consider maintaining an internal reference to the renderer, since the same one should be used to draw tiles later
 * \param the window renderer we are going to use the tilemap with.
 */
bool Tiles_init( SDL_Renderer* renderer ){
	SDL_Surface* loadedSurface = SDL_LoadBMP( CHARACTER_MAP_PATH );

	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", CHARACTER_MAP_PATH, SDL_GetError() );
		return false;
	}
	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );
	charMap = SDL_CreateTextureFromSurface( renderer, loadedSurface );
	SDL_FreeSurface( loadedSurface );
	if( charMap == NULL ) {
		printf( "Unable to create texture from %s! SDL Error: %s\n", CHARACTER_MAP_PATH, SDL_GetError() );
		return false;
	}
	return true;
}

/** \brief draw a single tile character at the specified postion on the renderer
 * clips a tile off the tilemap and copies it to the render at the given (x,y)
 * position. Tiles are 8x8 pixels, and the x,y is treated as a tile position but
 * copied as a pixel position. The real pixel top left corner of the tile will
 * actually be 8*x,8*y
 * \param horizontal tile to paint on
 * \param vertical tile to paint on
 * \param tile to paint
 * \param renderer used to paint
 */
void Tiles_paintCharAt(int x, int y, unsigned const char character, SDL_Renderer* renderer ){
	SDL_Rect tileClip = { ((character-32)%8)*8, ((character-32)/8)*8, 8, 8 };
	SDL_Rect tilePos = {x*8, y*8, 8, 8};
	//printf ( "PAINT %d:'%c' at {%d,%d}: clip{%d,%d,%d,%d}, pos{%d,%d,%d,%d}\n\n", character,character, x, y, tileClip.x,tileClip.y,tileClip.w,tileClip.h,tilePos.x,tilePos.y,tilePos.w,tilePos.h );
	SDL_RenderCopy( renderer, charMap, &tileClip, &tilePos );
}

/** \brief draw a string of characters at the specified postion on the renderer
 * Paints a string of characters in a horizontal row on the renderer. Does not
 * wrap or correct for overflow. x,y passed in is the tile position (x*8,y*x
 * pixel position) of the first character of the string
 * \param horizontal tile to start the string at
 * \param vertical tile to start the string at
 * \param string to paint
 * \param renderer used to paint
 */
void Tiles_paintStringAt(int x, int y, const char* message, SDL_Renderer* renderer ){
	int msgLen = strlen(message);
	int i=0;
	for(i=0; i < msgLen; i++){
		Tiles_paintCharAt(x+i,y,message[i], renderer);
	}
}

/** \brief cleans up the Tiles module
 * frees the stored texture memory of the tilemap
 */
void Tiles_cleanup(){
	SDL_DestroyTexture( charMap );
}







