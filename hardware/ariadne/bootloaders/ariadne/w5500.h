#ifndef w5100_h
#define w5100_h
#endif

//Mode
#define REG_MR          0x0000
//GW Address
#define REG_GAR0        0x0001
#define REG_GAR1        0x0002
#define REG_GAR2        0x0003
#define REG_GAR3        0x0004
//Mask
#define REG_SUBR0       0x0005
#define REG_SUBR1       0x0006
#define REG_SUBR2       0x0007
#define REG_SUBR3       0x0008
//Mac Address (Source Hardware Address)
#define REG_SHAR0       0x0009
#define REG_SHAR1       0x000A
#define REG_SHAR2       0x000B
#define REG_SHAR3       0x000C
#define REG_SHAR4       0x000D
#define REG_SHAR5       0x000E
//IP Address (Source IP Address)
#define REG_SIPR0       0x000F
#define REG_SIPR1       0x0010
#define REG_SIPR2       0x0011
#define REG_SIPR3       0x0012
//Interrupt
#define REG_IR          0x0015
//Interrupt Mask
#define REG_IMR         0x0016
//Retry Time
#define REG_RTR0        0x0019
#define REG_RTR1        0x001A
//Retry Count
#define REG_RCR         0x001B
//RX Memory Size
//#define REG_RMSR        0x01A
//TX Memory Size
//#define REG_TMSR        0x01B
//PPPoE Auth
//#define REG_PATR0       0x001C
//#define REG_PATR1       0x001D
//PPP LCP Request Timer
//#define REG_PTIMER      0x0028
//PPP LCP Magic Number
//#define REG_PMAGIC      0x0029
/*
//Unreachable IP Address
#define REG_UIPR0       0x02A
#define REG_UIPR1       0x02B
#define REG_UIPR2       0x02C
#define REG_UIPR3       0x02D
//Unreachable Port
#define REG_UPORT0      0x02E
#define REG_UPORT1      0x02F
*/
/**
 * Socket 0 addresses */
//Mode
#define REG_S0_MR       0x0000
//Command
#define REG_S0_CR       0x0001
//Interrupt
#define REG_S0_IR       0x0002
//Status
#define REG_S0_SR       0x0003
//Source Port
#define REG_S0_PORT0    0x0004
#define REG_S0_PORT1    0x0005
//Destination Hardware Address
#define REG_S0_DHAR0    0x0006
#define REG_S0_DHAR1    0x0007
#define REG_S0_DHAR2    0x0008
#define REG_S0_DHAR3    0x0009
#define REG_S0_DHAR4    0x000A
#define REG_S0_DHAR5    0x000B
//Destination IP Address
#define REG_S0_DIPR0    0x000C
#define REG_S0_DIPR1    0x000D
#define REG_S0_DIPR2    0x000E
#define REG_S0_DIPR3    0x000F
//Destination Port
#define REG_S0_DPORT0   0x0010
#define REG_S0_DPORT1   0x0011
//Maximum Segment Size
#define REG_S0_MSSR0    0x0012
#define REG_S0_MSSR1    0x0013
//TOS
#define REG_S0_TOS      0x0015
//TTL
#define REG_S0_TTL      0x0016
//TX Free Size
#define REG_S0_TX_FSR0  0x0020
#define REG_S0_TX_FSR1  0x0021
//TX Read Pointer
#define REG_S0_TX_RD0   0x0022
#define REG_S0_TX_RD1   0x0023
//TX Write Pointer
#define REG_S0_TX_WR0   0x0024
#define REG_S0_TX_WR1   0x0025
//RX Received Size
#define REG_S0_RX_RSR0  0x0026
#define REG_S0_RX_RSR1  0x0027
//RX Read Pointer
#define REG_S0_RX_RD0   0x0028
#define REG_S0_RX_RD1   0x0029
/**
 * Socket 1 addresses */
#define REG_S1_MR       0x0000
#define REG_S1_CR       0x0001
#define REG_S1_IR       0x0002
#define REG_S1_SR       0x0003
#define REG_S1_PORT0    0x0004
#define REG_S1_PORT1    0x0005
#define REG_S1_DHAR0    0x0006
#define REG_S1_DHAR1    0x0007
#define REG_S1_DHAR2    0x0008
#define REG_S1_DHAR3    0x0009
#define REG_S1_DHAR4    0x000A
#define REG_S1_DHAR5    0x000B
#define REG_S1_DIPR0    0x000C
#define REG_S1_DIPR1    0x000D
#define REG_S1_DIPR2    0x000E
#define REG_S1_DIPR3    0x000F
#define REG_S1_DPORT0   0x0010
#define REG_S1_DPORT1   0x0011
#define REG_S1_MSSR0    0x0012
#define REG_S1_MSSR1    0x0013
#define REG_S1_TOS      0x0015
#define REG_S1_TTL      0x0016
#define REG_S1_TX_FSR0  0x0020
#define REG_S1_TX_FSR1  0x0021
#define REG_S1_TX_RD0   0x0022
#define REG_S1_TX_RD1   0x0023
#define REG_S1_TX_WR0   0x0024
#define REG_S1_TX_WR1   0x0025
#define REG_S1_RX_RSR0  0x0026
#define REG_S1_RX_RSR1  0x0027
#define REG_S1_RX_RD0   0x0028
#define REG_S1_RX_RD1   0x0029
/**
 * Socket 2 addresses */
