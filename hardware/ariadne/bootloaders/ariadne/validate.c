/* Validate first sector is a genuine image */

#include <stdint.h>

#include "validate.h"
#include "serial.h"
#include "debug.h"
#include "debug_vald.h"

uint8_t validImage(uint8_t* base)
{
	/* Check that a jump table is present in the first flash sector */
	uint8_t i;
	for(i = 0; i < 0x34; i += 4) {

		// For each vector, check it is of the form:
		// 0x0C 0x94 0xWX 0xYZ  ; JMP 0xWXYZ
		if(base[i] != 0x0c) {
			DBG_VALD(
				tracePGMlnVald(mDebugVald_FAILED);
				tracenum(i);
				tracePGM(mDebugVald_WITH);
				tracenum(base[i]);
				tracePGM(mDebugVald_0x0C);
			)
			return(0);
		}
		
		if(base[i + 1] != 0x94) {
			DBG_VALD(
				tracePGMlnVald(mDebugVald_FAILED);
				tracenum(i + 1);
				tracePGM(mDebugVald_WITH);
				tracenum(base[i + 1]);
				tracePGM(mDebugVald_0x94);
			)
			return(0);
		}
	}

	DBG_VALD(tracePGMlnVald(mDebugVald_VALID);)

	return(1);
}
