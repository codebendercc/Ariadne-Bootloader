/* Name: debug_ann.h
 * Author: Stelios Tsampas
 * Copyright: codebender.cc
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: ariadne
 * Function: debugging progmem strings
 * Version: 0.5 "Mega2560"
 */

#ifndef debug_ann_h
#define debug_ann_h

#include <avr/pgmspace.h>

#if defined(ANNOUNCE)

#if (DEBUG_ANN > 0)
	#undef DBG_ANN
	#define DBG_ANN(block) block
	#define tracePGMlnAnn(msg) tracePGMln(mDebugAnn_PREFIX, msg)
const unsigned char mDebugAnn_PREFIX[]	PROGMEM =	" Ann: ";
const unsigned char mDebugAnn_DONE[]	PROGMEM =	"Broadcast init done";
#endif

#endif

#endif
