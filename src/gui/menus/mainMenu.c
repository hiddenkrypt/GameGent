#include <string.h>
#include "../../GameGent.h"
#include "../../dmg/dmg.h"
#include "../menuManager.h"
#include "loadRomMenu.h"
#include "settingsMenu.h"
#include "menu.h"
#include "menuItemStructure.h"
#include "mainMenu.h"

void loadRom(){
	MenuManager_setMenu( LoadRomMenu_getMenu() );
}

void settings(){
	MenuManager_setMenu( SettingsMenu_getMenu() );
}

static void noop();
static bool always();

static void continueLabel( char *label );
static void loadRomLabel( char *label );
static void loadStateLabel( char *label );
static void saveStateLabel( char *label );
static void stateNumberLabel( char *label );
static void optionsLabel( char *label );
static void exitLabel( char *label );

menuItem menuItems[7] = {
	{&noop,					&DMG_isEmulating,	&continueLabel},
	{&loadRom,				&always,			&loadRomLabel},
	{&noop,					&DMG_isEmulating,	&loadStateLabel},
	{&noop,					&DMG_isEmulating,	&saveStateLabel},
	{&noop,					&DMG_isEmulating,	&stateNumberLabel},
	{&settings,				&always,			&optionsLabel},
	{&GameGent_shutdown,	&always,			&exitLabel}
};
const int MAIN_MENU_ITEMS = 7;

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
	if(i > MAIN_MENU_ITEMS) {
		strncpy(returnBuffer, "getLabel FAILURE!",18);
		return;
	}
	for( int j = 0; j < MAIN_MENU_ITEMS; j++ ){
		if( menuItems[j].activeCondition(j) ){
			if(i-- == 0){
				menuItems[j].getLabel( returnBuffer );
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
	for( int i=0; i < MAIN_MENU_ITEMS; i++ ) {
		if ( menuItems[i].activeCondition(i) ) {
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
	if(i > MAIN_MENU_ITEMS) {return;}
	for( int j = 0; j < MAIN_MENU_ITEMS; j++ ){
		if( menuItems[j].activeCondition(j) ){
			if(i-- == 0){ menuItems[j].activate(j); }
		}
	}
}

/**\brief Menu item action: do nothing  */
static void noop(){}
/**\brief Menu item condition: always display  */
static bool always(){ return true; }


/**\brief Menu item label: literal value  */
static void continueLabel( char *label ){
	char *constantLabel = "Continue";
	strncpy( label, constantLabel, strlen( constantLabel ) + 1);

}

/**\brief Menu item label: literal value  */
static void loadRomLabel( char *label ){
 	char *constantLabel = "Load ROM ==>";
	strncpy( label, constantLabel, strlen( constantLabel ) + 1);

}

/**\brief Menu item label: literal value  */
static void loadStateLabel( char *label ){
 	char *constantLabel = "Load State";
	strncpy( label, constantLabel, strlen( constantLabel ) + 1);

}

/**\brief Menu item label: literal value  */
static void saveStateLabel( char *label ){
 	char *constantLabel = "Save State";
	strncpy( label, constantLabel, strlen( constantLabel ) + 1);

}

/**\brief Menu item label: dynamic value, currently unimplemented  */
static void stateNumberLabel( char *label ){
	char *constantLabel = "State Number:";
	strncpy( label, constantLabel, strlen( constantLabel ) + 1);

} /**@todo append current state number */

/**\brief Menu item label: literal value  */
static void optionsLabel( char *label ){
 	char *constantLabel = "Settings ==>";
	strncpy( label, constantLabel, strlen( constantLabel ) + 1);

}

/**\brief Menu item label: literal value  */
static void exitLabel( char *label ){
	char *constantLabel = "EXIT";
	strncpy( label, constantLabel, strlen( constantLabel ) + 1);

}

/** \brief creates the Menu Struct for this menu
 *
 * The menuManager uses Menu Structs to hold a reference to the currently
 * active menu. this function loads the main menu.
 *
 * \return a menu struct for the main Menu
 */
menu MainMenu_getMenu(){
	menu mainMenu;
	mainMenu.itemCount = &itemCount;
	mainMenu.getLabel = &getLabel;
	mainMenu.activateItem = &activateItem;
	return mainMenu;
}






