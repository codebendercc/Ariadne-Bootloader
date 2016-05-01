# Name: Makefile
# Author: Stelios Tsampas, from work by optiboot
# Copyright: optiboot
# License: GPL http://www.gnu.org/licenses/gpl-2.0.html
# Project: ariadne bootloader
# Function: tftp implementation and flasher
# Version: 0.2 tftp flashing functional, serial flashing

# Instructions
#
# To make bootloader .hex file:
# make diecimila
# make lilypad
# make ng
# etc...
#
# To burn bootloader .hex file:
# make diecimila_isp
# make lilypad_isp
# make ng_isp
# etc...

# program name should not be changed...
PROGRAM    = ariadne

# The default behavior is to build using tools that are in the users
# current path variables, but we can also build using an installed
# Arduino user IDE setup, or the Arduino source tree.
# Uncomment this next lines to build within the arduino environment,
# using the arduino-included avrgcc toolset (mac and pc)
# ENV ?= arduino
# ENV ?= arduinodev
# OS ?= macosx
# OS ?= windows

# enter the parameters for the avrdude isp tool
# for now they default to the arduinoISP on linux
ISPTOOL    = avrispmkii
#ISPTOOL   = usbtiny
ISPPORT	   = usb
ISPSPEED   = -b38400

MCU_TARGET = atmega328p
LDSECTIONS = -Wl,--section-start=.text=0x7000 #-Wl,--section-start=.version=0x7ffe

# Build environments
# Start of some ugly makefile-isms to allow optiboot to be built
# in several different environments.  See the README.TXT file for
# details.

# default
fixpath = $(1)

ifeq ($(ENV), arduino)
# For Arduino, we assume that we're connected to the optiboot directory
# included with the arduino distribution, which means that the full set
# of avr-tools are "right up there" in standard places.
TOOLROOT = ../../../tools
GCCROOT = $(TOOLROOT)/avr/bin/
AVRDUDE_CONF = -C$(TOOLROOT)/avr/etc/avrdude.conf

ifeq ($(OS), windows)
# On windows, SOME of the tool paths will need to have backslashes instead
# of forward slashes (because they use windows cmd.exe for execution instead
# of a unix/mingw shell?)  We also have to ensure that a consistent shell
# is used even if a unix shell is installed (ie as part of WINAVR)
fixpath = $(subst /,\,$1)
SHELL = cmd.exe
endif

else ifeq ($(ENV), arduinodev)
# Arduino IDE source code environment.  Use the unpacked compilers created
# by the build (you'll need to do "ant build" first.)
ifeq ($(OS), macosx)
TOOLROOT = ../../../../build/macosx/work/Arduino.app/Contents/Resources/Java/hardware/tools
endif
ifeq ($(OS), windows)
TOOLROOT = ../../../../build/windows/work/hardware/tools
endif

GCCROOT = $(TOOLROOT)/avr/bin/
AVRDUDE_CONF = -C$(TOOLROOT)/avr/etc/avrdude.conf

else
GCCROOT =
AVRDUDE_CONF =
endif
#
# End of build environment code.


# the efuse should really be 0xf8; since, however, only the lower
# three bits of that byte are used on the atmega168, avrdude gets
# confused if you specify 1's for the higher bits, see:
# http://tinker.it/now/2007/02/24/the-tale-of-avrdude-atmega168-and-extended-bits-fuses/
#
# similarly, the lock bits should be 0xff instead of 0x3f (to
# unlock the bootloader section) and 0xcf instead of 0x2f (to
# lock it), but since the high two bits of the lock byte are
# unused, avrdude would get confused.

ISPFUSES = $(GCCROOT)avrdude $(AVRDUDE_CONF) -c $(ISPTOOL) \
           -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
           -e -u -U lock:w:0x3F:m -U efuse:w:0x$(EFUSE):m \
           -U hfuse:w:0x$(HFUSE):m -U lfuse:w:0x$(LFUSE):m
ISPFLASH = $(GCCROOT)avrdude $(AVRDUDE_CONF) -c $(ISPTOOL) \
           -p $(MCU_TARGET) -P $(ISPPORT) $(ISPSPEED) \
           -U flash:w:$(PROGRAM)_$(TARGET).hex -U lock:w:0x0F:m

STK500   = "C:\Program Files\Atmel\AVR Tools\STK500\Stk500.exe"
STK500-1 = $(STK500) -e -d$(MCU_TARGET) -pf -vf -if$(PROGRAM)_$(TARGET).hex \
	   -lFF -LFF -f$(HFUSE)$(LFUSE) -EF8 -ms -q -cUSB -I200kHz -s -wt
STK500-2 = $(STK500) -d$(MCU_TARGET) -ms -q -lCF -LCF -cUSB -I200kHz -s -wt

OBJ      = main.o spi.o w5100.o tftp.o validate.o debug.o watchdog.o serial.o util.o announce.o optiboot.o stk500boot.o
OPTIMIZE = -Os -fno-inline-small-functions -fno-split-wide-types -mno-interrupts -mrelax
OPTIMIZE += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -fno-jump-tables -std=gnu99 #-save-temps

