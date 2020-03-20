#pragma once

#include <stdbool.h>

typedef struct{
    void  (*activate) ();
    bool  (*activeCondition) ();
    char* (*getLabel) ();
} menuItem;
