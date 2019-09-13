
#pragma once
/*!
 * @brief Intializes Gui system
 *
 * Initializes all Gui subsystems, creating an SDL window and associated renderer.
 * @todo breakout window and SDL init
 * @see Window_init()  about breaking out window and SDL init
 */
SDL_Renderer* Gui_init();

/*!
 * @brief Draws the gui
 *
 * draws the next frame of the program based on program state
 * @param GameGent the current state of the gamegent
 */
void Gui_draw (GameGent_State GameGent) ;

/*!
 * @brief Cleanup gui subsystems
 *
 * Calls all gui subsystem cleanup/shutdown functions.
 */
void Gui_shutdown();

/*!
 * @brief Handles user input events
 *
 * @todo EVERYTHING! handle any events
 */
void Gui_handleEvent( SDL_Event e );
