# GameGent Code Standards and Styleguide:

## Capitalization
* constants (including Enum members) are **ALL_CAPS**
* structure typedefs are **CapitalCase**
* structure members, local variables, local functions are **camelCase**
* Filenames are always **camelCase**

## Files

Files should be self-contained translation units. Do not \#include \*.c files. Do not put variable or function definitions in \*.h files

Filenames are always **camelCase**

The main entrypoint of the program is in the root directory, and named after the program: "GameGent.c". this is the sole exception to the camelCasing of filenames, due to it's property as the "start" of the code.

Filenames for headers that just define a structure should be named '\<structure typedef label>Structure.h'
* Example: src/gui/menus/menuStructure.h

All other code belongs in the `/src` directory. Code shall be split into subdirectories based on what system / subsystem they are a part of:
* `/src/gui` for general gui and related sub-systems
* `/src/gui/menus` for each discreet menu page
* `/src/dmg` is reserved for emulator core files

ALL HEADER FILES ALWAYS START WITH `#pragma once`

## Locality
Non-shared functions must be `static` wherever possible. The `static` keyword prefixes all type information in variables and functions.  

Static global variables must be defined at the top of the file after includes.

Shared (header defined) functions are always prefixed with the name of the translation unit in **CapitalCase** and an underscore
* Example: Gui_draw(), MainMenu_getMenu()

Getter / Setter functions are (as they are shared functions) named with the module name first with an underscore, then the name of the function which MUST start with the words "get" or "set" and be in camelCase.
* Example: MainMenu_getMenu(), CPU_setPC( 0x100 )


*Declare* local functions at the top of the file, after global variables, even if unneccesary 

*Define* local functions before shared functions, so that shared functions are the last items in a file.

## Variables
Avoid extern

Avoid globals unless persistent state is necessary for the module

Variable names should avoid initialisms, truncation, or other non-obvious names unless the result is a common and widely understood shortening, such as `i` for a loop index, or `FPS` for frames per second. Names should explain what the purpose of the variable is.

## Specific Syntax Notes
Function return value, name, and parameter list all in the same line.

pointers should attacks the `*` to the identifier 

`const` goes before type. `static` goes before anything else for variables, but after all return type info for functions. 

Open parens on the same line as whatever their associated with.

`else {` and `else if (...){` go on the same line as the close paren for the previous logic block.

Spaces on the inside of parens unless parens are empty.

Example:
```c
const *int static myFunction ( const int *index ) {
  if ( *index > 3 ){
    foo();
  } else if ( *index == 2 ) {
    bar( index );
  }
}
```
Functions separated by one empty line. Function bodies should avoid blank lines unless they help organize code in some way, though that usually means you should break up the function into multiple sub-functions.

## Documentation
Each function in a .c file should have a doxygen comment block before it.

Strucs and enums should include Doxy comments for each member / entry.

Use `@todo` liberally! Use `@note` as well!
