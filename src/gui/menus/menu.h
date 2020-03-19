#pragma once

typedef struct{
    int (*itemCount) ();
    char* (*getLabel) (int);
    void (*activateItem) (int);
} Menu;
