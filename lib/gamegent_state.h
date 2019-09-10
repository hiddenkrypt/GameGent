#pragma once
/*!
 * @brief current state of the overall program
 *
 * a selection of states the overall program can be in. Different subsystems may change the program state
 */
typedef enum {
    state_main_menu /**< Program is currently in the menu. Emulation is paused. */
    //state_emulating /**< Menu is hidden, emulation is proceeding */
} gamegent_state;

