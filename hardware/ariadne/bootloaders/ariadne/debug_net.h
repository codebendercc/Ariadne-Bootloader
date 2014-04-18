/* Name: debug_msg.h
 * Author: Stelios Tsampas
 * Copyright: codebender.cc
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: ariadne
 * Function: debugging progmem strings
 * Version: 0.5 "Mega2560"
 */

#ifndef debug_net_h
#define debug_net_h

#include <avr/pgmspace.h>


#if (DEBUG_NET > 0)
	#undef DBG_NET
	#define DBG_NET(block) block
	#define tracePGMlnNet(msg) tracePGMln(mDebugNet_PREFIX, msg)
const unsigned char mDebugNet_PREFIX[]	PROGMEM =	" Net: ";
const unsigned char mDebugNet_EEPROM[]	PROGMEM =	"EEPROM settings";
const unsigned char mDebugNet_BUILTIN[]	PROGMEM =	"Built-in settings";
const unsigned char mDebugNet_ADDR[]	PROGMEM =	"\tAddress: ";
const unsigned char mDebugNet_SUBN[]	PROGMEM =	"\t Subnet: ";
const unsigned char mDebugNet_GW[]		PROGMEM =	"\tGateway: ";
const unsigned char mDebugNet_MAC[]		PROGMEM =	"\t    MAC: ";
const unsigned char mDebugNet_DONE[]	PROGMEM =	"Network init done";
	#if (DEBUG_NET > 1)
		#undef DBG_NET_EX
		#define DBG_NET_EX(block) block
	#endif
#endif

#endif
