

#include <stdbool.h>


/*!
 * @brief Initialize the tilemap
 *
 * Loads the CharacterTileMap file and attaches it to the renderer
 * @param renderer SDL_Renderer the tilemap will be tied to
 * @return true if initialization and file load succeed, false if there are any problems.
 * @note consider maintaining an internal reference to the renderer, since the same one should be used to draw tiles later
 */
bool Tiles_init( SDL_Renderer* renderer );

/*!
 * @brief Draw string at tile position
 *
 * Displays a string *message* as bmp font tiles from the tilemap, starting at position {x,y} and going right, pushing those pixels onto the renderer
 * @param x tile x position for the first character of the string
 * @param y tile y position for the first character of the string
 * @param message Character string to display
 * @param renderer SDL_Renderer to draw on
 */
void Tiles_paintStringAt(int x, int y, const char* message, SDL_Renderer* renderer );

/*!
 * @brief Draws a single character at tile position
 *
 * Displays a character tile as bmp font tile from the tilemap at position {x,y} on the renderer
 * @param x tile x position for character tile
 * @param y tile y position for character tile
 * @param character character to display
 * @param renderer SDL_Renderer to draw on
 */
void Tiles_paintCharAt(int x, int y, unsigned const char character, SDL_Renderer* renderer );

/*!
 * @brief Frees tile memory
 *
 * Cleans up the tile manager by releasing the loaded tilemap texture
 */
void Tiles_cleanup();
