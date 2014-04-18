/* Name: debug_msg.h
 * Author: Stelios Tsampas
 * Copyright: codebender.cc
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: ariadne
 * Function: debugging progmem strings
 * Version: 0.5 "Mega2560"
 */

#ifndef debug_util_h
#define debug_util_h

#include <avr/pgmspace.h>

#if (DEBUG_UTIL > 0)
	#undef DBG_UTIL
	#define DBG_UTIL(block) block
	#define tracePGMlnUtil(msg) tracePGMln(mDebugUtil_PREFIX, msg)
const unsigned char mDebugUtil_PREFIX[]	PROGMEM =	"Util: ";
const unsigned char mDebugUtil_TICK[]	PROGMEM =	"Tick ";
const unsigned char mDebugUtil_NEXT[]	PROGMEM =	"nTM ";
const unsigned char mDebugUtil_LAST[]	PROGMEM =	"lTM ";
#endif


#endif