DEFS     =
LIBS     =

CC       = $(GCCROOT)avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS  = -g -Wall -Wextra -Wstrict-prototypes $(OPTIMIZE) -mmcu=$(MCU_TARGET) -DF_CPU=$(AVR_FREQ) $(DEFS)
override LDFLAGS = $(LDSECTIONS) -Wl,--relax -Wl,--gc-sections

OBJCOPY = $(GCCROOT)avr-objcopy
OBJDUMP = $(call fixpath,$(GCCROOT)avr-objdump)

SIZE    = $(GCCROOT)avr-size


# Build with the debug messages enabled
# Use it only if you have already seen the source code
debug328_w5100: TARGET = debug328_w5100
debug328_w5100: MCU_TARGET = atmega328p
debug328_w5100: CFLAGS += '-DDEBUG_MAIN=1' '-DDEBUG_NET=1' '-DDEBUG_TFTP=1' '-DBAUD_RATE=115200'
debug328_w5100: AVR_FREQ = 16000000L
debug328_w5100: LDSECTIONS = -Wl,--section-start=.text=0x7000 #-Wl,--section-start=.version=0x7ffe
debug328_w5100: $(PROGRAM)_debug328_w5100.hex
debug328_w5100: $(PROGRAM)_debug328_w5100.lst
debug328_isp_w5100: debug328_w5100
debug328_isp_w5100: TARGET = debug328_w5100
debug328_isp_w5100: MCU_TARGET = atmega328p
# Low power xtal (16MHz) 16KCK/14CK+65ms
debug328_isp_w5100: LFUSE = FF
# 4096 byte boot, SPIEN
debug328_isp_w5100: HFUSE = D0
# 2.7V brownout
debug328_isp_w5100: EFUSE = 05
debug328_isp_w5100: isp

# Build with the debug messages enabled
# Use it only if you have already seen the source code
debug328_w5200: TARGET = debug328_w5200
debug328_w5200: MCU_TARGET = atmega328p
debug328_w5200: CFLAGS += '-DW5200=1' '-DDEBUG_MAIN=1' '-DDEBUG_NET=1' '-DDEBUG_TFTP=1' '-DBAUD_RATE=115200'
debug328_w5200: AVR_FREQ = 16000000L
debug328_w5200: LDSECTIONS = -Wl,--section-start=.text=0x7000 #-Wl,--section-start=.version=0x7ffe
debug328_w5200: $(PROGRAM)_debug328_w5200.hex
debug328_w5200: $(PROGRAM)_debug328_w5200.lst
debug328_isp_w5200: debug328_w5200
debug328_isp_w5200: TARGET = debug328_w5200
debug328_isp_w5200: MCU_TARGET = atmega328p
# Low power xtal (16MHz) 16KCK/14CK+65ms
debug328_isp_w5200: LFUSE = FF
# 4096 byte boot, SPIEN
debug328_isp_w5200: HFUSE = D0
# 2.7V brownout
debug328_isp_w5200: EFUSE = 05
debug328_isp_w5200: isp

# Build with the debug messages enabled
# Use it only if you have already seen the source code
debug328_w5500: TARGET = debug328_w5500
debug328_w5500: MCU_TARGET = atmega328p
debug328_w5500: CFLAGS += '-DW5500=1' '-DDEBUG_MAIN=1' '-DDEBUG_NET=1' '-DDEBUG_TFTP=1' '-DBAUD_RATE=115200'
debug328_w5500: AVR_FREQ = 16000000L
debug328_w5500: LDSECTIONS = -Wl,--section-start=.text=0x7000 #-Wl,--section-start=.version=0x7ffe
debug328_w5500: $(PROGRAM)_debug328_w5500.hex
debug328_w5500: $(PROGRAM)_debug328_w5500.lst
debug328_isp_w5500: debug328_w5500
debug328_isp_w5500: TARGET = debug328_w5500
debug328_isp_w5500: MCU_TARGET = atmega328p
# Low power xtal (16MHz) 16KCK/14CK+65ms
debug328_isp_w5500: LFUSE = FF
# 4096 byte boot, SPIEN
debug328_isp_w5500: HFUSE = D0
# 2.7V brownout
debug328_isp_w5500: EFUSE = 05
debug328_isp_w5500: isp

# Debug build for Arduino Mega2560
debug2560_w5100: TARGET = debug2560_w5100
debug2560_w5100: MCU_TARGET = atmega2560
debug2560_w5100: CFLAGS += '-DDEBUG_MAIN=1' '-DDEBUG_NET=1' '-DDEBUG_TFTP=1' '-DDEBUG_VALD=1' '-DBAUD_RATE=115200'
debug2560_w5100: AVR_FREQ = 16000000L
debug2560_w5100: LDSECTIONS  = -Wl,--section-start=.text=0x3e000
debug2560_w5100: $(PROGRAM)_debug2560_w5100.hex
debug2560_w5100: $(PROGRAM)_debug2560_w5100.lst
debug2560_isp_w5100: debug2560_w5100
debug2560_isp_w5100: TARGET = debug2560_w5100
debug2560_isp_w5100: MCU_TARGET = atmega2560
# Low power xtal (16MHz) 16KCK/14CK+65ms
debug2560_isp_w5100: LFUSE = FF
# 4069 byte boot
debug2560_isp_w5100: HFUSE = D0
# 2.7V brownout
debug2560_isp_w5100: EFUSE = FD
debug2560_isp_w5100: isp

