#pragma once

typedef struct{
    char name[18];
    char* path;
} recentRom;

typedef struct{
    int number;
    recentRom items[10];
} recentRomList;
