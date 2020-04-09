#pragma once

void CPU_init();
void CPU_tick();
void CPU_crash(char* reason);
void CPU_noop();
void CPU_stop();
void CPU_halt();
void CPU_setCarryFlag();
void CPU_clearCarryFlag();
void CPU_flipCarryFlag();
bool CPU_getCarryFlag();
void CPU_setZeroFlag();
void CPU_clearZeroFlag();
bool CPU_getZeroFlag();
void CPU_setHalfCarryFlag();
void CPU_clearHalfCarryFlag();
bool CPU_getHalfCarryFlag();
void CPU_setSubtractFlag();
void CPU_clearSubtractFlag();
bool CPU_getSubtractFlag();
void CPU_enableInterrupts();
void CPU_disableInterrupts();
