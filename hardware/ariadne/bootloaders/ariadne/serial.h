#ifndef serial_h
#define serial_h

/*
 * define CPU frequency in Mhz here if not defined in Makefile
 */
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

/*
 * UART Baudrate, AVRStudio AVRISP only accepts 115200 bps
 */
#ifndef BAUDRATE
	#define BAUDRATE 115200
#endif

/*
 *  Enable (1) or disable (0) USART double speed operation
 */
#ifndef UART_BAUDRATE_DOUBLE_SPEED
	#if defined (__AVR_ATmega32__)
		#define UART_BAUDRATE_DOUBLE_SPEED 0
	#else
		#define UART_BAUDRATE_DOUBLE_SPEED 1
	#endif
#endif

/*
 * Macro to calculate UBBR from XTAL and baudrate
 */
#if defined(__AVR_ATmega32__) && UART_BAUDRATE_DOUBLE_SPEED
	#define UART_BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu / 4 / baudRate - 1) / 2)
#elif defined(__AVR_ATmega32__)
	#define UART_BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu / 8 / baudRate - 1) / 2)
#elif UART_BAUDRATE_DOUBLE_SPEED
	#define UART_BAUD_SELECT(baudRate,xtalCpu) (((float)(xtalCpu))/(((float)(baudRate))*8.0)-1.0+0.5)
#else
	#define UART_BAUD_SELECT(baudRate,xtalCpu) (((float)(xtalCpu))/(((float)(baudRate))*16.0)-1.0+0.5)
#endif


/* set the UART baud rate defaults */
#ifndef BAUD_RATE
	#if F_CPU >= 8000000L
		#define BAUD_RATE	115200L // Highest rate Avrdude win32 will support
	#elif F_CPU >= 1000000L
		#define BAUD_RATE	9600L   // 19200 also supported, but with significant error
	#elif F_CPU >= 128000L
		#define BAUD_RATE	4800L   // Good for 128kHz internal RC
	#else
		#define BAUD_RATE	1200L     // Good even at 32768Hz
	#endif
#endif

/* Switch in soft UART for hard baud rates */
#if (F_CPU/BAUD_RATE) > 280 // > 57600 for 16MHz
	#ifndef SOFT_UART
		#define SOFT_UART
	#endif
#endif

/* USART definitions */
#if defined(_BOARD_ROBOTX_) || defined(__AVR_AT90USB1287__) || defined(__AVR_AT90USB1286__)
	#define	UART_BAUD_RATE_LOW			UBRR1L
	#define	UART_STATUS_REG				UCSR1A
	#define	UART_CONTROL_REG			UCSR1B
	#define	UART_ENABLE_TRANSMITTER		TXEN1
	#define	UART_ENABLE_RECEIVER		RXEN1
	#define	UART_TRANSMIT_COMPLETE		TXC1
	#define	UART_RECEIVE_COMPLETE		RXC1
	#define	UART_DATA_REG				UDR1
	#define	UART_DOUBLE_SPEED			U2X1

#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__)
/* ATMega8 with one USART */
	#define	UART_BAUD_RATE_LOW			UBRRL
	#define	UART_STATUS_REG				UCSRA
	#define	UART_CONTROL_REG			UCSRB
	#define	UART_ENABLE_TRANSMITTER		TXEN
	#define	UART_ENABLE_RECEIVER		RXEN
	#define	UART_TRANSMIT_COMPLETE		TXC
	#define	UART_RECEIVE_COMPLETE		RXC
	#define	UART_DATA_REG				UDR
	#define	UART_DOUBLE_SPEED			U2X

#elif defined(__AVR_ATmega64__) || defined(__AVR_ATmega128__) || defined(__AVR_ATmega162__) \
|| defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) \
|| defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__) || defined(__AVR_ATmega1284P__)
/* ATMega with two USART, use UART0 */
	#define	UART_BAUD_RATE_LOW			UBRR0L
	#define	UART_STATUS_REG				UCSR0A
	#define	UART_CONTROL_REG			UCSR0B
	#define UART_MODE_REG               UCSR0C
	#define	UART_ENABLE_TRANSMITTER		TXEN0
	#define	UART_ENABLE_RECEIVER		RXEN0
	#define UART_CHAR_SIZE_LOW          UCSZ00
	#define UART_CHAR_SIZE_MID          UCSZ01
	#define	UART_TRANSMIT_COMPLETE		TXC0
	#define	UART_RECEIVE_COMPLETE		RXC0
	#define	UART_DATA_REG				UDR0
	#define UART_DATA_REG_EMPTY         UDRE0
	#define	UART_DOUBLE_SPEED			U2X0
	#define UART_FRAME_ERROR            FE0

#elif defined(UBRR0L) && defined(UCSR0A) && defined(TXEN0)
/* ATMega with two USART, use UART0 */
	#define	UART_BAUD_RATE_LOW			UBRR0L
	#define	UART_STATUS_REG				UCSR0A
	#define	UART_CONTROL_REG			UCSR0B
	#define	UART_ENABLE_TRANSMITTER		TXEN0
	#define	UART_ENABLE_RECEIVER		RXEN0
	#define	UART_TRANSMIT_COMPLETE		TXC0
	#define	UART_RECEIVE_COMPLETE		RXC0
	#define	UART_DATA_REG				UDR0
	#define	UART_DOUBLE_SPEED			U2X0

#elif defined(UBRRL) && defined(UCSRA) && defined(UCSRB) && defined(TXEN) && defined(RXEN)
//* catch all
	#define	UART_BAUD_RATE_LOW			UBRRL
	#define	UART_STATUS_REG				UCSRA
	#define	UART_CONTROL_REG			UCSRB
	#define	UART_ENABLE_TRANSMITTER		TXEN
	#define	UART_ENABLE_RECEIVER		RXEN
	#define	UART_TRANSMIT_COMPLETE		TXC
	#define	UART_RECEIVE_COMPLETE		RXC
	#define	UART_DATA_REG				UDR
	#define	UART_DOUBLE_SPEED			U2X

#else
	#error "no UART definition for MCU available"

#endif

/* Serial status flag, it is set to TRUE if flashing from
 * serial is currently active */
uint8_t serialFlashing;

/*
 * Function definitions
 */
void serialInit(void);

void putch(uint8_t c);
void puthex(uint8_t c);

uint8_t getch(void);

uint8_t serialPoll(void);
#endif
