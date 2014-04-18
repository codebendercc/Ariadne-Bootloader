/*
 * Title:     STK500v2 compatible bootloader
 * 		Modified for Ariadne bootloader
 * Author:    Peter Fleury <pfleury@gmx.ch>   http://jump.to/fleury
 * File:      $Id: stk500boot.c,v 1.11 2006/06/25 12:39:17 peter Exp $
 * Compiler:  avr-gcc 3.4.5 or 4.1 / avr-libc 1.4.3
 * Hardware:  All AVRs with bootloader support, tested with ATmega8
 * License:   GNU General Public License
 *
 * Modified:  Worapoht Kornkaewwattanakul <dev@avride.com>   http://www.avride.com
 * Date:      17 October 2007
 * Update:    1st, 29 Dec 2007 : Enable CMD_SPI_MULTI but ignore unused command by return 0x00 byte response..
 * Compiler:  WINAVR20060421
 * Description: add timeout feature like previous Wiring bootloader
 *
 * Modified:  Stelios Tsampas <loathingkernel@gmail.com>  http://codebender.cc
 * Date:      14 April 2013
 * Compiler:  avr-gcc 4.7.2
 * Description: adjusted to fit Ariadne bootloader
 */

//************************************************************************
//*	Edit History
//************************************************************************
//*	Jul  7,	2010	<MLS> = Mark Sproul msproul@skycharoit.com
//*	Jul  7,	2010	<MLS> Working on mega2560. No Auto-restart
//*	Jul  7,	2010	<MLS> Switched to 8K bytes (4K words) so that we have room for the monitor
//*	Jul  8,	2010	<MLS> Found older version of source that had auto restart, put that code back in
//*	Jul  8,	2010	<MLS> Adding monitor code
//*	Jul 11,	2010	<MLS> Added blinking LED while waiting for download to start
//*	Jul 11,	2010	<MLS> Added EEPROM test
//*	Jul 29,	2010	<MLS> Added recchar_timeout for timing out on bootloading
//*	Aug 23,	2010	<MLS> Added support for atmega2561
//*	Aug 26,	2010	<MLS> Removed support for BOOT_BY_SWITCH
//*	Sep  8,	2010	<MLS> Added support for atmega16
//*	Nov  9,	2010	<MLS> Issue 392:Fixed bug that 3 !!! in code would cause it to jump to monitor
//*	Jun 24,	2011	<MLS> Removed analogRead (was not used)
//*	Dec 29,	2011	<MLS> Issue 181: added watch dog timmer support
//*	Dec 29,	2011	<MLS> Issue 505:  bootloader is comparing the seqNum to 1 or the current sequence
//*	Jan  1,	2012	<MLS> Issue 543: CMD_CHIP_ERASE_ISP now returns STATUS_CMD_FAILED instead of STATUS_CMD_OK
//*	Jan  1,	2012	<MLS> Issue 543: Write EEPROM now does something (NOT TESTED)
//*	Jan  1,	2012	<MLS> Issue 544: stk500v2 bootloader doesn't support reading fuses
//************************************************************************


//#include	<inttypes.h>
//#include	<avr/io.h>
//#include	<avr/interrupt.h>
//#include	<avr/boot.h>
//#include	<avr/pgmspace.h>
//#include	<util/delay.h>
//#include	<avr/common.h>
//#include	<stdlib.h>
//#include	<avr/sfr_defs.h>

#include	<inttypes.h>
#include	<avr/io.h>
#include	<avr/pgmspace.h>
#include	<avr/boot.h>
#include	<avr/eeprom.h>

#include	"util.h"
#include	"serial.h"
#include	"watchdog.h"
#include	"neteeprom.h"
#include	"stk500boot.h"
#include	"stk500boot_command.h"


// #define	MAX_TIME_COUNT	(F_CPU >> 1)
// static unsigned char recchar_timeout(void)
// {
// 	uint32_t count = 0;
//
// 	while(!(UART_STATUS_REG & (1 << UART_RECEIVE_COMPLETE))) {
// 		// wait for data
// 		count++;
//
// 		if(count > MAX_TIME_COUNT) {
// 			unsigned int	data;
// #if (FLASHEND > 0x10000)
// 			data	=	pgm_read_word_far(0);	//*	get the first word of the user program
// #else
// 			data	=	pgm_read_word_near(0);	//*	get the first word of the user program
// #endif
//
// 			if(data != 0xffff) {				//*	make sure its valid before jumping to it.
// 				asm volatile(
// 				    "clr	r30		\n\t"
// 				    "clr	r31		\n\t"
// 				    "ijmp	\n\t"
// 				);
// 			}
//
// 			count	=	0;
// 		}
// 	}
//
// 	return UART_DATA_REG;
// }


