#include <string.h>
#include "../../GameGent.h"
#include "../../dmg/dmg.h"
#include "../menuManager.h"
#include "loadRomMenu.h"
#include "mainMenu.h"
#include "menu.h"
#include "menuItemStructure.h"
#include "settingsMenu.h"


static void noop();
static bool always();
static char *keyBindsLabel();
static char *debugLabel();
static char *runBootromLabel();
static char *bootRomPathLabel();
static char *runLastRomLabel();
static char *backLabel();
static void backAction();

menuItem settingsMenuItems[6] = {
	{&noop,				&always,		&keyBindsLabel}, 	//keybinds submenu
	{&noop,				&always,		&debugLabel}, 	//launch debug
	{&noop,				&always,		&runBootromLabel},	//run boot rom
	{&noop,				&always,		&bootRomPathLabel},	//boot rom file
	{&noop,				&always,		&runLastRomLabel},	//run last rom on boot
	{&backAction,		&always,		&backLabel}			//back
};
const int SETTINGS_MENU_ITEMS = 6;

/** \brief get the text for a menu item
 *
 * dynamically determines the text for a menu item indexed by i.
 * Since this menu may have 'inactive' items, the menu item list
 * has to be filtered based on the items activeCondition. i is
 * the index of the list of active items, not all items. Also,
 * current save state number is dynamically updated
 *
 * \param the index of the item requested
 * \param a passed char* buffer to put the label into
 **/
static void getLabel( int i, char *returnBuffer ){
	if(i > SETTINGS_MENU_ITEMS) {
		strncpy(returnBuffer, "getLabel FAILURE!",18);
		return;
	}
	for( int j = 0; j < SETTINGS_MENU_ITEMS; j++ ){
		if( settingsMenuItems[j].activeCondition(j) ){
			if(i-- == 0){
				strncpy( returnBuffer, settingsMenuItems[j].getLabel(j), 18 );
				return;
			}
		}
	}
	strncpy( returnBuffer, "wat", 18 );
}

/** \brief gets the number of menu items that are active
 *
 * generates a count of the number of menu items that return
 * true when their activeCondition is called
 * \return the count of items that are active
 */
static int itemCount(){
	int count = 0;
	for( int i=0; i < SETTINGS_MENU_ITEMS; i++ ) {
		if ( settingsMenuItems[i].activeCondition(i) ) {
			count++;
		}
	}
	return count;
}
/** \brief perform the action of the menu item indexed by i
 *
 * Activate the menu item with an active items index of i. This
 * requires filtering to just he active items to find the right one.
 *
 *	\param the index of the menu item being selected for activation
**/
static void activateItem(int i){
	if(i > SETTINGS_MENU_ITEMS) {return;}
	for( int j = 0; j < SETTINGS_MENU_ITEMS; j++ ){
		if( settingsMenuItems[j].activeCondition(j) ){
			if(i-- == 0){ settingsMenuItems[j].activate(j); }
		}
	}
}

/**\brief Menu item action: do nothing  */
static void noop(){}
/**\brief Menu item condition: always display  */
static bool always(){ return true; }
/**\brief Menu item label: literal value  */
static char *keyBindsLabel(){ return "Key Binds ==>"; }
/**\brief Menu item label: dynamic value @todo: dynamically concat state of setting */
static char *debugLabel(){ return "Use Debugger: "; }
/**\brief Menu item label: dynamic value  @todo: dynamically concat state of setting*/
static char *runBootromLabel(){ return "Run Boot Rom: "; }
/**\brief Menu item label: dynamic value @todo: dynamically concat path of bootrom */
static char *bootRomPathLabel(){ return "Bootrom: "; }
/**\brief Menu item label: dynamic value, @todo: dynamically apply state of setting  */
static char *runLastRomLabel(){ return "Run Last Rom on Boot: "; }
/**\brief Menu item label: literal value  */
static char *backLabel(){ return "<=="; }

static void backAction(){
	MenuManager_setMenu( MainMenu_getMenu() );
}
/** \brief creates the Menu Struct for this menu
 *
 * The menuManager uses Menu Structs to hold a reference to the currently
 * active menu. this function loads the setting menu.
 *
 * \return a menu struct for the settins Menu
 */
menu SettingsMenu_getMenu(){
	menu settingsMenu;
	settingsMenu.itemCount = &itemCount;
	settingsMenu.getLabel = &getLabel;
	settingsMenu.activateItem = &activateItem;
	return settingsMenu;
}






