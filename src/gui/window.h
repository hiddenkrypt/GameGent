
#pragma once

/*!
 * @brief Initializes and creates a window
 *
 * Currently initializes SDL for video, opens a window, and creates a renderer tied to the window
 * @todo break out SDL init and window creation into separate modules
 */
SDL_Renderer* Window_init();

/*!
 * @brief cleans up memory objects related to the window
 *
 * Closes and frees the window, and it's tied renderer, then shuts down SDL.
 * @todo breakout SDL_Quit as a part of Window_init todo SDL breakout.
 */
void Window_shutdown();