# Debug build for Arduino Mega2560
debug2560_w5200: TARGET = debug2560_w5200
debug2560_w5200: MCU_TARGET = atmega2560
debug2560_w5200: CFLAGS += '-DW5200=1' '-DDEBUG_MAIN=1' '-DDEBUG_NET=1' '-DDEBUG_TFTP=1' '-DDEBUG_VALD=1' '-DBAUD_RATE=115200'
debug2560_w5200: AVR_FREQ = 16000000L
debug2560_w5200: LDSECTIONS  = -Wl,--section-start=.text=0x3e000
debug2560_w5200: $(PROGRAM)_debug2560_w5200.hex
debug2560_w5200: $(PROGRAM)_debug2560_w5200.lst
debug2560_isp_w5200: debug2560_w5200
debug2560_isp_w5200: TARGET = debug2560_w5200
debug2560_isp_w5200: MCU_TARGET = atmega2560
# Low power xtal (16MHz) 16KCK/14CK+65ms
debug2560_isp_w5200: LFUSE = FF
# 4069 byte boot
debug2560_isp_w5200: HFUSE = D0
# 2.7V brownout
debug2560_isp_w5200: EFUSE = FD
debug2560_isp_w5200: isp

# Debug build for Arduino Mega2560
debug2560_w5500: TARGET = debug2560_w5500
debug2560_w5500: MCU_TARGET = atmega2560
debug2560_w5500: CFLAGS += '-DW5500=1' '-DDEBUG_MAIN=1' '-DDEBUG_NET=1' '-DDEBUG_TFTP=1' '-DDEBUG_VALD=1' '-DBAUD_RATE=115200'
debug2560_w5500: AVR_FREQ = 16000000L
debug2560_w5500: LDSECTIONS  = -Wl,--section-start=.text=0x3e000
debug2560_w5500: $(PROGRAM)_debug2560_w5500.hex
debug2560_w5500: $(PROGRAM)_debug2560_w5500.lst
debug2560_isp_w5500: debug2560_w5500
debug2560_isp_w5500: TARGET = debug2560_w5500
debug2560_isp_w5500: MCU_TARGET = atmega2560
# Low power xtal (16MHz) 16KCK/14CK+65ms
debug2560_isp_w5500: LFUSE = FF
# 4069 byte boot
debug2560_isp_w5500: HFUSE = D0
# 2.7V brownout
debug2560_isp_w5500: EFUSE = FD
debug2560_isp_w5500: isp

# Debug build for Atmega1284
debug1284_w5100: TARGET = debug1284_w5100
debug1284_w5100: MCU_TARGET = atmega1284p
debug1284_w5100: CFLAGS += '-DBAUD_RATE=115200'
debug1284_w5100: AVR_FREQ = 16000000L
debug1284_w5100: LDSECTIONS  = -Wl,--section-start=.text=0x1f000
debug1284_w5100: $(PROGRAM)_debug1284_w5100.hex
debug1284_w5100: $(PROGRAM)_debug1284_w5100.lst

debug1284_w5100_isp: debug1284_w5100
debug1284_w5100_isp: TARGET = debug1284_w5100
debug1284_w5100_isp: MCU_TARGET = atmega1284p
# 4096 word boot
debug1284_w5100_isp: HFUSE = D8
# External power xtal (16MHz) 16KCK/14CK+65ms
debug1284_w5100_isp: LFUSE = FF
# 2.7V brownout
debug1284_w5100_isp: EFUSE = FD
debug1284_w5100_isp: isp

# Debug build for Atmega1284
debug1284_w5200: TARGET = debug1284_w5200
debug1284_w5200: MCU_TARGET = atmega1284p
debug1284_w5200: CFLAGS += '-DW5200=1' '-DDEBUG_MAIN=1' '-DDEBUG_NET=1' '-DDEBUG_TFTP=1' '-DDEBUG_VALD=1' '-DBAUD_RATE=115200'
debug1284_w5200: AVR_FREQ = 16000000L
debug1284_w5200: LDSECTIONS  = -Wl,--section-start=.text=0x1f000
debug1284_w5200: $(PROGRAM)_debug1284_w5200.hex
debug1284_w5200: $(PROGRAM)_debug1284_w5200.lst

debug1284_w5200_isp: debug1284_w5200
debug1284_w5200_isp: TARGET = debug1284_w5200
debug1284_w5200_isp: MCU_TARGET = atmega1284p
# 4096 word boot
debug1284_w5200_isp: HFUSE = D8
# External power xtal (16MHz) 16KCK/14CK+65ms
debug1284_w5200_isp: LFUSE = FF
# 2.7V brownout
debug1284_w5200_isp: EFUSE = FD
debug1284_w5200_isp: isp

