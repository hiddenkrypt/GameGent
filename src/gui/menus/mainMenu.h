#pragma once
#include "menu.h"

Menu MainMenu_getMenu( );

static void noop();
static bool always();

static char* continueLabel();
static char* loadRomLabel();
static char* loadStateLabel();
static char* saveStateLabel();
static char* stateNumberLabel();
static char* optionsLabel();
static char* exitLabel();
