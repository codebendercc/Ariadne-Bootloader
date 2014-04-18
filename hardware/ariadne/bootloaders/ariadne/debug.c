/* Name: debug.c
 * Author: .
 * Copyright: Arduino
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: eboot
 * Function: Utility routines for bootloader debugging
 * Version: 0.2 tftp / flashing functional, serial flashing
 */

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include "util.h"
#include "debug.h"


#if defined(ENABLE_DEBUG)

/*
 * Standart strings used throughout the code.
 */
const unsigned char mDebug_NEWLINE[]	PROGMEM =	"\r\n";
const unsigned char mDebug_HEXPREF[]	PROGMEM =	"0x";

void tracePGM(const void* p_msg)
{
	uint8_t	c = 1, i = 0;

	while(c != 0){
#if (FLASHEND > 0x10000)
		/* 0x30000 was added to fix the issues of progmem with >64Kb flash.
		 * 0x30000 is specific to atmega2560 and won't work on smaller or larger flashes.
		 * I should find a way to macro the calculation of this value
		 */
		c = pgm_read_byte_far(PROGMEM_OFFSET + (uint32_t)(uint16_t)p_msg + i);
#else
		c = pgm_read_byte_near((uint16_t)p_msg + i);
#endif
		if (c != 0) putch(c);
		i++;
	}
}


void tracePGMln(const void* p_prefix, const void* p_msg)
{
	tracePGM(mDebug_NEWLINE);
	tracePGM(p_prefix);
	tracePGM(p_msg);
}


void trace(char* msg)
{
	uint8_t c;

	if(*msg != '\0') {
		while((c = *msg++)) putch(c);
	}
}


void traceln(const void* p_prefix, char* msg)
{
	tracePGM(mDebug_NEWLINE);
	tracePGM(p_prefix);
	trace(msg);
}


void tracehex(uint32_t num, uint8_t len)
{
	tracePGM(mDebug_HEXPREF);

	while(len > 0) {
		puthex(num >> (4 * (len - 1)));
		len--;
	}
}


#if defined(DEBUG_BTN)
	#undef DBG_BTN
	#define DBG_BTN(block) block
	#define tracePGMlnBtn(msg) tracePGMln(mDebugBtn_PREFIX, msg)
const unsigned char mDebugBtn_PREFIX[]	PROGMEM =	" Dbg: ";
const unsigned char mDebugBtn_INIT[]	PROGMEM =	"Button enabled";
const unsigned char mDebugBtn_WAIT[]	PROGMEM =	"Wait input";

void buttonInit(void)
{
	PORTB |= _BV(PB0);
	DBG_BTN(tracePGMlnBtn(mDebugBtn_INIT);)
}


/* FIXME: the button used was reverse, shortcircuiting when it is released. Code was modified
 * accordingly */
uint8_t checkButton(void)
{
	/* the button is pressed when BUTTON_BIT is clear */
	if(bit_is_clear(PINB, PB0)) {
		_delay_ms(25);

		if(bit_is_clear(PINB, PB0)) return 0;
	}

	return 1;
}


void button(void)
{
	DBG_BTN(tracePGMlnBtn(mDebugBtn_WAIT);)

 	while(1) if(checkButton()) break;

	_delay_ms(250); // Lock input
}
#endif

#endif
