#ifndef spi_h
#define spi_h

/** Pin definitions for SPI and leds */
/** Uno and Deumilanove */
#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
	/** SPI port and pins */
	#define SPI_DDR		DDRB
	#define SPI_PORT	PORTB

	#define SCK     PINB5  //Pin 13
	#define MISO    PINB4  //Pin 12
	#define MOSI    PINB3  //Pin 11
	#define SS      PINB2  //Pin 10

	/** Ethernet Shield SS pin */
	#define ETH_DDR		DDRB
	#define ETH_PORT	PORTB
	#define ETH_SS		PINB2  //Pin 10

	/** SD card SS pin */
	#define SD_DDR	DDRD
	#define SD_PORT	PORTD
	#define SD_SS	PIND4  //Pin 04

	/** Onboard LED is connected to pin PB5 in Duemilanove and Uno or to PB1 in Ethernet */
	#define LED_DDR		DDRB
	#define LED_PORT	PORTB
	#if defined(ARDUINO_ETHERNET)
		#define LED     PINB1  //Pin 9
	#else
		#define LED     PINB5  //Pin 13
	#endif

/** Mega1280 and Mega2560 */
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	/** SPI port and pins */
	#define SPI_DDR		DDRB
	#define SPI_PORT	PORTB
	#define SCK		PINB1  //Pin 52
	#define MISO	PINB3  //Pin 50
	#define MOSI	PINB2  //Pin 51
	#define SS      PINB0  //Pin 53

	/** Ethernet Shield SS pin */
	#define ETH_DDR		DDRB
	#define ETH_PORT	PORTB
	#define ETH_SS		PINB4  //Pin 10

	/** SD card SS pin */
	#define SD_DDR	DDRG
	#define SD_PORT	PORTG
	#define SD_SS	PING5  //Pin 04

	/** Onboard LED is connected to pin PB7 on Arduino Mega */
	#define LED_DDR     DDRB
	#define LED_PORT    PORTB
	#define LED         PINB7

/** Leonardo */
#elif defined(__AVR_ATmega32U4__)
	#error "Leonardo not supported yet"
#else
	#error "No pin definitions for MCU available"
#endif

#define SPI_WRITE (0xF0)
#define SPI_READ  (0x0F)

#define SS_LOW()	ETH_PORT &= ~_BV(ETH_SS)
#define SS_HIGH()	ETH_PORT |= _BV(ETH_SS)

void spiInit(void);

void spiWriteReg(uint16_t address, uint8_t value);
void spiWriteWord(uint16_t address, uint16_t value);

uint8_t  spiReadReg(uint16_t address);
uint16_t spiReadWord(uint16_t address);

#endif
