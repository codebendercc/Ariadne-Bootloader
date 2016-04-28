/* Name: serial.c
 * Author: .
 * Copyright: Stelios Tsampas with stuff from Arduino and optiboot
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: tftpboot
 * Function: UART support of optiboot and debugging
 * Version: 0.2 support for USB flashing
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "serial.h"
#include "watchdog.h"
#include "util.h"
#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1284P__)
	#include "optiboot.h"
#elif defined(__AVR_ATmega2560__)
	#include "stk500boot.h"
#else
	#error "Unknown MCU. Cannot find the proper serial bootloader."
#endif



void serialInit(void)
{
	// Double speed mode USART0
	UART_STATUS_REG		= _BV(UART_DOUBLE_SPEED);
	// Enable receiver and transiter on USART0
	UART_CONTROL_REG	= _BV(UART_ENABLE_RECEIVER) | _BV(UART_ENABLE_TRANSMITTER);
	// Set 8bit character length on USART0
	UART_MODE_REG		= _BV(UART_CHAR_SIZE_LOW) | _BV(UART_CHAR_SIZE_MID);
	// Set USART0 baud rate
	UART_BAUD_RATE_LOW	= (uint8_t)((F_CPU + BAUD_RATE * 4L) / (BAUD_RATE * 8L) - 1);
	// Alternative way taken from stk500boot
	//UART_BAUD_RATE_LOW	= UART_BAUD_SELECT(BAUDRATE, F_CPU);


#if (DEBUG > 0)
	DDRD = 0x92;
#endif

}


void putch(uint8_t c)
{
	while(!(UART_STATUS_REG & _BV(UART_DATA_REG_EMPTY)));
	UART_DATA_REG = c;
}


void puthex(uint8_t c)
{
	c &= 0xf;
	if(c > 9) c += 7;
	//while(!(UART_STATUS_REG & _BV(UART_DATA_REG_EMPTY)));
	//UART_DATA_REG = c + '0';
	putch(c + '0');
}


uint8_t getch(void)
{
	//uint8_t ch;

	while(!(UART_STATUS_REG & _BV(UART_RECEIVE_COMPLETE)));
	if(!(UART_STATUS_REG & _BV(UART_FRAME_ERROR))) {
		/*
		 * A Framing Error indicates (probably) that something is talking
		 * to us at the wrong bit rate.  Assume that this is because it
		 * expects to be talking to the application, and DON'T reset the
		 * watchdog.  This should cause the bootloader to abort and run
		 * the application "soon", if it keeps happening.  (Note that we
		 * don't care that an invalid char is returned...)
		 */
		wdt_reset();
	}

	//ch = UART_DATA_REG;
	//return ch;

	return(UART_DATA_REG);
}


uint8_t serialPoll(void)
{
	if(UART_STATUS_REG & _BV(UART_RECEIVE_COMPLETE)) {
		resetTick();
		serialFlashing = TRUE;
#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1284P__)
		return(processOptiboot());
#elif defined(__AVR_ATmega2560__)
		return(processStk500boot());
#endif
	}
	return(1);
}