# Debug build for Atmega1284
debug1284_w5500: TARGET = debug1284_w5500
debug1284_w5500: MCU_TARGET = atmega1284p
debug1284_w5500: CFLAGS += '-DW5500=1' '-DDEBUG_MAIN=1' '-DDEBUG_NET=1' '-DDEBUG_TFTP=1' '-DDEBUG_VALD=1' '-DBAUD_RATE=115200'
debug1284_w5500: AVR_FREQ = 16000000L
debug1284_w5500: LDSECTIONS  = -Wl,--section-start=.text=0x1f000
debug1284_w5500: $(PROGRAM)_debug1284_w5500.hex
debug1284_w5500: $(PROGRAM)_debug1284_w5500.lst

debug1284_w5500_isp: debug1284_w5500
debug1284_w5500_isp: TARGET = debug1284_w5500
debug1284_w5500_isp: MCU_TARGET = atmega1284p
# 4096 word boot
debug1284_w5500_isp: HFUSE = D8
# External power xtal (16MHz) 16KCK/14CK+65ms
debug1284_w5500_isp: LFUSE = FF
# 2.7V brownout
debug1284_w5500_isp: EFUSE = FD
debug1284_w5500_isp: isp

# Build with the debug messages enabled
# Use it only if you have already seen the source code
debug32u4: TARGET = debug32u4
debug32u4: MCU_TARGET = atmega32u4
debug32u4: CFLAGS += '-DDEBUG_MAIN=1' '-DDEBUG_NET=1' '-DDEBUG_TFTP=1' '-DBAUD_RATE=115200'
debug32u4: AVR_FREQ = 16000000L
debug32u4: LDSECTIONS = -Wl,--section-start=.text=0x7000 #-Wl,--section-start=.version=0x7ffe
debug32u4: $(PROGRAM)_debug32u4.hex
debug32u4: $(PROGRAM)_debug32u4.lst

#
#
# # 20MHz clocked platforms
# # These are capable of 230400 baud, or 115200 baud on PC (Arduino Avrdude issue)
# pro20: TARGET = pro_20mhz
# pro20: MCU_TARGET = atmega168
# pro20: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
# pro20: AVR_FREQ = 20000000L
# pro20: $(PROGRAM)_pro_20mhz.hex
# pro20: $(PROGRAM)_pro_20mhz.lst
# pro20_isp: pro20
# pro20_isp: TARGET = pro_20mhz
# # 2.7V brownout
# pro20_isp: HFUSE = DD
# # Full swing xtal (20MHz) 258CK/14CK+4.1ms
# pro20_isp: LFUSE = C6
# # 512 byte boot
# pro20_isp: EFUSE = 04
# pro20_isp: isp
#
#
# # 16MHz clocked platforms
# # These are capable of 230400 baud, or 115200 baud on PC (Arduino Avrdude issue)
# pro16: TARGET = pro_16MHz
# pro16: MCU_TARGET = atmega168
# pro16: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
# pro16: AVR_FREQ = 16000000L
# pro16: $(PROGRAM)_pro_16MHz.hex
# pro16: $(PROGRAM)_pro_16MHz.lst
# pro16_isp: pro16
# pro16_isp: TARGET = pro_16MHz
# # 2.7V brownout
# pro16_isp: HFUSE = DD
# # Full swing xtal (20MHz) 258CK/14CK+4.1ms
# pro16_isp: LFUSE = C6
# # 512 byte boot
# pro16_isp: EFUSE = 04
# pro16_isp: isp
#
#
# # Diecimila, Duemilanove with m168, and NG use identical bootloaders
# # Call it "atmega168" for generality and clarity, keep "diecimila" for
# # backward compatibility of makefile
# atmega168: TARGET = atmega168
# atmega168: MCU_TARGET = atmega168
# atmega168: CFLAGS += '-DBAUD_RATE=115200'
# atmega168: AVR_FREQ = 16000000L
# atmega168: $(PROGRAM)_atmega168.hex
# atmega168: $(PROGRAM)_atmega168.lst
# atmega168_isp: atmega168
# atmega168_isp: TARGET = atmega168
# # 2.7V brownout
# atmega168_isp: HFUSE = DD
# # Low power xtal (16MHz) 16KCK/14CK+65ms
# atmega168_isp: LFUSE = FF
# # 512 byte boot
# atmega168_isp: EFUSE = 04
# atmega168_isp: isp
#
# diecimila: TARGET = diecimila
# diecimila: MCU_TARGET = atmega168
# diecimila: CFLAGS += '-DBAUD_RATE=115200'
# diecimila: AVR_FREQ = 16000000L
# diecimila: $(PROGRAM)_diecimila.hex
# diecimila: $(PROGRAM)_diecimila.lst
# diecimila_isp: diecimila
# diecimila_isp: TARGET = diecimila
# # 2.7V brownout
# diecimila_isp: HFUSE = DD
# # Low power xtal (16MHz) 16KCK/14CK+65ms
# diecimila_isp: LFUSE = FF
# # 512 byte boot
# diecimila_isp: EFUSE = 04
# diecimila_isp: isp


