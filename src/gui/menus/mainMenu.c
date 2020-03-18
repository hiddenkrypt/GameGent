#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include "tilemap.h"
#include "mainMenu.h"
#include "menu.h"
#include "menuItem.h"
#include "GameGent.h"
#include "dmg.h"

static menuItem menuItems[7] = {
    {&noop,&DMG_isEmulating,&continueLabel},
    {&noop,&always,&loadRomLabel},
    {&noop,&DMG_isEmulating,&loadStateLabel},
    {&noop,&DMG_isEmulating,&saveStateLabel},
    {&noop,&DMG_isEmulating,&stateNumberLabel},
    {&noop,&always,&optionsLabel},
    {&GameGent_shutdown,&always,&exitLabel}
};
static const int MAIN_MENU_ITEMS = 7;

static char* getLabel( int i ){
    if(i > MAIN_MENU_ITEMS) {return "getLabel FAILURE!";}
    for( int j = 0; j < MAIN_MENU_ITEMS; j++ ){
        if( menuItems[j].activeCondition(j) ){
            if(i-- == 0){ return menuItems[j].getLabel(j); }
        }
    }
    return "wat";
}

/** \brief gets the number of menu items that are active
 *
 * generates a count of the number of menu items that return
 * true when their activeCondition is called
 * \return the count of items that are active
 */
static int itemCount(){
    int count = 0;
    for( int i=0; i < MAIN_MENU_ITEMS; i++ ) {
        if ( menuItems[i].activeCondition(i) ) {
            count++;
        }
    }
    return count;
}

void activateItem(int i){
    if(i > MAIN_MENU_ITEMS) {return;}
    for( int j = 0; j < MAIN_MENU_ITEMS; j++ ){
        if( menuItems[j].activeCondition(j) ){
            if(i-- == 0){ menuItems[j].activate(j); }
        }
    }
}

static void noop(){}
static bool always(){ return true; }

static char* continueLabel(){ return "Continue"; }
static char* loadRomLabel(){ return "Load ROM"; }
static char* loadStateLabel(){ return "Load State"; }
static char* saveStateLabel(){ return "Save State"; }
static char* stateNumberLabel(){ return "State Number:"; } /** @todo append current state number */
static char* optionsLabel(){ return "Options..."; }
static char* exitLabel(){ return "EXIT"; }

/** \brief creates the Menu Struct for this menu
 *
 * \return a menu struct for the main Menu
 *
 */
Menu MainMenu_getMenu(){
    Menu mainMenu;
    mainMenu.itemCount = &itemCount;
    mainMenu.getLabel = &getLabel;
    mainMenu.activateItem = &activateItem;
    return mainMenu;
}






