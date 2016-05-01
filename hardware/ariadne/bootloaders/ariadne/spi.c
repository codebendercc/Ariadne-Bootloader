/* Name: spi.c
 * Author: Stelios Tsampas
 * Copyright: Arduino
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: ariadne bootloader
 * Function: SPI functions
 * Version: 0.5 "Mega2560"
 */

#include <avr/io.h>

#include "spi.h"
#include "debug.h"
#include "debug_spi.h"

/** Send uint8_t to Ethernet controller */
void spiWriteReg(uint16_t address, uint8_t cb, uint8_t value)
{
	DBG_SPI_EX(
		tracePGMlnSpi(mDebugSpi_NWREG);
		tracenum(address);
		tracePGM(mDebugSpi_COMMA);
		tracenum(value);
	)

	SPCR = _BV(SPE) | _BV(MSTR); // Set SPI as master
	SS_LOW();

#if (W5200 > 0)

	SPDR = address >> 8;
	while(!(SPSR & _BV(SPIF)));

	SPDR = address & 0xff;
	while(!(SPSR & _BV(SPIF)));

	SPDR = 0x80;
	while(!(SPSR & _BV(SPIF)));

	SPDR = 0x01;
	while(!(SPSR & _BV(SPIF)));

#elif (W5500 > 0)

	SPDR = address >> 8;
	while(!(SPSR & _BV(SPIF)));

	SPDR = address & 0xff;
	while(!(SPSR & _BV(SPIF)));

	SPDR = cb;  //Socket 3 BSB Write 0x6D Selects Socket 3 Register, write mode, 1 byte data length
	while(!(SPSR & _BV(SPIF)));

#else //Standard W5100 Code

	SPDR = SPI_WRITE;
	while(!(SPSR & _BV(SPIF)));

	SPDR = address >> 8;
	while(!(SPSR & _BV(SPIF)));

	SPDR = address & 0xff;
	while(!(SPSR & _BV(SPIF)));

#endif

	SPDR = value;
	while(!(SPSR & _BV(SPIF)));

	SS_HIGH();
	cb = 0; //prevents compiler whining about unused cb variable
	SPCR = cb; // Turn off SPI	

}

void spiWriteWord(uint16_t address, uint8_t cb, uint16_t value)
{
	// Write uint16_t to Ethernet controller
	spiWriteReg(address++, cb, value >> 8);
	spiWriteReg(address, cb, value & 0xff);
}

/** Read uint8_t from Ethernet controller */
uint8_t spiReadReg(uint16_t address, uint8_t cb)
{
	#if defined(SPAM_ME)
	DBG_SPI_EX(
		tracePGMlnSpi(mDebugSpi_NRREG);
		tracenum(address);
	)
	#endif

	uint8_t returnValue;

	SPCR = _BV(SPE) | _BV(MSTR);
	SS_LOW();

#if (W5200 > 0)

	SPDR = address >> 8;
	while(!(SPSR & _BV(SPIF)));

	SPDR = address & 0xff;
	while(!(SPSR & _BV(SPIF)));

	SPDR = 0x00;
	while(!(SPSR & _BV(SPIF)));

	SPDR = 0x01;
	while(!(SPSR & _BV(SPIF)));

#elif (W5500 > 0)
//W5500 code

	SPDR = address >> 8;
	while(!(SPSR & _BV(SPIF)));

	SPDR = address & 0xff;
	while(!(SPSR & _BV(SPIF)));

	SPDR = cb;  //Socket 3 BSB Read 0x69 Selects Socket 3 Register, read mode, 1 byte data length
	while(!(SPSR & _BV(SPIF)));

#else //Standard W5100 Code

	SPDR = SPI_READ;
	while(!(SPSR & _BV(SPIF)));

	SPDR = address >> 8;
	while(!(SPSR & _BV(SPIF)));

	SPDR = address & 0xff;
	while(!(SPSR & _BV(SPIF)));

#endif

	SPDR = 0;
	while(!(SPSR & _BV(SPIF)));

	SS_HIGH();
	returnValue = SPDR;

	cb = 0; //prevents compiler whining about unused cb variable
	SPCR = cb; // Turn off SPI

	return(returnValue);
}

uint16_t spiReadWord(uint16_t address, uint8_t cb)
{
	// Read uint16_t from Ethernet controller
	return((spiReadReg(address, cb) << 8) | spiReadReg(address + 1, cb));
}

void spiInit(void)
{
	/**
	 * Set up pins for SPI communication.
	 * At this stage all pins are set to HIGH. This in fact DISABLES SPI for both Ethernet and SD.
	 * SS pin for ethernet is pulled low just in time for reading or writing data inside those
	 * functions. */

	/** Set SPI pins high */
	SPI_PORT = _BV(SCK) | _BV(MISO) | _BV(MOSI) | _BV(SS);
	/** Set SPI pins as output */
	SPI_DDR = _BV(SCK) | _BV(MOSI) | _BV(SS);

	#if (ETH_SS != SS)
	/** Initialize extra SS pin used in some boards (mega) */
	/** Set ethernet SS high */
	ETH_PORT |= _BV(ETH_SS);
	/** Set ethernet SS as output */
	ETH_DDR |= _BV(ETH_SS);
	#endif

	/** Disable SD card */
	/** Set SD SS pin high */
	SD_PORT |= _BV(SD_SS);
	/** Set SD SS pin as output */
	SD_DDR |= _BV(SD_SS);

	#if (LED != SCK)
	/** Set up pins to flash the onboard led */
	/** Set led pin to high */
	LED_PORT |= _BV(LED);
	/** Set led pin as output */
	LED_DDR |= _BV(LED);
	#endif

	/** Set up SPI
	 ** Set the Double SPI Speed Bit */
	SPSR = (1 << SPI2X);

	DBG_SPI(tracePGMlnSpi(mDebugSpi_DONE);)
}
