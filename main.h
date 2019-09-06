
#pragma once




int main ( int argn, char* args[] );
void shutdown();

/**
 * @brief current state of the overall program
 *
 * a selection of states the overall program can be in. Different subsystems may change the program state
 */
enum program_state{
    state_menu, /**< Program is currently in the menu. Emulation is paused. */
    state_emulating /**< Menu is hidden, emulation is proceeding */
};
