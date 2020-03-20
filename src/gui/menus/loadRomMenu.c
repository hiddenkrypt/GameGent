#include "menu.h"
#include "menuItem.h"
#include "loadRomMenu.h"

static int itemCount(){ return 0; }
static char* getLabel( int i ){ return ""; }
static void activateItem(int i){}

Menu LoadRomMenu_getMenu(){
    Menu loadMenu;
    loadMenu.itemCount = &itemCount;
    loadMenu.getLabel = &getLabel;
    loadMenu.activateItem = &activateItem;
    return loadMenu;
}

