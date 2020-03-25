#pragma once

/** \brief a recently loaded rom
 * A path to a rom file, and a short display name (18 characters, truncated from the filename)
 */
typedef struct{
	char name[18];	/**< a user displayed nameof the rom, 18 characters long or less */
	char* path;		/**< a full absolute path to the rom file */
} recentRom;

/** \brief a list of recent roms
 * typical array stuct holding the array itself and a int for the number of items
 */
typedef struct{
	int number;				/**< the actual number of items */
	recentRom items[10];	/**< the array of recentRom items. May have empty values. */
} recentRomList;
