#pragma once
#include "menuItem.h"
typedef struct{
    int itemCount;
    int (*activeItemCount) ();
    menuItem (*getItem) (int);
} Menu;
