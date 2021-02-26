#include <string.h>
#include <stdio.h>

#include "../../../lib/tinyfiledialogs.h"
#include "../../settings/settings.h"
#include "../../dmg/dmg.h"
#include "../menuManager.h"
#include "mainMenu.h"
#include "menu.h"
#include "menuItemStructure.h"
#include "recentRomStructure.h"
#include "loadRomMenu.h"

recentRomList recentRoms = {0, {}};

/** \brief get the text for a menu item
 *
 * dynamically determines the text for a menu item indexed by i
 * the first and last menu items are always predetermined, but
 * the middle parts are based on recently loaded roms and have
 * to be generated.
 *
 * \param the index of the item requested
 * \param a passed char* buffer to put the label into
 **/
static void getLabel( int i, char *returnBuffer ){
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

/** \brief perform the action of the menu item indexed by i
 *
 * The first menu item always opens a load rom dialog. The
 * last menu item always goes back to the main menu. The
 * middle items are generated based on previously played
 * roms, and load from that stored rom path.
 * @todo load previous rom items
 *
 *	\param the index of the menu item being selected for activation
**/
static void activateItem( int i ){
	if( i == 0 ){
		const char *dialogFilterPatterns[2] = { "*.gb", "*.gbc" }; /** @todo add zip support? **/
		const char *romFilePath;
		romFilePath = tinyfd_openFileDialog(
			"Open a Rom file",
			"",
			2,
			dialogFilterPatterns,
			NULL,
			0);

		if (! romFilePath){
			printf("No rom selected.");
		} else {
			printf("\nRom Load path: %s\n", romFilePath);
			DMG_loadRom( romFilePath );
		}
	}
	if( i == recentRoms.number+1 ){
		MenuManager_setMenu( MainMenu_getMenu() );
		return;
	}
	//load previous rom recentRoms.items[i-1].path
}
/** \brief get the numebr of items in this menu
 * This menu consists of a list of previous roms, a
 * load rom option, and a back option. Thus it's
 * always the number of previous roms+2
 *
 * \return the number of items in the menu
 */
static int itemCount(){
	return recentRoms.number+2;
}

/** \brief creates the Menu Struct for this menu
 *
 * The menuManager uses Menu Structs to hold a reference to the currently
 * active menu. this function loads the load rom menu.
 *
 * \return a menu struct for the load rom Menu
 */
menu LoadRomMenu_getMenu(){
	recentRoms = Settings_get_recentRoms();
	menu loadMenu;
	loadMenu.itemCount = &itemCount;
	loadMenu.getLabel = &getLabel;
	loadMenu.activateItem = &activateItem;
	return loadMenu;
}
