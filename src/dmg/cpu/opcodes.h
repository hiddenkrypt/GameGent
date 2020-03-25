#pragma once
#include <stdint.h>
#include <stdbool.h>

#define NO_FLAGS E_UNAFFECTED,E_UNAFFECTED,E_UNAFFECTED,E_UNAFFECTED

/** \brief an instruction's effect on a flag
 *
 *	each instruction can affect each flag in one of these four ways
 */
typedef enum flagEffectEnum{
	E_UNAFFECTED = 0,	/**< flag is unchanged */
	E_CLEARED = 1,		/**< flag is always set to 0 */
	E_RAISED = 2,		/**< flag is always set to 1 */
	E_APPLIED = 3		/**< flag is set according to the rules of the flag */
} flagEffect;

/** \brief a collection of the effects an instruction has on the four cpu flags
 * Each instruction may have an effect on each of the four flags. So each
 * instruction gets a flagEffects struct to store what the effect is on each
 * flag. See ::flagEffect enum for more info.
 */
typedef struct{
	flagEffect zero;		/**< effect on Zero flag */
	flagEffect subtract;	/**< effect on subtraction flag */
	flagEffect halfCarry;	/**< effect on the half carry flag */
	flagEffect carry;		/**< effect on the carry flag */
} flagEffects;

/** \brief a description of an instruction
 * This struct describes the 'meta' of an instruction, from side
 * effects to byte size to number of parameters, to a human
 * readable mnemonic. This doesn't include the actual *code*.
 */
typedef struct{
	uint8_t codePoint;		/**< the 8 bits that represent this instruction (minus CB prefixes) */
	uint8_t length;			/**< the overall length of the instruction and args in bytes */
	uint8_t cycles;			/**< the normal number of cpu cycles the instruction takes */
	uint8_t cyclesAbort;	/**< some branching/conditional instructions may take a different number of cycles depending on the condition/branch.  */
	flagEffects flags;		/**< A ::flagEffects struct holding the ::flagEffect enum representing the effect this instruction has on each flag*/
	char mnemonic[6];		/**< A human readable asm mnemonic for this instruction. Useful for debugging. */
	char arg1[5];			/**< the mnemonic representation of the first arg, if applicable */
	char arg2[5];			/**< the mnemonic representation of the second arg, if applicable */
} instruction;

#include "codeTables.h"