uint8_t processStk500boot(void)
{
	address_t		address			=	0;
	address_t		eraseAddress	=	0;
	unsigned char	msgParseState;
	unsigned int	ii				=	0;
	unsigned char	checksum		=	0;
	unsigned char	seqNum			=	0;
	unsigned int	msgLength		=	0;
	unsigned char	msgBuffer[285];
	unsigned char	c, *p;
	unsigned char   isLeave = 0;

	while(!isLeave) {
		/*
		 * Collect received bytes to a complete message
		 */
		msgParseState	=	ST_START;

		while(msgParseState != ST_PROCESS) {
// 			if(boot_state == 1) {
// 				boot_state	=	0;
 				c			=	getch();
// 			} else {
// 				//	c	=	recchar();
// 				c = recchar_timeout();
// 			}

			switch(msgParseState) {
				case ST_START:

					if(c == MESSAGE_START) {
						msgParseState	=	ST_GET_SEQ_NUM;
						checksum		=	MESSAGE_START ^ 0;
					}

					break;

				case ST_GET_SEQ_NUM:
#ifdef _FIX_ISSUE_505_
					seqNum			=	c;
					msgParseState	=	ST_MSG_SIZE_1;
					checksum		^=	c;
#else

					if((c == 1) || (c == seqNum)) {
						seqNum			=	c;
						msgParseState	=	ST_MSG_SIZE_1;
						checksum		^=	c;
					} else {
						msgParseState	=	ST_START;
					}

#endif
					break;

				case ST_MSG_SIZE_1:
					msgLength		=	c << 8;
					msgParseState	=	ST_MSG_SIZE_2;
					checksum		^=	c;
					break;

				case ST_MSG_SIZE_2:
					msgLength		|=	c;
					msgParseState	=	ST_GET_TOKEN;
					checksum		^=	c;
					break;

				case ST_GET_TOKEN:

					if(c == TOKEN) {
						msgParseState	=	ST_GET_DATA;
						checksum		^=	c;
						ii				=	0;
					} else {
						msgParseState	=	ST_START;
					}

					break;

				case ST_GET_DATA:
					msgBuffer[ii++]	=	c;
					checksum		^=	c;

					if(ii == msgLength) {
						msgParseState	=	ST_GET_CHECK;
					}

					break;

				case ST_GET_CHECK:

					if(c == checksum) {
						msgParseState	=	ST_PROCESS;
					} else {
						msgParseState	=	ST_START;
					}

					break;
			}	//	switch
		}	//	while(msgParseState)

		/*
		 * Now process the STK500 commands, see Atmel Appnote AVR068
		 */

		switch(msgBuffer[0]) {
#ifndef REMOVE_CMD_SPI_MULTI
			case CMD_SPI_MULTI: {
				unsigned char answerByte;
				unsigned char flag = 0;

				if(msgBuffer[4] == 0x30) {
					unsigned char signatureIndex	=	msgBuffer[6];

					if(signatureIndex == 0) {
						//answerByte	=	(SIGNATURE_BYTES >> 16) & 0x000000FF;
						answerByte	=	SIGNATURE_0;
					} else if(signatureIndex == 1) {
						//answerByte	=	(SIGNATURE_BYTES >> 8) & 0x000000FF;
						answerByte	=	SIGNATURE_1;
					} else {
						//answerByte	=	SIGNATURE_BYTES & 0x000000FF;
						answerByte	=	SIGNATURE_2;
					}
				} else if(msgBuffer[4] & 0x50) {
					//*	Issue 544: 	stk500v2 bootloader doesn't support reading fuses
					//*	I cant find the docs that say what these are supposed to be but this was figured out by trial and error
					//	answerByte	=	boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
					//	answerByte	=	boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
					//	answerByte	=	boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
					if(msgBuffer[4] == 0x50) {
						answerByte	=	boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
					} else if(msgBuffer[4] == 0x58) {
						answerByte	=	boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
					} else {
						answerByte	=	0;
					}
				} else {
					answerByte	=	0; // for all others command are not implemented, return dummy value for AVRDUDE happy <Worapoht>
				}

				if(!flag) {
					msgLength		=	7;
					msgBuffer[1]	=	STATUS_CMD_OK;
					msgBuffer[2]	=	0;
					msgBuffer[3]	=	msgBuffer[4];
					msgBuffer[4]	=	0;
					msgBuffer[5]	=	answerByte;
					msgBuffer[6]	=	STATUS_CMD_OK;
				}
			}
			break;
#endif
			case CMD_SIGN_ON:
				msgLength		=	11;
				msgBuffer[1] 	=	STATUS_CMD_OK;
				msgBuffer[2] 	=	8;
				msgBuffer[3] 	=	'A';
				msgBuffer[4] 	=	'V';
				msgBuffer[5] 	=	'R';
				msgBuffer[6] 	=	'I';
				msgBuffer[7] 	=	'S';
				msgBuffer[8] 	=	'P';
				msgBuffer[9] 	=	'_';
				msgBuffer[10]	=	'2';
				break;

			case CMD_GET_PARAMETER: {
				unsigned char value;

				switch(msgBuffer[1]) {
					case PARAM_BUILD_NUMBER_LOW:
						value	=	CONFIG_PARAM_BUILD_NUMBER_LOW;
						break;
					case PARAM_BUILD_NUMBER_HIGH:
						value	=	CONFIG_PARAM_BUILD_NUMBER_HIGH;
						break;
					case PARAM_HW_VER:
						value	=	CONFIG_PARAM_HW_VER;
						break;
					case PARAM_SW_MAJOR:
						value	=	CONFIG_PARAM_SW_MAJOR;
						break;
					case PARAM_SW_MINOR:
						value	=	CONFIG_PARAM_SW_MINOR;
						break;
					default:
						value	=	0;
						break;
				}

				msgLength		=	3;
				msgBuffer[1]	=	STATUS_CMD_OK;
				msgBuffer[2]	=	value;
			}
			break;

			case CMD_LEAVE_PROGMODE_ISP:
				isLeave	=	1;
				//*	fall thru

			case CMD_SET_PARAMETER:
			case CMD_ENTER_PROGMODE_ISP:
				msgLength		=	2;
				msgBuffer[1]	=	STATUS_CMD_OK;
				break;

			case CMD_READ_SIGNATURE_ISP: {
				unsigned char signatureIndex	=	msgBuffer[4];
				unsigned char signature;

				if(signatureIndex == 0)
					//signature	=	(SIGNATURE_BYTES >> 16) & 0x000000FF;
					signature	=	SIGNATURE_0;
				else if(signatureIndex == 1)
					//signature	=	(SIGNATURE_BYTES >> 8) & 0x000000FF;
					signature	=	SIGNATURE_1;
				else
					//signature	=	SIGNATURE_BYTES & 0x000000FF;
					signature	=	SIGNATURE_2;

				msgLength		=	4;
				msgBuffer[1]	=	STATUS_CMD_OK;
				msgBuffer[2]	=	signature;
				msgBuffer[3]	=	STATUS_CMD_OK;
			}
			break;

			case CMD_READ_LOCK_ISP:
				msgLength		=	4;
				msgBuffer[1]	=	STATUS_CMD_OK;
				msgBuffer[2]	=	boot_lock_fuse_bits_get(GET_LOCK_BITS);
				msgBuffer[3]	=	STATUS_CMD_OK;
				break;

			case CMD_READ_FUSE_ISP: {
				unsigned char fuseBits;

				if(msgBuffer[2] == 0x50) {
					if(msgBuffer[3] == 0x08)
						fuseBits	=	boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
					else
						fuseBits	=	boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
				} else {
					fuseBits	=	boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
				}

				msgLength		=	4;
				msgBuffer[1]	=	STATUS_CMD_OK;
				msgBuffer[2]	=	fuseBits;
				msgBuffer[3]	=	STATUS_CMD_OK;
			}
			break;

#ifndef REMOVE_PROGRAM_LOCK_BIT_SUPPORT
			case CMD_PROGRAM_LOCK_ISP: {
				unsigned char lockBits	=	msgBuffer[4];

				lockBits	=	(~lockBits) & 0x3C;	// mask BLBxx bits
				boot_lock_bits_set(lockBits);		// and program it
				boot_spm_busy_wait();

				msgLength		=	3;
				msgBuffer[1]	=	STATUS_CMD_OK;
				msgBuffer[2]	=	STATUS_CMD_OK;
			}
			break;
#endif
			case CMD_CHIP_ERASE_ISP:
				eraseAddress	=	0;
				msgLength		=	2;
				//	msgBuffer[1]	=	STATUS_CMD_OK;
				msgBuffer[1]	=	STATUS_CMD_FAILED;	//*	isue 543, return FAILED instead of OK
				break;

			case CMD_LOAD_ADDRESS:
#if defined(RAMPZ)
				address	=	(((address_t)(msgBuffer[1]) << 24) | ((address_t)(msgBuffer[2]) << 16) | ((address_t)(msgBuffer[3]) << 8) | (msgBuffer[4])) << 1;
#else
				address	=	(((msgBuffer[3]) << 8) | (msgBuffer[4])) << 1;		//convert word to byte address
#endif
				msgLength		=	2;
				msgBuffer[1]	=	STATUS_CMD_OK;
				break;

			case CMD_PROGRAM_FLASH_ISP:
			case CMD_PROGRAM_EEPROM_ISP: {
				unsigned int	size	=	((msgBuffer[1]) << 8) | msgBuffer[2];
				unsigned char*	p	=	msgBuffer + 10;
				unsigned int	data;
				unsigned char	highByte, lowByte;
				address_t		tempaddress	=	address;


				if(msgBuffer[0] == CMD_PROGRAM_FLASH_ISP) {
					// erase only main section (bootloader protection)
					if(eraseAddress < APP_END) {
						boot_page_erase(eraseAddress);	// Perform page erase
						boot_spm_busy_wait();		// Wait until the memory is erased.
						eraseAddress += SPM_PAGESIZE;	// point to next page to be erase
					}

					/* Write FLASH */
					do {
						lowByte		=	*p++;
						highByte 	=	*p++;

						data		=	(highByte << 8) | lowByte;
						boot_page_fill(address, data);

						address	=	address + 2;	// Select next word in memory
						size	-=	2;				// Reduce number of bytes to write by two
					} while(size);					// Loop until all bytes written

					boot_page_write(tempaddress);
					boot_spm_busy_wait();
					boot_rww_enable();				// Re-enable the RWW section
				} else {
					//*	issue 543, this should work, It has not been tested.
					//	#if (!defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega2560__)  && !defined(__AVR_ATmega2561__)  && !defined(__AVR_ATmega1284P__)  && !defined(__AVR_ATmega640__))
#if (defined(EEARL) && defined(EEARH)  && defined(EEMWE)  && defined(EEWE)  && defined(EEDR))
					/* write EEPROM */
					do {
						EEARL	=	address;			// Setup EEPROM address
						EEARH	=	(address >> 8);
						address++;						// Select next EEPROM byte

						EEDR	=	*p++;				// get byte from buffer
						EECR	|=	(1 << EEMWE);			// Write data into EEPROM
						EECR	|=	(1 << EEWE);

						while(EECR & (1 << EEWE))
							;	// Wait for write operation to finish

						size--;						// Decrease number of bytes to write
					} while(size);					// Loop until all bytes written

#endif
				}

				msgLength	=	2;
				msgBuffer[1]	=	STATUS_CMD_OK;
			}
			break;

			case CMD_READ_FLASH_ISP:
			case CMD_READ_EEPROM_ISP: {
				unsigned int	size	=	((msgBuffer[1]) << 8) | msgBuffer[2];
				unsigned char*	p		=	msgBuffer + 1;
				msgLength				=	size + 3;

				*p++	=	STATUS_CMD_OK;

				if(msgBuffer[0] == CMD_READ_FLASH_ISP) {
					unsigned int data;

					// Read FLASH
					do {
						//#if defined(RAMPZ)
#if (FLASHEND > 0x10000)
						data	=	pgm_read_word_far(address);
#else
						data	=	pgm_read_word_near(address);
#endif
						*p++	=	(unsigned char)data;		//LSB
						*p++	=	(unsigned char)(data >> 8);	//MSB
						address	+=	2;							// Select next word in memory
						size	-=	2;
					} while(size);
				} else {
					/* Read EEPROM */
					do {
						EEARL	=	address;			// Setup EEPROM address
						EEARH	=	((address >> 8));
						address++;					// Select next EEPROM byte
						EECR	|=	(1 << EERE);			// Read EEPROM
						*p++	=	EEDR;				// Send EEPROM data
						size--;
					} while(size);
				}

				*p++	=	STATUS_CMD_OK;
			}
			break;

			default:
				msgLength		=	2;
				msgBuffer[1]	=	STATUS_CMD_FAILED;
				break;
		}

		/*
		 * Now send answer message back
		 */
		putch(MESSAGE_START);
		checksum	=	MESSAGE_START ^ 0;

		putch(seqNum);
		checksum	^=	seqNum;

		c			=	((msgLength >> 8) & 0xFF);
		putch(c);
		checksum	^=	c;

		c			=	msgLength & 0x00FF;
		putch(c);
		checksum ^= c;

		putch(TOKEN);
		checksum ^= TOKEN;

		p	=	msgBuffer;

		while(msgLength) {
			c	=	*p++;
			putch(c);
			checksum ^= c;
			msgLength--;
		}

		putch(checksum);
		seqNum++;

	}

	asm volatile("nop");			// wait until port has changed

	/*
	 * Now leave bootloader
	 */
	//TODO: find out what this does
	//UART_STATUS_REG	&=	0xfd;
#if defined(RWWSRE)
	boot_rww_enable();				// enable application section
#endif
	eeprom_write_byte(EEPROM_IMG_STAT, EEPROM_IMG_OK_VALUE);
	return(0);
}
