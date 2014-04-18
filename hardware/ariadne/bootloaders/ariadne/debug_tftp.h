/* Name: debug_msg.h
 * Author: Stelios Tsampas
 * Copyright: codebender.cc
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: ariadne
 * Function: debugging progmem strings
 * Version: 0.5 "Mega2560"
 */

#ifndef debug_tftp_h
#define debug_tftp_h

#include <avr/pgmspace.h>

#if (DEBUG_TFTP > 0)
	#undef DBG_TFTP
	#define DBG_TFTP(block) block
	#define tracePGMlnTftp(msg) tracePGMln(mDebugTftp_PREFIX, msg)
const unsigned char mDebugTftp_PREFIX[] PROGMEM =	"Tftp: ";
const unsigned char mDebugTftp_START[]	PROGMEM =	"Processing packet of size ";
const unsigned char mDebugTftp_OVFL[]	PROGMEM =	"Overflow";
const unsigned char mDebugTftp_RADDR[]	PROGMEM =	"Set up return address";
const unsigned char mDebugTftp_BLOCK[]	PROGMEM =	"This is block ";
const unsigned char mDebugTftp_OPCODE[]	PROGMEM =	" with opcode ";
const unsigned char mDebugTftp_DLEN[]	PROGMEM =	" and data length ";
const unsigned char mDebugTftp_OPRRQ[]	PROGMEM =	"Read request";
const unsigned char mDebugTftp_OPWRQ[]	PROGMEM =	"Write request";
const unsigned char mDebugTftp_OPDATA[]	PROGMEM =	"Data block";
const unsigned char mDebugTftp_NPORT[]	PROGMEM =	"Changed to port ";
const unsigned char mDebugTftp_FULL[]	PROGMEM =	"Flash is full";
const unsigned char mDebugTftp_WRADDR[]	PROGMEM =	"Writing data from address ";
const unsigned char mDebugTftp_PLEN[]	PROGMEM =	"Packet length adjusted to ";
const unsigned char mDebugTftp_DONE[]	PROGMEM =	"Flashing complete";
const unsigned char mDebugTftp_OPACK[]	PROGMEM =	"Acknowledge";
const unsigned char mDebugTftp_OPERR[]	PROGMEM =	"Error";
const unsigned char mDebugTftp_INVOP[]	PROGMEM =	"Invalid opcode ";
const unsigned char mDebugTftp_SACK[]	PROGMEM =	"Sent ACK";
const unsigned char mDebugTftp_SFACK[]	PROGMEM =	"Sent Final ACK";
const unsigned char mDebugTftp_RESP[]	PROGMEM =	"Response sent";
const unsigned char mDebugTftp_INIT[]	PROGMEM =	"TFTP server init done";
const unsigned char mDebugTftp_PORT[]	PROGMEM =	"\tDataPort: ";
const unsigned char mDebugTftp_SOCK[]	PROGMEM =	"Init socket to port ";
	#if (DEBUG_TFTP > 1)
		#undef DBG_TFTP_EX
		#define DBG_TFTP_EX(block) block
const unsigned char mDebugTftp_NEWLINE[]	PROGMEM =	"\r\n";
const unsigned char mDebugTftp_RPTR[]		PROGMEM =	"readPointer at position ";
const unsigned char mDebugTftp_RPOS[]		PROGMEM =	"Reading from position ";
const unsigned char mDebugTftp_BLEFT[]		PROGMEM =	"Bytes left ";
const unsigned char mDebugTftp_WRITE[]		PROGMEM =	"Writing ";
const unsigned char mDebugTftp_OFFSET[]		PROGMEM =	" at offset ";
	#endif
#endif

#endif
