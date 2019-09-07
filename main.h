
#pragma once



/*!
 * @brief program entry, main loop
 *
 * Main is the program entry point. It calls all the initializers, runs the core program loop, and calls all the sleanup/shutdown functions.
 */
int main ( int argn, char* args[] );

/*!
 * @brief top level program cleanup
 *
 * Calls all subsystem cleanup/shutdown functions.
 */
void shutdown();

/*!
 * @brief current state of the overall program
 *
 * a selection of states the overall program can be in. Different subsystems may change the program state
 */
enum program_state{
    state_menu, /**< Program is currently in the menu. Emulation is paused. */
    state_emulating /**< Menu is hidden, emulation is proceeding */
};
