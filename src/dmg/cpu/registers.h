#pragma once
#include <stdint.h>

/** \brief #define some flag bitmasks for the F register
 * the flags of the cpu are stored in register F, and need bitmasks to tease out.
* @note these may not stay #defined, but might end up as actual variables, depending on future coding.
 */
#define FLAG_ZERO 0x80
#define FLAG_ADDSUM 0x40
#define FLAG_HALFCARRY 0x20
#define FLAG_CARRY 0x10

/** \brief the core cpu registers as one big structure
 *
 * DMG CPU registers are a set of 8 8bit and 2 16 bit registers, but
 * pairs of the 8 bit registers can be accessed as if they were a
 * single 16 bit register. So, unions are used. This structure
 * allows access to registers a and f as a uint8_t or AF as a
 * uint16_t. same goes for the pairs BC, DE, HL. PC and SP are only
 * uint16_t.
 *
 * @note a clock cycles counter may be added here in the future
 */
typedef struct {
	struct{
		union{
			struct{
				uint8_t f;
				uint8_t a;
			};
			uint16_t af;
		};
	};
		struct{
		union{
			struct{
				uint8_t c;
				uint8_t b;
			};
			uint16_t bc;
		};
	};
		struct{
		union{
			struct{
				uint8_t e;
				uint8_t d;
			};
			uint16_t de;
		};
	};
		struct{
		union{
			struct{
				uint8_t l;
				uint8_t h;
			};
			uint16_t hl;
		};
	};
	uint16_t SP;
	uint16_t PC;
} DmgRegisters;
