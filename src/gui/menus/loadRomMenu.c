#include <string.h>
#include "../../../settings.h"
#include "../menuManager.h"
#include "mainMenu.h"
#include "menu.h"
#include "menuItem.h"
#include "recentRomStruct.h"
#include "loadRomMenu.h"

recentRomList recentRoms = {0, {}};

static char* getLabel( int i ){
    if( i == 0 ){
        return "Load Rom File...";
    }
    if( i == recentRoms.number+1 ){
        return "Back";
    }
    return "";
}
static void activateItem( int i ){
    if( i == recentRoms.number+1 ){
        MenuManager_setMenu( MainMenu_getMenu() );
    }
}
static int itemCount(){
    return recentRoms.number+2;
}
menu LoadRomMenu_getMenu(){
    recentRoms = Settings_get_recentRoms();
    menu loadMenu;
    loadMenu.itemCount = &itemCount;
    loadMenu.getLabel = &getLabel;
    loadMenu.activateItem = &activateItem;
    return loadMenu;
}
