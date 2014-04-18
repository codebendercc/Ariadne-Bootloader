/* Name: watchdog.c
 * Author: Stelios Tsampas
 * Copyright: Stelios Tsampas
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: ethboot
 * Function: watchdog/reset handling
 * Version: 0.2 tftp / flashing functional
 */

#include <stdint.h>
#include <avr/wdt.h>

#include "watchdog.h"
#include "debug.h"


 /* Disable the watchdog timer to prevent
  * eternal reset loop of doom and despair */
uint8_t watchdogDisable(void)
{
	uint8_t mcusr_mirror;

	mcusr_mirror = MCUSR;
	MCUSR = 0;
	wdt_disable();

	return(mcusr_mirror);
}

void watchdogReset(void)
{
	wdt_reset();
}

void watchdogConfig(uint8_t x)
{
	WDTCSR = _BV(WDCE) | _BV(WDE);
	WDTCSR = x;
}
