/* Name: net_w5200.c
 * Author: .
 * Copyright: Arduino
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: eboot
 * Function: Network initialization
 * Version: 0.1 tftp / flashing functional
 */



uint8_t registerBuffer[REGISTER_BLOCK_SIZE] = {
	0x80,         // MR Mode - reset device

	// EEPROM block starts here
	GW_ADDR,      // GWR Gateway IP Address Register
	SUB_MASK,  // SUBR Subnet Mask Register
	MAC_ADDR,     // SHAR Source Hardware Address Register
	IP_ADDR,      // SIPR Source IP Address Register
	// EEPROM block ends here

	0, 0,         // Reserved locations
	0,            // IR Interrupt Register
	0,            // IMR Interrupt Mask Register
	0x07, 0xd0,   // RTR Retry Time-value Register
	0x08,         // RCR Retry Count Register
	0,            // Reserved in w5200
	0             // Reserved in w5200
};


void netInit(void)
{
	uint8_t i;

	/* Pull in altered network settings, if available,
	 * from AVR EEPROM (if signature bytes are set) */
	if((eeprom_read_byte(EEPROM_SIG_1) == EEPROM_SIG_1_VALUE)
		&& (eeprom_read_byte(EEPROM_SIG_2) == EEPROM_SIG_2_VALUE)) {

		for(i = 0; i < EEPROM_SETTINGS_SIZE; i++)
			registerBuffer[i + 1] = eeprom_read_byte(EEPROM_DATA + i);

		DBG_NET(tracePGMlnNet(mDebugNet_EEPROM);)

	} DBG_NET(
		else tracePGMlnNet(mDebugNet_BUILTIN);
	)


	DBG_NET(
		tracePGMlnNet(mDebugNet_ADDR);
		for(i = 15; i < 19; i++) {
			tracenet(registerBuffer[i]);
			if(i != 18) putch(0x2E);
		}
		tracePGMlnNet(mDebugNet_SUBN);
		for(i = 5; i < 9; i++) {
			tracenet(registerBuffer[i]);
			if(i != 8) putch(0x2E);
		}
		tracePGMlnNet(mDebugNet_GW);
		for(i = 1; i < 5; i++) {
			tracenet(registerBuffer[i]);
			if(i != 4) putch(0x2E);
		}
		tracePGMlnNet(mDebugNet_MAC);
		for(i = 9; i < 15; i++) {
			tracenet(registerBuffer[i]);
			if(i != 14) putch(0x2E);
		}
	)

	/** Configure Wiznet chip. Network settings */
	for(i = 0; i < REGISTER_BLOCK_SIZE-2; i++)
		spiWriteReg(i, 0, registerBuffer[i]);

        for (i=0; i<8; i++) {
        	spiWriteReg((0x4000 + i * 0x100 + 0x001F), 0, 0x02);
                spiWriteReg((0x4000 + i * 0x100 + 0x001E), 0, 0x02);
        }

	DBG_NET(tracePGMlnNet(mDebugNet_DONE);)
}
