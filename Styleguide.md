# GameGent Code Standards and Styleguide:

## Capitalization
* constants are **ALL_CAPS**
* structure typedefs are **CapitalCase**
* structure members, local variables, local functions are **camelCase**
* Filenames are always **camelCase**

## Files

Files should be self-contained translation units. Do not \#include \*.c files. Do not put variable or function definitions in \*.h files

Filenames are always **camelCase**

Filenames for headers that just define a structure should be named '\<structure typedef label>Structure.h'
* Example: src/gui/menus/menuStructure.h

The main entrypoint of the program is in the root directory, and named after the program: "GameGent.c". this is the sole exception to the camelCasing of filenames, due to it's property as the "start" of the code.

All other code belongs in the `/src` directory. Code shall be split into subdirectories based on what system / subsystem they are a part of:
* `/src/gui` for general gui and related sub-systems
* `/src/gui/menus` for each discreet menu page
* `/src/dmg` is reserved for emulator core files

ALL HEADER FILES ALWAYS START WITH `#pragma once`

`#include` pragmas

## Functions
Non-shared functions must / should be `static`

Static global variables must be defined at the top of the file after includes

Shared (header defined) functions are always prefixed with the name of the translation unit in **CapitalCase** and an underline
* Example: Gui_draw(), MainMenu_getMenu()

*Declare* local functions at the top of the file, after global variables

*Define* local functions before shared functions, so that shared functions are the last items in a file.

## Variables
Avoid extern

Globals must be static

Avoid globals unless persistent state is necessary for the module

Variable names should avoid initialisms, truncation, unless the result is a common and widely understood shortening, such as `i` for a loop index, or `FPS` for frames per second.

## Specific Syntax Notes
Function return value, name, and parameter list all in the same line.

Open parens on the same line as whatever their associated with.

`else {` on the same line as the related close paren.

spaces on the inside of parens unless parens are empty.

Example:
```c
void myFunction ( int index ) {
  if ( index > 3 ){
    doThing();
  } else if ( index == 2 ) {
    doOtherThing();
  }
}
```
Functions separated by one empty line. Function bodies should avoid blank lines unless they help organize code in some way, though that usually means you should break up the function into multiple sub-functions.

## Documentation
Each function in a .c file should have a doxygen comment block before it.

Strucs and enums should include Doxy comments for each member / entry.

Use `@todo` liberally! Use `@note` as well!
