#pragma once

extern uint16_t breakpoints[20];

void Debugger_init();
bool Debugger_break();
bool Debugger_checkBreakpoint( uint16_t addr );