#define REG_S2_MR       0x0000
#define REG_S2_CR       0x0001
#define REG_S2_IR       0x0002
#define REG_S2_SR       0x0003
#define REG_S2_PORT0    0x0004
#define REG_S2_PORT1    0x0005
#define REG_S2_DHAR0    0x0006
#define REG_S2_DHAR1    0x0007
#define REG_S2_DHAR2    0x0008
#define REG_S2_DHAR3    0x0009
#define REG_S2_DHAR4    0x000A
#define REG_S2_DHAR5    0x000B
#define REG_S2_DIPR0    0x000C
#define REG_S2_DIPR1    0x000D
#define REG_S2_DIPR2    0x000E
#define REG_S2_DIPR3    0x000F
#define REG_S2_DPORT0   0x0010
#define REG_S2_DPORT1   0x0011
#define REG_S2_MSSR0    0x0012
#define REG_S2_MSSR1    0x0013
#define REG_S2_TOS      0x0015
#define REG_S2_TTL      0x0016
#define REG_S2_TX_FSR0  0x0020
#define REG_S2_TX_FSR1  0x0021
#define REG_S2_TX_RD0   0x0022
#define REG_S2_TX_RD1   0x0023
#define REG_S2_TX_WR0   0x0024
#define REG_S2_TX_WR1   0x0025
#define REG_S2_RX_RSR0  0x0026
#define REG_S2_RX_RSR1  0x0027
#define REG_S2_RX_RD0   0x0028
#define REG_S2_RX_RD1   0x0029
/**
 * Socket 3 addresses */
#define REG_S3_MR       0x0000
#define REG_S3_CR       0x0001
#define REG_S3_IR       0x0002
#define REG_S3_SR       0x0003
#define REG_S3_PORT0    0x0004
#define REG_S3_PORT1    0x0005
#define REG_S3_DHAR0    0x0006
#define REG_S3_DHAR1    0x0007
#define REG_S3_DHAR2    0x0008
#define REG_S3_DHAR3    0x0009
#define REG_S3_DHAR4    0x000A
#define REG_S3_DHAR5    0x000B
#define REG_S3_DIPR0    0x000C
#define REG_S3_DIPR1    0x000D
#define REG_S3_DIPR2    0x000E
#define REG_S3_DIPR3    0x000F
#define REG_S3_DPORT0   0x0010
#define REG_S3_DPORT1   0x0011
#define REG_S3_MSSR0    0x0012
#define REG_S3_MSSR1    0x0013
#define REG_S3_TOS      0x0015
#define REG_S3_TTL      0x0016
#define REG_S3_TX_FSR0  0x0020
#define REG_S3_TX_FSR1  0x0021
#define REG_S3_TX_RD0   0x0022
#define REG_S3_TX_RD1   0x0023
#define REG_S3_TX_WR0   0x0024
#define REG_S3_TX_WR1   0x0025
#define REG_S3_RX_RSR0  0x0026
#define REG_S3_RX_RSR1  0x0027
#define REG_S3_RX_RD0   0x0028
#define REG_S3_RX_RD1   0x0029

#define S0_TX_START 0x0000
#define S0_TX_END   0x0800
#define S1_TX_START 0x1000
#define S1_TX_END   0x1800
#define S2_TX_START 0x1800
#define S2_TX_END   0x2000
#define S3_TX_START 0x2000
#define S3_TX_END   0x2800
#define S0_RX_START 0x0000
#define S0_RX_END   0x0800
#define S1_RX_START 0x0800
#define S1_RX_END   0x1000
#define S2_RX_START 0x1800
#define S2_RX_END   0x2000
#define S3_RX_START 0x2800
#define S3_RX_END   0x3000

#define MR_CLOSED         0x00
#define MR_TCP            0x01
#define MR_UDP            0x02
#define MR_IPRAW          0x03
#define MR_MACRAW         0x04
#define MR_PPPOE          0x05
/**
 * Sn_CR (Socket n Command Register)[R/W] [0x0401,0x0501,0x0601,0x0701] [0x00]
 * This register is utilized for socket n initialization, close, connection
 * establishment, termination, data transmission and command receipt. After
 * performing the commands, the register value will be automatically cleared to 0x00. */
#define CR_OPEN           0x01
#define CR_LISTEN         0x02
#define CR_CONNECT        0x04
#define CR_DISCON         0x08
#define CR_CLOSE          0x10
#define CR_SEND           0x20
#define CR_SEND_MAC       0x21
#define CR_SEND_KEEP      0x22
#define CR_RECV           0x40
/**
 * Sn_SR (Socket n Status Register) [R] [0x0403, 0x0503, 0x0603, 0x0703] [0x00]
 * This register has the status value of socket n. The main status is shown
 * in the below diagram. */
#define SOCK_CLOSED       0x00
//#define SOCK_ARP1         0x11
#define SOCK_INIT         0x13
#define SOCK_LISTEN       0x14
#define SOCK_SYNSENT      0x15
#define SOCK_SYNRECV      0x16
#define SOCK_ESTABLISHED  0x17
#define SOCK_FIN_WAIT     0x18
#define SOCK_CLOSING      0x1A
#define SOCK_TIME_WAIT    0x1B
#define SOCK_CLOSE_WAIT   0x1C
#define SOCK_LAST_ACK     0x1D
//#define SOCK_ARP2         0x21
#define SOCK_UDP          0x22
//#define SOCK_ARP3         0x31
#define SOCK_IPRAW        0x32
#define SOCK_MACRAW       0x42
#define SOCK_PPPOE        0x5F
/**
 * Sn_IR (Socket n Interrupt Register) [R] [0x0402, 0x0502, 0x0602, 0x0702] [0x00]
 * This register is used for notifying connection establishment and termination, receiving data
 * and Timeout. The Socket n Interrupt Register must be cleared by writing ‘1’. */
#define IR_SEND_OK   0x10
#define IR_TIMEOUT   0x08
#define IR_RECV      0x04
#define IR_DISCON    0x02
#define IR_CON       0x01
//#define IR_CLR       0x00


void netInit(void);

