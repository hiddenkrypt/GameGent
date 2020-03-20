#include <string.h>
#include "../../../settings.h"
#include "../menuManager.h"
#include "mainMenu.h"
#include "menu.h"
#include "menuItem.h"
#include "recentRomStruct.h"
#include "loadRomMenu.h"

recentRomList recentRoms = {0, {}};

static void getLabel( int i, char* returnBuffer ){
    if( i == 0 ){
        strncpy( returnBuffer, "Load Rom File...", 18 );
        return;
    }
    if( i == recentRoms.number+1 ){
        strncpy( returnBuffer, "Back", 18 );
        return;
    }
    char prefix[2] = " \0";
    strncpy( returnBuffer, prefix, 2 );
    strncat( returnBuffer, recentRoms.items[i-1].name, 17 );
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
