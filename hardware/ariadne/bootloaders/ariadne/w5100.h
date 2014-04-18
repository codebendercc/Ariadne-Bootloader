#ifndef w5100_h
#define w5100_h

//Mode
#define REG_MR          0x000
//GW Address
#define REG_GAR0        0x001
#define REG_GAR1        0x002
#define REG_GAR2        0x003
#define REG_GAR3        0x004
//Mask
#define REG_SUBR0       0x005
#define REG_SUBR1       0x006
#define REG_SUBR2       0x007
#define REG_SUBR3       0x008
//Mac Address (Source Hardware Address)
#define REG_SHAR0       0x009
#define REG_SHAR1       0x00A
#define REG_SHAR2       0x00B
#define REG_SHAR3       0x00C
#define REG_SHAR4       0x00D
#define REG_SHAR5       0x00E
//IP Address (Source IP Address)
#define REG_SIPR0       0x00F
#define REG_SIPR1       0x010
#define REG_SIPR2       0x011
#define REG_SIPR3       0x012
//Interrupt
#define REG_IR          0x015
//Interrupt Mask
#define REG_IMR         0x016
//Retry Time
#define REG_RTR0        0x017
#define REG_RTR1        0x018
//Retry Count
#define REG_RCR         0x019
//RX Memory Size
#define REG_RMSR        0x01A
//TX Memory Size
#define REG_TMSR        0x01B
//PPPoE Auth
#define REG_PATR0       0x01C
#define REG_PATR1       0x01D
//PPP LCP Request Timer
#define REG_PTIMER      0x028
//PPP LCP Magic Number
#define REG_PMAGIC      0x029
//Unreachable IP Address
#define REG_UIPR0       0x02A
#define REG_UIPR1       0x02B
#define REG_UIPR2       0x02C
#define REG_UIPR3       0x02D
//Unreachable Port
#define REG_UPORT0      0x02E
#define REG_UPORT1      0x02F
/**
 * Socket 0 addresses */
//Mode
#define REG_S0_MR       0x400
//Command
#define REG_S0_CR       0x401
//Interrupt
#define REG_S0_IR       0x402
//Status
#define REG_S0_SR       0x403
//Source Port
#define REG_S0_PORT0    0x404
#define REG_S0_PORT1    0x405
//Destination Hardware Address
#define REG_S0_DHAR0    0x406
#define REG_S0_DHAR1    0x407
#define REG_S0_DHAR2    0x408
#define REG_S0_DHAR3    0x409
#define REG_S0_DHAR4    0x40A
#define REG_S0_DHAR5    0x40B
//Destination IP Address
#define REG_S0_DIPR0    0x40C
#define REG_S0_DIPR1    0x40D
#define REG_S0_DIPR2    0x40E
#define REG_S0_DIPR3    0x40F
//Destination Port
#define REG_S0_DPORT0   0x410
#define REG_S0_DPORT1   0x411
//Maximum Segment Size
#define REG_S0_MSSR0    0x412
#define REG_S0_MSSR1    0x413
//Protocol in Raw Mode
#define REG_S0_PROTO    0x414
//TOS
#define REG_S0_TOS      0x415
//TTL
#define REG_S0_TTL      0x416
//TX Free Size
#define REG_S0_TX_FSR0  0x420
#define REG_S0_TX_FSR1  0x421
//TX Read Pointer
#define REG_S0_TX_RD0   0x422
#define REG_S0_TX_RD1   0x423
//TX Write Pointer
#define REG_S0_TX_WR0   0x424
#define REG_S0_TX_WR1   0x425
//RX Received Size
#define REG_S0_RX_RSR0  0x426
#define REG_S0_RX_RSR1  0x427
//RX Read Pointer
#define REG_S0_RX_RD0   0x428
#define REG_S0_RX_RD1   0x429
/**
 * Socket 1 addresses */
#define REG_S1_MR       0x500
#define REG_S1_CR       0x501
#define REG_S1_IR       0x502
#define REG_S1_SR       0x503
#define REG_S1_PORT0    0x504
#define REG_S1_PORT1    0x505
#define REG_S1_DHAR0    0x506
#define REG_S1_DHAR1    0x507
#define REG_S1_DHAR2    0x508
#define REG_S1_DHAR3    0x509
#define REG_S1_DHAR4    0x50A
#define REG_S1_DHAR5    0x50B
#define REG_S1_DIPR0    0x50C
#define REG_S1_DIPR1    0x50D
#define REG_S1_DIPR2    0x50E
#define REG_S1_DIPR3    0x50F
#define REG_S1_DPORT0   0x510
#define REG_S1_DPORT1   0x511
#define REG_S1_MSSR0    0x512
#define REG_S1_MSSR1    0x513
#define REG_S1_PROTO    0x514
#define REG_S1_TOS      0x515
#define REG_S1_TTL      0x516
#define REG_S1_TX_FSR0  0x520
#define REG_S1_TX_FSR1  0x521
#define REG_S1_TX_RD0   0x522
#define REG_S1_TX_RD1   0x523
#define REG_S1_TX_WR0   0x524
#define REG_S1_TX_WR1   0x525
#define REG_S1_RX_RSR0  0x526
#define REG_S1_RX_RSR1  0x527
#define REG_S1_RX_RD0   0x528
#define REG_S1_RX_RD1   0x529
/**
 * Socket 2 addresses */