# Atmega328 used on Arduino UNO and Arduino Ethernet
atmega328_w5100: EXT_OBJ = optiboot.o
atmega328_w5100: TARGET = atmega328_w5100
atmega328_w5100: MCU_TARGET = atmega328p
atmega328_w5100: CFLAGS += '-DBAUD_RATE=115200'
atmega328_w5100: AVR_FREQ = 16000000L
atmega328_w5100: LDSECTIONS  = -Wl,--section-start=.text=0x7000 #-Wl,--section-start=.version=0x7ffe
atmega328_w5100: $(PROGRAM)_atmega328_w5100.hex
atmega328_w5100: $(PROGRAM)_atmega328_w5100.lst
atmega328_w5100_isp: atmega328_w5100
atmega328_w5100_isp: TARGET = atmega328_w5100
atmega328_w5100_isp: MCU_TARGET = atmega328p
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328_w5100_isp: LFUSE = FF
# 4096 byte boot, SPIEN
atmega328_w5100_isp: HFUSE = D8
# 2.7V brownout
atmega328_w5100_isp: EFUSE = 05
atmega328_w5100_isp: isp

# Atmega328 used on Arduino UNO and Arduino Ethernet
atmega328_w5200: EXT_OBJ = optiboot.o
atmega328_w5200: TARGET = atmega328_w5200
atmega328_w5200: MCU_TARGET = atmega328p
atmega328_w5200: CFLAGS += '-DW5200=1' '-DBAUD_RATE=115200'
atmega328_w5200: AVR_FREQ = 16000000L
atmega328_w5200: LDSECTIONS  = -Wl,--section-start=.text=0x7000 #-Wl,--section-start=.version=0x7ffe
atmega328_w5200: $(PROGRAM)_atmega328_w5200.hex
atmega328_w5200: $(PROGRAM)_atmega328_w5200.lst
atmega328_w5200_isp: atmega328_w5200
atmega328_w5200_isp: TARGET = atmega328_w5200
atmega328_w5200_isp: MCU_TARGET = atmega328p
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328_w5200_isp: LFUSE = FF
# 4096 byte boot, SPIEN
atmega328_w5200_isp: HFUSE = D8
# 2.7V brownout
atmega328_w5200_isp: EFUSE = 05
atmega328_w5200_isp: isp

# Atmega328 used on Arduino UNO and Arduino Ethernet
atmega328_w5500: EXT_OBJ = optiboot.o
atmega328_w5500: TARGET = atmega328_w5500
atmega328_w5500: MCU_TARGET = atmega328p
atmega328_w5500: CFLAGS += '-DW5500=1' '-DBAUD_RATE=115200'
atmega328_w5500: AVR_FREQ = 16000000L
atmega328_w5500: LDSECTIONS  = -Wl,--section-start=.text=0x7000 #-Wl,--section-start=.version=0x7ffe
atmega328_w5500: $(PROGRAM)_atmega328_w5500.hex
atmega328_w5500: $(PROGRAM)_atmega328_w5500.lst
atmega328_w5500_isp: atmega328_w5500
atmega328_w5500_isp: TARGET = atmega328_w5500
atmega328_w5500_isp: MCU_TARGET = atmega328p
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328_w5500_isp: LFUSE = FF
# 4096 byte boot, SPIEN
atmega328_w5500_isp: HFUSE = D8
# 2.7V brownout
atmega328_w5500_isp: EFUSE = 05
atmega328_w5500_isp: isp

atmega328_ethernet: TARGET = atmega328_ethernet
atmega328_ethernet: MCU_TARGET = atmega328p
atmega328_ethernet: CFLAGS += '-DARDUINO_ETHERNET' '-DBAUD_RATE=115200'
atmega328_ethernet: AVR_FREQ = 16000000L
atmega328_ethernet: LDSECTIONS  = -Wl,--section-start=.text=0x7000 #-Wl,--section-start=.version=0x7ffe
atmega328_ethernet: $(PROGRAM)_atmega328_ethernet.hex
atmega328_ethernet: $(PROGRAM)_atmega328_ethernet.lst
atmega328_ethernet_isp: atmega328_ethernet
atmega328_ethernet_isp: TARGET = atmega328_ethernet
atmega328_ethernet_isp: MCU_TARGET = atmega328p
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega328_ethernet_isp: LFUSE = FF
# 4096 byte boot, SPIEN
atmega328_ethernet_isp: HFUSE = D8
# 2.7V brownout
atmega328_ethernet_isp: EFUSE = 05
atmega328_ethernet_isp: isp


