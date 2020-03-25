#pragma once

/** \brief a menu structure for accessing menu features
 * a menu struct is a collection of function pointers common to all menus.
 * used by the menuManager to work with various menus interchangeably.
 */

typedef struct{
	int (*itemCount) (); 			/**< a function returning the number of items in the menu */
	void (*getLabel) (int, char*);	/**< a function returning the string label of item # i */
	void (*activateItem) (int);		/**< a function telling the menu that the user has activated item # i */
} menu;
