# GameGent
DMG-01 emulator

Written in C(18)
Built with Code::Blocks -- http://www.codeblocks.org/

Using SDL2.0 -- https://www.libsdl.org/

Maybe using tiny file dialogs -- https://sourceforge.net/projects/tinyfiledialogs/

Mainly building this as a personal project because I've always wanted to make an emulator. My goals are to make the end program user-friendly for non-technical people, so I'm avoiding any sort of command line interface.

I've made and am sticking to [my own styleguide](Styleguide.md) for this as I haven't found any other styleguides for C that I quite like. I still need to figure out a linter that I can configure to my style, though.

Gamegent Source files, this readme, and all other documents in this repo are released under the Gamegent license found in the accompanying LICENCE.txt file. This is not true open source, as certain disqualifying restrictions apply.  A basic explanation of this license would be that it's basically the standard MIT license, with one additional restriction against any right to use this licensed property by any persons who have ever worked for the US government's Department of Homeland Security.

If you've never worked for DHS, then you're free to use this code as you see fit as long as any substantial copy of the code has my copyright notice attached. If you currently or have ever worked for the DHS, then you have no right to copy or use this code in any capacity.

## Major components and estimated state of completion

### Emulator Core
-CPU: 1%
-MMU: 0%
-GPU/PPU/LCD: 0%
-APU: %0
-Cart (+MBC1,3,5): 0%

### Supporting Framework
-SDL Display: 30%
-Menus: 10%