# # Sanguino has a minimum boot size of 1024 bytes, so enable extra functions
# sanguino: TARGET = atmega644p
# sanguino: MCU_TARGET = atmega644p
# sanguino: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200' '-DBIGBOOT'
# sanguino: AVR_FREQ = 16000000L
# sanguino: LDSECTIONS  = -Wl,--section-start=.text=0xfc00
# sanguino: $(PROGRAM)_atmega644p.hex
# sanguino: $(PROGRAM)_atmega644p.lst
# sanguino_isp: sanguino
# sanguino_isp: TARGET = atmega644p
# sanguino_isp: MCU_TARGET = atmega644p
# # 1024 byte boot
# sanguino_isp: HFUSE = DE
# # Low power xtal (16MHz) 16KCK/14CK+65ms
# sanguino_isp: LFUSE = FF
# # 2.7V brownout
# sanguino_isp: EFUSE = 05
# sanguino_isp: isp
#
#
# Mega has a minimum boot size of 1024 bytes
# mega1280: TARGET = atmega1280
# mega1280: MCU_TARGET = atmega1280
# mega1280: CFLAGS += '-DBAUD_RATE=115200'
# mega1280: AVR_FREQ = 16000000L
# mega1280: LDSECTIONS  = -Wl,--section-start=.text=0x1f000
# mega1280: $(PROGRAM)_atmega1280.hex
# mega1280: $(PROGRAM)_atmega1280.lst
# mega1280_isp: mega1280
# mega1280_isp: TARGET = atmega1280
# mega1280_isp: MCU_TARGET = atmega1280
# # Low power xtal (16MHz) 16KCK/14CK+65ms
# mega1280_isp: LFUSE = FF
# # 4069 byte boot
# mega1280_isp: HFUSE = DA
# # 2.7V brownout
# mega1280_isp: EFUSE = F5
# mega1280_isp: isp
#
#
# Mega has a minimum boot size of 1024 bytes
atmega2560_w5100: TARGET = atmega2560_w5100
atmega2560_w5100: MCU_TARGET = atmega2560
atmega2560_w5100: CFLAGS += '-DBAUD_RATE=115200'
atmega2560_w5100: AVR_FREQ = 16000000L
atmega2560_w5100: LDSECTIONS  = -Wl,--section-start=.text=0x3e000
atmega2560_w5100: $(PROGRAM)_atmega2560_w5100.hex
atmega2560_w5100: $(PROGRAM)_atmega2560_w5100.lst
atmega2560_w5100_isp: atmega2560_w5100
atmega2560_w5100_isp: TARGET = atmega2560_w5100
atmega2560_w5100_isp: MCU_TARGET = atmega2560
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega2560_w5100_isp: LFUSE = FF
# 4069 byte boot
atmega2560_w5100_isp: HFUSE = D8
# 2.7V brownout
atmega2560_w5100_isp: EFUSE = FD
atmega2560_w5100_isp: isp
#
# Mega has a minimum boot size of 1024 bytes
atmega2560_w5200: TARGET = atmega2560_w5200
atmega2560_w5200: MCU_TARGET = atmega2560
atmega2560_w5200: CFLAGS += '-DW5200=1' '-DBAUD_RATE=115200'
atmega2560_w5200: AVR_FREQ = 16000000L
atmega2560_w5200: LDSECTIONS  = -Wl,--section-start=.text=0x3e000
atmega2560_w5200: $(PROGRAM)_atmega2560_w5200.hex
atmega2560_w5200: $(PROGRAM)_atmega2560_w5200.lst
atmega2560_w5200_isp: atmega2560_w5200
atmega2560_w5200_isp: TARGET = atmega2560_w5200
atmega2560_w5200_isp: MCU_TARGET = atmega2560
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega2560_w5200_isp: LFUSE = FF
# 4069 byte boot
atmega2560_w5200_isp: HFUSE = D8
# 2.7V brownout
atmega2560_w5200_isp: EFUSE = FD
atmega2560_w5200_isp: isp
#
# Mega has a minimum boot size of 1024 bytes
atmega2560_w5500: TARGET = atmega2560_w5500
atmega2560_w5500: MCU_TARGET = atmega2560
atmega2560_w5500: CFLAGS += '-DW5500=1' '-DBAUD_RATE=115200'
atmega2560_w5500: AVR_FREQ = 16000000L
atmega2560_w5500: LDSECTIONS  = -Wl,--section-start=.text=0x3e000
atmega2560_w5500: $(PROGRAM)_atmega2560_w5500.hex
atmega2560_w5500: $(PROGRAM)_atmega2560_w5500.lst
atmega2560_w5500_isp: atmega2560_w5500
atmega2560_w5500_isp: TARGET = atmega2560_w5500
atmega2560_w5500_isp: MCU_TARGET = atmega2560
# Low power xtal (16MHz) 16KCK/14CK+65ms
atmega2560_w5500_isp: LFUSE = FF
# 4069 byte boot
atmega2560_w5500_isp: HFUSE = D8
# 2.7V brownout
atmega2560_w5500_isp: EFUSE = FD
atmega2560_w5500_isp: isp


# Atmega1284
atmega1284_w5100: TARGET = atmega1284_w5100
atmega1284_w5100: MCU_TARGET = atmega1284p
atmega1284_w5100: CFLAGS += '-DBAUD_RATE=115200'
atmega1284_w5100: AVR_FREQ = 16000000L
atmega1284_w5100: LDSECTIONS  = -Wl,--section-start=.text=0x1f000
atmega1284_w5100: $(PROGRAM)_atmega1284_w5100.hex
atmega1284_w5100: $(PROGRAM)_atmega1284_w5100.lst

