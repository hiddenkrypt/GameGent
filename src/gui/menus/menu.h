#pragma once
#include "menuItem.h"
typedef struct{
    int (*itemCount) ();
    char* (*getLabel) (int);
    void (*activateItem) (int);
} Menu;
