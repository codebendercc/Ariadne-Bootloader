/* Name: debug_vald.h
 * Author: Stelios Tsampas
 * Copyright: codebender.cc
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: ariadne
 * Function: debugging progmem strings
 * Version: 0.5 "Mega2560"
 */

#ifndef debug_vald_h
#define debug_vald_h

#include <avr/pgmspace.h>

#if (DEBUG_VALD > 0)
	#undef DBG_VALD
	#define DBG_VALD(block) block
	#define tracePGMlnVald(msg) tracePGMln(mDebugVald_PREFIX, msg)
const unsigned char mDebugVald_PREFIX[] PROGMEM =	"Vald: ";
const unsigned char mDebugVald_VALID[]	PROGMEM =	"Valid image";
const unsigned char mDebugVald_FAILED[]	PROGMEM =	"Failed at ";
const unsigned char mDebugVald_WITH[]	PROGMEM =	" with ";
const unsigned char mDebugVald_0x0C[]	PROGMEM =	" instead of 0x0C";
const unsigned char mDebugVald_0x94[]	PROGMEM =	" instead of 0x94";
#endif

#endif
