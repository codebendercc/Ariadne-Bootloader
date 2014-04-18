/* Name: debug_spi.h
 * Author: Stelios Tsampas
 * Copyright: codebender.cc
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: ariadne
 * Function: debugging progmem strings for SPI subsystem
 * Version: 0.5 "Mega2560"
 */

#ifndef debug_spi_h
#define debug_spi_h

#include <avr/pgmspace.h>


#if (DEBUG_SPI > 0)
	#undef DBG_SPI
	#define DBG_SPI(block) block
	#define tracePGMlnSpi(msg) tracePGMln(mDebugSpi_PREFIX, msg)
const unsigned char mDebugSpi_PREFIX[]	PROGMEM =	" Spi: ";
const unsigned char mDebugSpi_DONE[]	PROGMEM =	"SPI init done";
	#if (DEBUG_SPI > 1)
		#undef DBG_SPI_EX
		#define DBG_SPI_EX(block) block
const unsigned char mDebugSpi_COMMA[]	PROGMEM =	", ";
const unsigned char mDebugSpi_NWREG[]	PROGMEM =	"spiWriteReg: ";
const unsigned char mDebugSpi_NRREG[]	PROGMEM =	"spiReadReg: ";
#endif
#endif

#endif
