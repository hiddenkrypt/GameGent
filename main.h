
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

