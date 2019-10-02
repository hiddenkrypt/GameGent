
#include <stdbool.h>
#include "dmg.h"
#include "cpu.h"

void DMG_init(){
    CPU_init();
}
void DMG_LoadRom(char* path){}
void DMG_startEmulation(){}
void DMG_haltEmulation(){}
bool DMG_isEmulating(){
    return false;
}
