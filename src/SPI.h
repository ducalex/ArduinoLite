#ifndef _SPI_H_
#define _SPI_H_

#include "inttypes.h"
#include "string.h"
#include "stddef.h"
#include "esp_log.h"

#define SPI_HAS_TRANSACTION 1
#define SPI_HAS_NOTUSINGINTERRUPT 1
#define SPI_ATOMIC_VERSION 1

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

class SPISettings
{
  public:
    SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {}
    SPISettings() { SPISettings(4000000, MSBFIRST, SPI_MODE0); }
};

class SPIClass
{
  public:
    static void begin() {}
    static void end() {}
    static void usingInterrupt(uint8_t interruptNumber) {}
    static void notUsingInterrupt(uint8_t interruptNumber) {}
    static void beginTransaction(SPISettings settings) {}
    static uint8_t transfer(uint8_t data) { return 0;}
    static uint16_t transfer16(uint16_t data) { return 0;}
    static void transfer(void *buf, size_t count) {}
    static void endTransaction(void) {}
    static void setBitOrder(uint8_t bitOrder) {}
    static void setDataMode(uint8_t dataMode) {}
    static void setClockDivider(uint8_t clockDiv) {}
};

extern SPIClass SPI;

#endif
