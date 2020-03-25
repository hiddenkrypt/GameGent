#pragma once

/** \brief enumeration of possible command intents
 * a list of the various ways user input may be interpreted
 * names match the dmg core inputs for a reason, and only alternative uses will be mentioned in documentation
 */
typedef enum keyCommandEnum{
	A,			/**< "activate" in menus */
	B,			/**< "back" in menus */
	START,		/**< */
	SELECT,		/**< */
	UP,			/**< up in menus*/
	DOWN,		/**< down in menus*/
	LEFT,		/**< */
	RIGHT,		/**< */
	MENU,		/**< Open or close the menu, switching between the emulator and the menu system*/
	NO_COMMAND	/**< No system effect intended by this input */
} keyCommand;
