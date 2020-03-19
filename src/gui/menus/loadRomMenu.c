//#include <SDL.h>
//#include <string.h>
//#include "../../../GameGent.h"
//#include "../../dmg/dmg.h"
//#include "../tileMap.h"
//#include "menu.h"
//#include "menuItem.h"
//#include "loadRomMenu.h"
//
//static menuItem* menuItems;
//static int menuItemCount = 0;
//
///** \brief get the numbered menuItem
// * \return a copy of the menuItem struct for the numbered item
// */
//static menuItem getItem(int i){
//    return menuItems[i];
//}
//
///** \brief gets the number of menu items that are active
// *
// * generates a count of the number of menu items that return
// * true when their activeCondition is called
// * \return the count of items that are active
// */
//static int activeItems(){
//    int count = 0;
//    for( int i=0; i < menuItemCount; i++ ) {
//        if ( menuItems[i].activeCondition() ) {
//            count++;
//        }
//    }
//    return count;
//}
///** \brief creates the Menu Struct for this menu
// *
// * The menu items list is dynamic, and should be generated here
// * @todo populate menu item list when this function is called
// * \return a menu struct for the load rom menu, with a list of menu items based on previously loaded roms
// *
// */
//Menu LoadRomMenu_getMenu(){
//    Menu loadRomMenu;
//    loadRomMenu.itemCount = menuItemCount;
//    loadRomMenu.activeItemCount = &activeItems;
//    loadRomMenu.getItem = &getItem;
//    return loadRomMenu;
//}
//
//
