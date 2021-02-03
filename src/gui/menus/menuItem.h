#pragma once

#include <stdbool.h>

/** \brief a single item in a menu.
 * a trio of function pointers allowing menu items to define themselves dynamically.
 * @todo maybe refactor this out of existence, the loadRomMenu way might just be better. I think I might have let the oop get to my head again
 */

typedef struct{
	void  (*activate) ();			/**< a function for performing the menu item's action */
	bool  (*activeCondition) ();	/**< is this item active or not */
	char *(*getLabel) ();			/**< what is the string label of this item */
} menuItem;
