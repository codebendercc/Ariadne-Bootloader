#ifndef util_h
#define util_h

#define TIMEOUT 4

#ifndef LED_START_FLASHES
	#define LED_START_FLASHES 0
#endif

#define TRUE  1
#define FALSE 0

#define MAKESTR(a) #a
#define MAKEVER(a, b) MAKESTR(a*256+b)

/* FIXME: For some reason avr-gcc 4.7.1 decides that a ".word" has size of 4
 * and a ".byte" has size of 2 registers. For now this will stay like this
 * and change the -Wl,--section-start=.version=0x7ffe in the Makefile to 7ffc */
// asm("  .section .version\n"
//     "tftpboot_version: .word " MAKEVER(TFTPBOOT_MAJVER, TFTPBOOT_MINVER) "\n"
//     "  .section .text\n");

/*
 * use 16bit address variable for ATmegas with <= 64K flash
 */
#if defined(RAMPZ)
	typedef uint32_t address_t;
#else
	typedef uint16_t address_t;
#endif

#if (FLASHEND > 0x10000)
	#if defined(__AVR_ATmega2560__)
		#define PROGMEM_OFFSET 0x30000
	#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega1284P__)
		#define PROGMEM_OFFSET 0x10000
	#else
		#error "Unknown MCU. Cannot define PROGMEM_OFFSET"
	#endif
#endif

void updateLed(void);
void resetTick(void);
uint8_t timedOut(void);

#endif