atmega1284_w5100_isp: atmega1284_w5100
atmega1284_w5100_isp: TARGET = atmega1284_w5100
atmega1284_w5100_isp: MCU_TARGET = atmega1284p
# 4096 word boot
atmega1284_w5100_isp: HFUSE = D8
# External power xtal (16MHz) 16KCK/14CK+65ms
atmega1284_w5100_isp: LFUSE = FF
# 2.7V brownout
atmega1284_w5100_isp: EFUSE = FD
atmega1284_w5100_isp: isp

atmega1284_w5200: TARGET = atmega1284_w5200
atmega1284_w5200: MCU_TARGET = atmega1284p
atmega1284_w5200: CFLAGS += '-DW5200=1' '-DBAUD_RATE=115200'
atmega1284_w5200: AVR_FREQ = 16000000L
atmega1284_w5200: LDSECTIONS  = -Wl,--section-start=.text=0x1f000
atmega1284_w5200: $(PROGRAM)_atmega1284_w5200.hex
atmega1284_w5200: $(PROGRAM)_atmega1284_w5200.lst

atmega1284_w5200_isp: atmega1284_w5200
atmega1284_w5200_isp: TARGET = atmega1284_w5200
atmega1284_w5200_isp: MCU_TARGET = atmega1284p
# 4096 word boot
atmega1284_w5200_isp: HFUSE = D8
# External power xtal (16MHz) 16KCK/14CK+65ms
atmega1284_w5200_isp: LFUSE = FF
# 2.7V brownout
atmega1284_w5200_isp: EFUSE = FD
atmega1284_w5200_isp: isp



atmega1284_w5500: TARGET = atmega1284_w5500
atmega1284_w5500: MCU_TARGET = atmega1284p
atmega1284_w5500: CFLAGS += '-DW5500=1' '-DBAUD_RATE=115200'
atmega1284_w5500: AVR_FREQ = 16000000L
atmega1284_w5500: LDSECTIONS  = -Wl,--section-start=.text=0x1f000
atmega1284_w5500: $(PROGRAM)_atmega1284_w5500.hex
atmega1284_w5500: $(PROGRAM)_atmega1284_w5500.lst

atmega1284_w5500_isp: atmega1284_w5500
atmega1284_w5500_isp: TARGET = atmega1284_w5500
atmega1284_w5500_isp: MCU_TARGET = atmega1284p
# 4096 word boot
atmega1284_w5500_isp: HFUSE = D8
# External power xtal (16MHz) 16KCK/14CK+65ms
atmega1284_w5500_isp: LFUSE = FF
# 2.7V brownout
atmega1284_w5500_isp: EFUSE = FD
atmega1284_w5500_isp: isp


debug1284_w5100: TARGET = debug1284_w5100
debug1284_w5100: MCU_TARGET = atmega1284p
debug1284_w5100: CFLAGS += '-DDEBUG_MAIN=1' '-DBAUD_RATE=115200'
debug1284_w5100: AVR_FREQ = 16000000L
debug1284_w5100: LDSECTIONS  = -Wl,--section-start=.text=0x1f000
debug1284_w5100: $(PROGRAM)_debug1284_w5100.hex
debug1284_w5100: $(PROGRAM)_debug1284_w5100.lst

debug1284_w5100_isp: debug1284_w5100
debug1284_w5100_isp: TARGET = debug1284_w5100
debug1284_w5100_isp: MCU_TARGET = atmega1284p
# 4096 word boot
debug1284_w5100_isp: HFUSE = D8
# External power xtal (16MHz) 16KCK/14CK+65ms
debug1284_w5100_isp: LFUSE = FF
# 2.7V brownout
debug1284_w5100_isp: EFUSE = FD
debug1284_w5100_isp: isp

