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
#define REG_RTR0        0x0017
#define REG_RTR1        0x0018
//Retry Count
#define REG_RCR         0x0019
//RX Memory Size
//#define REG_RMSR        0x01A
//TX Memory Size
//#define REG_TMSR        0x01B
//PPPoE Auth
#define REG_PATR0       0x001C
#define REG_PATR1       0x001D
//PPP LCP Request Timer
#define REG_PTIMER      0x0028
//PPP LCP Magic Number
#define REG_PMAGIC      0x0029
/* Reserved in the W5200
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
#define REG_S0_MR       0x4000
//Command
#define REG_S0_CR       0x4001
//Interrupt
#define REG_S0_IR       0x4002
//Status
#define REG_S0_SR       0x4003
//Source Port
#define REG_S0_PORT0    0x4004
#define REG_S0_PORT1    0x4005
//Destination Hardware Address
#define REG_S0_DHAR0    0x4006
#define REG_S0_DHAR1    0x4007
#define REG_S0_DHAR2    0x4008
#define REG_S0_DHAR3    0x4009
#define REG_S0_DHAR4    0x400A
#define REG_S0_DHAR5    0x400B
//Destination IP Address
#define REG_S0_DIPR0    0x400C
#define REG_S0_DIPR1    0x400D
#define REG_S0_DIPR2    0x400E
#define REG_S0_DIPR3    0x400F
//Destination Port
#define REG_S0_DPORT0   0x4010
#define REG_S0_DPORT1   0x4011
//Maximum Segment Size
#define REG_S0_MSSR0    0x4012
#define REG_S0_MSSR1    0x4013
//Protocol in Raw Mode
#define REG_S0_PROTO    0x4014
//TOS
#define REG_S0_TOS      0x4015
//TTL
#define REG_S0_TTL      0x4016
//TX Free Size
#define REG_S0_TX_FSR0  0x4020
#define REG_S0_TX_FSR1  0x4021
//TX Read Pointer
#define REG_S0_TX_RD0   0x4022
#define REG_S0_TX_RD1   0x4023
//TX Write Pointer
#define REG_S0_TX_WR0   0x4024
#define REG_S0_TX_WR1   0x4025
//RX Received Size
#define REG_S0_RX_RSR0  0x4026
#define REG_S0_RX_RSR1  0x4027
//RX Read Pointer
#define REG_S0_RX_RD0   0x4028
#define REG_S0_RX_RD1   0x4029
/**
 * Socket 1 addresses */
#define REG_S1_MR       0x4100
#define REG_S1_CR       0x4101
#define REG_S1_IR       0x4102
#define REG_S1_SR       0x4103
#define REG_S1_PORT0    0x4104
#define REG_S1_PORT1    0x4105
#define REG_S1_DHAR0    0x4106
#define REG_S1_DHAR1    0x4107
#define REG_S1_DHAR2    0x4108
#define REG_S1_DHAR3    0x4109
#define REG_S1_DHAR4    0x410A
#define REG_S1_DHAR5    0x410B
#define REG_S1_DIPR0    0x410C
#define REG_S1_DIPR1    0x410D
#define REG_S1_DIPR2    0x410E
#define REG_S1_DIPR3    0x410F
#define REG_S1_DPORT0   0x4110
#define REG_S1_DPORT1   0x4111
#define REG_S1_MSSR0    0x4112
#define REG_S1_MSSR1    0x4113
#define REG_S1_PROTO    0x4114
#define REG_S1_TOS      0x4115
#define REG_S1_TTL      0x4116
#define REG_S1_TX_FSR0  0x4120
#define REG_S1_TX_FSR1  0x4121
#define REG_S1_TX_RD0   0x4122
#define REG_S1_TX_RD1   0x4123
#define REG_S1_TX_WR0   0x4124
#define REG_S1_TX_WR1   0x4125
#define REG_S1_RX_RSR0  0x4126
#define REG_S1_RX_RSR1  0x4127
#define REG_S1_RX_RD0   0x4128
#define REG_S1_RX_RD1   0x4129
/*
 * Socket 2 addresses */