#define REG_S2_MR       0x600
#define REG_S2_CR       0x601
#define REG_S2_IR       0x602
#define REG_S2_SR       0x603
#define REG_S2_PORT0    0x604
#define REG_S2_PORT1    0x605
#define REG_S2_DHAR0    0x606
#define REG_S2_DHAR1    0x607
#define REG_S2_DHAR2    0x608
#define REG_S2_DHAR3    0x609
#define REG_S2_DHAR4    0x60A
#define REG_S2_DHAR5    0x60B
#define REG_S2_DIPR0    0x60C
#define REG_S2_DIPR1    0x60D
#define REG_S2_DIPR2    0x60E
#define REG_S2_DIPR3    0x60F
#define REG_S2_DPORT0   0x610
#define REG_S2_DPORT1   0x611
#define REG_S2_MSSR0    0x612
#define REG_S2_MSSR1    0x613
#define REG_S2_PROTO    0x614
#define REG_S2_TOS      0x615
#define REG_S2_TTL      0x616
#define REG_S2_TX_FSR0  0x620
#define REG_S2_TX_FSR1  0x621
#define REG_S2_TX_RD0   0x622
#define REG_S2_TX_RD1   0x623
#define REG_S2_TX_WR0   0x624
#define REG_S2_TX_WR1   0x625
#define REG_S2_RX_RSR0  0x626
#define REG_S2_RX_RSR1  0x627
#define REG_S2_RX_RD0   0x628
#define REG_S2_RX_RD1   0x629
/**
 * Socket 3 addresses */
#define REG_S3_MR       0x700
#define REG_S3_CR       0x701
#define REG_S3_IR       0x702
#define REG_S3_SR       0x703
#define REG_S3_PORT0    0x704
#define REG_S3_PORT1    0x705
#define REG_S3_DHAR0    0x706
#define REG_S3_DHAR1    0x707
#define REG_S3_DHAR2    0x708
#define REG_S3_DHAR3    0x709
#define REG_S3_DHAR4    0x70A
#define REG_S3_DHAR5    0x70B
#define REG_S3_DIPR0    0x70C
#define REG_S3_DIPR1    0x70D
#define REG_S3_DIPR2    0x70E
#define REG_S3_DIPR3    0x70F
#define REG_S3_DPORT0   0x710
#define REG_S3_DPORT1   0x711
#define REG_S3_MSSR0    0x712
#define REG_S3_MSSR1    0x713
#define REG_S3_PROTO    0x714
#define REG_S3_TOS      0x715
#define REG_S3_TTL      0x716
#define REG_S3_TX_FSR0  0x720
#define REG_S3_TX_FSR1  0x721
#define REG_S3_TX_RD0   0x722
#define REG_S3_TX_RD1   0x723
#define REG_S3_TX_WR0   0x724
#define REG_S3_TX_WR1   0x725
#define REG_S3_RX_RSR0  0x726
#define REG_S3_RX_RSR1  0x727
#define REG_S3_RX_RD0   0x728
#define REG_S3_RX_RD1   0x729

#define S0_TX_START 0x4000
#define S0_TX_END   0x4800
#define S1_TX_START 0x4800
#define S1_TX_END   0x5000
#define S2_TX_START 0x5000
#define S2_TX_END   0x5800
#define S3_TX_START 0x5800
#define S3_TX_END   0x6000
#define S0_RX_START 0x6000
#define S0_RX_END   0x6800
#define S1_RX_START 0x6800
#define S1_RX_END   0x7000
#define S2_RX_START 0x7000
#define S2_RX_END   0x7800
#define S3_RX_START 0x7800
#define S3_RX_END   0x8000

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
#define SOCK_ARP1         0x11
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
#define SOCK_ARP2         0x21
#define SOCK_UDP          0x22
#define SOCK_ARP3         0x31
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
#define IR_CLR       0x00


/* Network settings */
#define IP_ADDR     192,168,1,128
#define SUB_MASK    255,255,255,0
#define GW_ADDR     192,168,1,254
#define MAC_ADDR    0xDE,0xAD,0xBE,0xEF,0xFE,0xED

void netInit(void);

#endif
