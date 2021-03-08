#include <string.h>
#include <stdio.h>
#include "../../settings/settings.h"
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

static void keyBindsLabel( char *labelBuffer, int bufferSize );
static void debugLabel( char *labelBuffer, int bufferSize );
static void runBootromLabel( char *labelBuffer, int bufferSize );
static void bootRomPathLabel( char *labelBuffer, int bufferSize );
static void runLastRomLabel( char *labelBuffer, int bufferSize );
static void backLabel( char *labelBuffer, int bufferSize );

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
static void getLabel( int i, char *returnBuffer, int bufferSize ){
	if(i > SETTINGS_MENU_ITEMS) {
		snprintf( returnBuffer, 10, "ERR LABEL" );
		return;
	}
	for( int j = 0; j < SETTINGS_MENU_ITEMS; j++ ){
		if( settingsMenuItems[j].activeCondition( j ) ){
			if(i-- == 0){
				settingsMenuItems[j].getLabel( returnBuffer, bufferSize );
				return;
			}
		}
	}
	snprintf( returnBuffer, 10, "ERR LABEL" );
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
static void keyBindsLabel( char *labelBuffer, int bufferSize ){
	char *constantLabel = "Key Binds ==>";
	strncpy( labelBuffer, constantLabel, strlen( constantLabel ) + 1);
}

/**\brief Menu item label: dynamic value @todo: dynamically concat state of setting */
static void debugLabel( char *labelBuffer, int bufferSize ){
	char value = 'N';
	if( Settings_getDebugFlag() ){
		value = 'Y';
	}
	snprintf( labelBuffer, bufferSize, "Debug Mode: %c", value );
}

/**\brief Menu item label: dynamic value  @todo: dynamically concat state of setting*/
static void runBootromLabel( char *labelBuffer, int bufferSize ){
	char value = 'N';
	if( Settings_getRunBootRom() ){
		value = 'Y';
	}
	snprintf( labelBuffer, bufferSize, "Run Boot Rom: %c", value );
}

/**\brief Menu item label: dynamic value @todo: dynamically concat path of bootrom */
static void bootRomPathLabel( char *labelBuffer, int bufferSize ){
	snprintf( labelBuffer, bufferSize, "Bootrom: %s", Settings_getBootRomPath() );
}

/**\brief Menu item label: dynamic value, @todo: dynamically apply state of setting  */
static void runLastRomLabel( char *labelBuffer, int bufferSize ){
	char *constantLabel = "Run Last on Boot: ";
	strncpy( labelBuffer, constantLabel, strlen( constantLabel ) + 1);
}

/**\brief Menu item label: literal value  */
static void backLabel( char *labelBuffer, int bufferSize ){
	char *constantLabel = "<==";
	strncpy( labelBuffer, constantLabel, strlen( constantLabel ) + 1);
}

static void backAction(){
	MenuManager_setMenu( MainMenu_getMenu() );
}
/** \brief creates the Menu Struct for this menu
 *
 * The menuManager uses Menu Structs to hold a reference to the currently
 * active menu. this function loads the setting menu.
 *
 * \return a menu struct for the settings Menu
 */
menu SettingsMenu_getMenu(){
	menu settingsMenu;
	settingsMenu.itemCount = &itemCount;
	settingsMenu.getLabel = &getLabel;
	settingsMenu.activateItem = &activateItem;
	return settingsMenu;
}






