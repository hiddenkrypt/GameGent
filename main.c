
#include "main.h"
#include <stdio.h>



enum program_state currentState = state_main_menu;



int main ( int argn, char* args[] ) {
    printf( "state: %d", currentState);
    currentState = state_emulating;
    printf( "state: %d", currentState);
    return 0;
}