# # ATmega8
# atmega8: TARGET = atmega8
# atmega8: MCU_TARGET = atmega8
# atmega8: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
# atmega8: AVR_FREQ = 16000000L
# atmega8: LDSECTIONS  = -Wl,--section-start=.text=0x1e00 -Wl,--section-start=.version=0x1ffe
# atmega8: $(PROGRAM)_atmega8.hex
# atmega8: $(PROGRAM)_atmega8.lst
# atmega8_isp: atmega8
# atmega8_isp: TARGET = atmega8
# atmega8_isp: MCU_TARGET = atmega8
# # SPIEN, CKOPT, Bootsize=512B
# atmega8_isp: HFUSE = CC
# # 2.7V brownout, Low power xtal (16MHz) 16KCK/14CK+65ms
# atmega8_isp: LFUSE = BF
# atmega8_isp: isp
#
#
# # ATmega88
# atmega88: TARGET = atmega88
# atmega88: MCU_TARGET = atmega88
# atmega88: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
# atmega88: AVR_FREQ = 16000000L
# atmega88: LDSECTIONS  = -Wl,--section-start=.text=0x1e00 -Wl,--section-start=.version=0x1ffe
# atmega88: $(PROGRAM)_atmega88.hex
# atmega88: $(PROGRAM)_atmega88.lst
# atmega88_isp: atmega88
# atmega88_isp: TARGET = atmega88
# atmega88_isp: MCU_TARGET = atmega88
# # 2.7V brownout
# atmega88_isp: HFUSE = DD
# # Low power xtal (16MHz) 16KCK/14CK+65ms
# atemga88_isp: LFUSE = FF
# # 512 byte boot
# atmega88_isp: EFUSE = 04
# atmega88_isp: isp
#
#
# # 8MHz clocked platforms
# # These are capable of 115200 baud
# lilypad: TARGET = lilypad
# lilypad: MCU_TARGET = atmega168
# lilypad: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
# lilypad: AVR_FREQ = 8000000L
# lilypad: $(PROGRAM)_lilypad.hex
# lilypad: $(PROGRAM)_lilypad.lst
# lilypad_isp: lilypad
# lilypad_isp: TARGET = lilypad
# # 2.7V brownout
# lilypad_isp: HFUSE = DD
# # Internal 8MHz osc (8MHz) Slow rising power
# lilypad_isp: LFUSE = E2
# # 512 byte boot
# lilypad_isp: EFUSE = 04
# lilypad_isp: isp
#
# lilypad_resonator: TARGET = lilypad_resonator
# lilypad_resonator: MCU_TARGET = atmega168
# lilypad_resonator: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
# lilypad_resonator: AVR_FREQ = 8000000L
# lilypad_resonator: $(PROGRAM)_lilypad_resonator.hex
# lilypad_resonator: $(PROGRAM)_lilypad_resonator.lst
# lilypad_resonator_isp: lilypad_resonator
# lilypad_resonator_isp: TARGET = lilypad_resonator
# # 2.7V brownout
# lilypad_resonator_isp: HFUSE = DD
# # Full swing xtal (20MHz) 258CK/14CK+4.1ms
# lilypad_resonator_isp: LFUSE = C6
# # 512 byte boot
# lilypad_resonator_isp: EFUSE = 04
# lilypad_resonator_isp: isp
#
#
# #
# pro8: TARGET = pro_8MHz
# pro8: MCU_TARGET = atmega168
# pro8: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
# pro8: AVR_FREQ = 8000000L
# pro8: $(PROGRAM)_pro_8MHz.hex
# pro8: $(PROGRAM)_pro_8MHz.lst
# pro8_isp: pro8
# pro8_isp: TARGET = pro_8MHz
# # 2.7V brownout
# pro8_isp: HFUSE = DD
# # Full swing xtal (20MHz) 258CK/14CK+4.1ms
# pro8_isp: LFUSE = C6
# # 512 byte boot
# pro8_isp: EFUSE = 04
# pro8_isp: isp
#
#
# #
# atmega328_pro8: TARGET = atmega328_pro_8MHz
# atmega328_pro8: MCU_TARGET = atmega328p
# atmega328_pro8: CFLAGS += '-DLED_START_FLASHES=3' '-DBAUD_RATE=115200'
# atmega328_pro8: AVR_FREQ = 8000000L
# atmega328_pro8: LDSECTIONS = -Wl,--section-start=.text=0x7e00 -Wl,--section-start=.version=0x7ffc
# atmega328_pro8: $(PROGRAM)_atmega328_pro_8MHz.hex
# atmega328_pro8: $(PROGRAM)_atmega328_pro_8MHz.lst
# atmega328_pro8_isp: atmega328_pro8
# atmega328_pro8_isp: TARGET = atmega328_pro_8MHz
# atmega328_pro8_isp: MCU_TARGET = atmega328p
# # 512 byte boot, SPIEN
# atmega328_pro8_isp: HFUSE = DE
# # Low power xtal (16MHz) 16KCK/14CK+65ms
# atmega328_pro8_isp: LFUSE = FF
# # 2.7V brownout
# atmega328_pro8_isp: EFUSE = 05
# atmega328_pro8_isp: isp
#
#
# # 1MHz clocked platforms
# # These are capable of 9600 baud
# luminet: TARGET = luminet
# luminet: MCU_TARGET = attiny84
# luminet: CFLAGS += '-DLED_START_FLASHES=3' '-DSOFT_UART' '-DBAUD_RATE=9600'
# luminet: CFLAGS += '-DVIRTUAL_BOOT_PARTITION'
# luminet: AVR_FREQ = 1000000L
# luminet: LDSECTIONS = -Wl,--section-start=.text=0x1d00 -Wl,--section-start=.version=0x1efe
# luminet: $(PROGRAM)_luminet.hex
# luminet: $(PROGRAM)_luminet.lst
# luminet_isp: luminet
# luminet_isp: TARGET = luminet
# luminet_isp: MCU_TARGET = attiny84
# # Brownout disabled
# luminet_isp: HFUSE = DF
# # 1MHz internal oscillator, slowly rising power
# luminet_isp: LFUSE = 62
# # Self-programming enable
# luminet_isp: EFUSE = FE
# luminet_isp: isp



#
# Generic build instructions
#
#
isp: $(TARGET)
	$(ISPFUSES)
	$(ISPFLASH)

isp-stk500: $(PROGRAM)_$(TARGET).hex
	$(STK500-1)
	$(STK500-2)

%.elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(SIZE) $@

clean:
	rm -rf *.o *.i *.s *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex *~

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -j .version --set-section-flags .version=alloc,load -O binary $< $@
