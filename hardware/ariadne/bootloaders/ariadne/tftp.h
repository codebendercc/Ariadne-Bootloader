#ifndef tftp_h
#define tftp_h

/** TFTP port settings */
#define TFTP_PORT 69
#define TFTP_DATA_PORT 46969
/** Define this if you want random port generation */
//#define RANDOM_TFTP_DATA_PORT

#define TFTP_OPCODE_UKN   0
/** TFTP Opcode values from RFC 1350 */
#define TFTP_OPCODE_RRQ     1
#define TFTP_OPCODE_WRQ     2
#define TFTP_OPCODE_DATA    3
#define TFTP_OPCODE_ACK     4
#define TFTP_OPCODE_ERROR   5

/** TFTP Error codes from RFC 1350 */
#define TFTP_ERROR_UNDEF        0
#define TFTP_ERROR_NOT_FOUND    1
#define TFTP_ERROR_ACCESS       2
#define TFTP_ERROR_FULL         3
#define TFTP_ERROR_ILLEGAL_OP   4
#define TFTP_ERROR_UNKNOWN_XFER 4
#define TFTP_ERROR_EXISTS       6
#define TFTP_ERROR_NO_SUCH_USER 7

/** TFTP message types */
#define ERROR_UNKNOWN 0
#define ERROR_INVALID 1
#define ACK           2
#define ERROR_FULL    3
#define FINAL_ACK     4 /// Like an ACK, but for the final data packet. Internal use only.
#define INVALID_IMAGE 5


#if defined(__AVR_ATmega328P__)
	#define MAX_ADDR	0x7000	/// For 328p with 2Kword bootloader
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1284P__)
	#define MAX_ADDR	0x1F000	/// For 1280 with 2Kword bootloader
#elif defined(__AVR_ATmega2560__)
	#define MAX_ADDR	0x3F000	/// For 2560 with 2Kword bootloader
#endif

#define TFTP_DATA_SIZE   	512
#define UDP_HEADER_SIZE  	8
#define TFTP_OPCODE_SIZE 	2
#define TFTP_BLOCKNO_SIZE	2
#define TFTP_MAX_PAYLOAD 	512
#define TFTP_PACKET_MAX_SIZE (UDP_HEADER_SIZE+TFTP_OPCODE_SIZE+\
                              TFTP_BLOCKNO_SIZE+TFTP_MAX_PAYLOAD)

#define TFTP_PACKET_DELAY	400

/**
 * Tftp status flag, it is set to TRUE if flashing from
 * tftp is currently active */
uint8_t tftpFlashing;

#ifndef TFTP_RANDOM_PORT
uint16_t tftpTransferPort;
#endif

void tftpInit(void);
uint8_t tftpPoll(void);

#endif
