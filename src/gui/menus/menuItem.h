#pragma once

typedef struct{
    void  (*activate) ();
    bool  (*activeCondition) ();
    char* (*getLabel) ();
} menuItem;