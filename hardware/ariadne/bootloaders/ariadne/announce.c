/* Name: announce.c
 * Author: .
 * Copyright: Arduino
 * License: GPL http://www.gnu.org/licenses/gpl-2.0.html
 * Project: eboot
 * Function: announcement (Network broadcast)
 * Version: 0.1 tftp / flashing functional
 */

#include <avr/pgmspace.h>
#include <string.h>

#include	"announce.h"
#include	"spi.h"
#include	"w5100.h"
#include	"debug.h"
#include	"debug_ann.h"

#if defined(ANNOUNCE)
uint16_t readPointer;
char* hex = "0123456789ABCDEF";
const char bootloaderIdentString[] PROGMEM = "Ethernet 1.0";


uint8_t readNextByte()
{
	uint8_t returnValue;
	returnValue = readPointer++;
	if(readPointer == S2_RX_END) readPointer = S2_RX_START;
	return (returnValue);
}

void announceReply()
{
	uint8_t txBuffer[100];
	uint8_t* txPtr;
	uint8_t packetLength = 0;
	uint16_t writePointer;
	uint8_t value;
	uint8_t i;

	writePointer = spiReadWord(REG_S2_TX_WR0, S2_R_CB) + S2_TX_START;
	txPtr = txBuffer + 2;

	// Send IP address in hex
	//
	for(i = REG_SIPR0; i <= REG_SIPR3; i++) {
		value = spiReadReg(i, S2_R_CB);
		*txPtr++ = hex[value >> 4];
		*txPtr++ = hex[value & 0xf];
	}
	//
	// Tag on ident string
	//
	memcpy_P(txPtr, bootloaderIdentString, bootloaderIdentStringLength);
	packetLength = 8 + bootloaderIdentStringLength;

	// Write packet length at start of packet
	txBuffer[0] = 0;
	txBuffer[1] = packetLength;
	packetLength += 2;
	txPtr = txBuffer;
	while(packetLength--) {
		spiWriteReg(writePointer++, S2_W_CB, *txPtr++);
		if(writePointer == S2_TX_END) writePointer = S2_TX_START;
	}
	spiWriteWord(REG_S2_TX_WR0, S2_W_CB, writePointer - S2_TX_START);
	spiWriteReg(REG_S2_CR, S2_W_CB, CR_SEND);
	while(spiReadReg(REG_S2_CR, S2_R_CB));
}

//FIXME: void announcePacket(uint16_t packetSize) {
void announcePacket()
{
	uint8_t buffer[ANNOUNCE_DATA_SIZE];
	uint16_t packetLength;

	// Transfer entire packet to RAM
	uint8_t* bufPtr = buffer;
	uint16_t count;

	readPointer = spiReadWord(REG_S2_RX_RD0, S2_R_CB) + S2_RX_START;

	// Read destination IP address
	for(count = 0; count < 4; count++) {
		spiWriteReg(REG_S2_DIPR0 + count, S2_W_CB, readNextByte());
	}

	// Read destination port - but ignore it and respond on 5555 anyway.
	readNextByte();
	readNextByte();
	spiWriteWord(REG_S2_DPORT0, S2_W_CB, ANNOUNCE_PORT);

	// Read packet length
	packetLength = readNextByte() | (readNextByte() << 8);

	// Trim overlong packets
	if(packetLength > ANNOUNCE_DATA_SIZE) packetLength = ANNOUNCE_DATA_SIZE;
	for(count = packetLength; --count;) {
		*bufPtr++ = readNextByte();
	}
	spiWriteWord(REG_S2_RX_RD0, S2_W_CB, readPointer - S2_RX_START); // Write back new pointer
	spiWriteWord(REG_S2_CR, S2_W_CB, CR_RECV); // Receive again

	// Dump packet
	bufPtr = buffer;

	// Parse packet
	if(memcmp(buffer, "arduino", 7) == 0) announceReply();
}

void announceInit()
{
	// Open socket
	do {
		spiWriteWord(REG_S2_PORT0, S2_W_CB, ANNOUNCE_PORT);
		spiWriteReg(REG_S2_MR, S2_W_CB, MR_UDP);
		spiWriteReg(REG_S2_CR, S2_W_CB, CR_OPEN);
		if(spiReadReg(REG_S2_SR, S2_R_CB) != SOCK_UDP)
			spiWriteReg(REG_S2_CR, S2_W_CB, CR_CLOSE);
	} while(spiReadReg(REG_S2_SR, S2_R_CB) != SOCK_UDP);


	DBG_ANN(tracePGMlnAnn(mDebugAnn_DONE);)

}

void announcePoll()
{
	uint16_t packetSize = spiReadWord(REG_S2_RX_RSR0, S2_R_CB);

	if(packetSize) {
		announcePacket(packetSize);
		// Close the socket
		spiWriteReg(REG_S2_CR, S2_W_CB, CR_CLOSE);
		announceInit();
	}
}

#endif