#define REG_S2_MR       0x4200
#define REG_S2_CR       0x4201
#define REG_S2_IR       0x4202
#define REG_S2_SR       0x4203
#define REG_S2_PORT0    0x4204
#define REG_S2_PORT1    0x4205
#define REG_S2_DHAR0    0x4206
#define REG_S2_DHAR1    0x4207
#define REG_S2_DHAR2    0x4208
#define REG_S2_DHAR3    0x4209
#define REG_S2_DHAR4    0x420A
#define REG_S2_DHAR5    0x420B
#define REG_S2_DIPR0    0x420C
#define REG_S2_DIPR1    0x420D
#define REG_S2_DIPR2    0x420E
#define REG_S2_DIPR3    0x420F
#define REG_S2_DPORT0   0x4210
#define REG_S2_DPORT1   0x4211
#define REG_S2_MSSR0    0x4212
#define REG_S2_MSSR1    0x4213
#define REG_S2_PROTO    0x4214
#define REG_S2_TOS      0x4215
#define REG_S2_TTL      0x4216
#define REG_S2_TX_FSR0  0x4220
#define REG_S2_TX_FSR1  0x4221
#define REG_S2_TX_RD0   0x4222
#define REG_S2_TX_RD1   0x4223
#define REG_S2_TX_WR0   0x4224
#define REG_S2_TX_WR1   0x4225
#define REG_S2_RX_RSR0  0x4226
#define REG_S2_RX_RSR1  0x4227
#define REG_S2_RX_RD0   0x4228
#define REG_S2_RX_RD1   0x4229
/*
 * Socket 3 addresses */
#define REG_S3_MR       0x4300
#define REG_S3_CR       0x4301
#define REG_S3_IR       0x4302
#define REG_S3_SR       0x4303
#define REG_S3_PORT0    0x4304
#define REG_S3_PORT1    0x4305
#define REG_S3_DHAR0    0x4306
#define REG_S3_DHAR1    0x4307
#define REG_S3_DHAR2    0x4308
#define REG_S3_DHAR3    0x4309
#define REG_S3_DHAR4    0x430A
#define REG_S3_DHAR5    0x430B
#define REG_S3_DIPR0    0x430C
#define REG_S3_DIPR1    0x430D
#define REG_S3_DIPR2    0x430E
#define REG_S3_DIPR3    0x430F
#define REG_S3_DPORT0   0x4310
#define REG_S3_DPORT1   0x4311
#define REG_S3_MSSR0    0x4312
#define REG_S3_MSSR1    0x4313
#define REG_S3_PROTO    0x4314
#define REG_S3_TOS      0x4315
#define REG_S3_TTL      0x4316
#define REG_S3_TX_FSR0  0x4320
#define REG_S3_TX_FSR1  0x4321
#define REG_S3_TX_RD0   0x4322
#define REG_S3_TX_RD1   0x4323
#define REG_S3_TX_WR0   0x4324
#define REG_S3_TX_WR1   0x4325
#define REG_S3_RX_RSR0  0x4326
#define REG_S3_RX_RSR1  0x4327
#define REG_S3_RX_RD0   0x4328
#define REG_S3_RX_RD1   0x4329

#define S0_TX_START 0x8000
#define S0_TX_END   0x8800
#define S1_TX_START 0x8800
#define S1_TX_END   0x9000
#define S2_TX_START 0x9000
#define S2_TX_END   0x9800
#define S3_TX_START 0x9800
#define S3_TX_END   0xA000
#define S0_RX_START 0xC000
#define S0_RX_END   0xC800
#define S1_RX_START 0xC800
#define S1_RX_END   0xD000
#define S2_RX_START 0xD000
#define S2_RX_END   0xD800
#define S3_RX_START 0xD800
#define S3_RX_END   0xE000

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



