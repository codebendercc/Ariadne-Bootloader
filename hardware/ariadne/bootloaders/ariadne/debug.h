#ifndef debug_h
#define debug_h

/*
 * Define DBG_* dummy macros. These disable the debugging code if they aren't
 * overriden later on in the subsytem sections.
 */
#define DBG_MAIN(block)
#define DBG_MAIN_EX(block)
#define DBG_NET(block)
#define DBG_NET_EX(block)
#define DBG_SPI(block)
#define DBG_SPI_EX(block)
#define DBG_TFTP(block)
#define DBG_TFTP_EX(block)
#define DBG_VALD(block)
#define DBG_UTIL(block)
#define DBG_BTN(block)
#define DBG_ANN(block)

#if (DEBUG_ALL > 1)
	#define DEBUG_MAIN	2
	#define DEBUG_SPI	2
	#define DEBUG_NET	2
	#define DEBUG_TFTP	2
	#define DEBUG_VALD	2
	#define DEBUG_UTIL	2
	#define DEBUG_ANN	2
#elif (DEBUG_ALL > 0)
	#define DEBUG_MAIN	1
	#define DEBUG_SPI	1
	#define DEBUG_NET	1
	#define DEBUG_TFTP	1
	#define DEBUG_VALD	1
	#define DEBUG_UTIL	1
	#define DEBUG_ANN	1
#endif

#if (DEBUG_MAIN > 0) || (DEBUG_NET > 0) || (DEBUG_TFTP > 0)	|| (DEBUG_VALD > 0) ||\
	(DEBUG_UTIL > 0) || (DEBUG_ANN > 0) || (DEBUG_BTN > 0)  || (DEBUG_SPI > 0)
	#define ENABLE_DEBUG
#endif

#if defined(ENABLE_DEBUG)

void tracePGM(const void* p_msg);
void tracePGMln(const void* p_prefix, const void* p_msg);
void tracehex(uint32_t num, uint8_t len);
void trace(char* msg);
void traceln(const void* p_prefix, char* msg);

#define traceadd(num) tracehex(num, 6)
#define tracenum(num) tracehex(num, 4)
#define tracenet(num) tracehex(num, 2)

#if defined(DEBUG_BTN)
void buttonInit(void);
void button(void);
#endif

#endif

#endif
