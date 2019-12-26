#ifndef _SPI_h_
#define _SPI_h_

#include "Arduino.h"
#include "driver/spi_master.h"

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

class SPISettings
{
  public:
    SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {}
    SPISettings() { SPISettings(4000000, MSBFIRST, SPI_MODE0); }
};

class SPIClass
{
  private:
    spi_device_handle_t spi = nullptr;
    spi_host_device_t host = VSPI_HOST;
    spi_transaction_t transaction;
  public:
    SPIClass(spi_host_device_t bus = VSPI_HOST);
    bool begin();
    bool begin(uint8_t mosi, uint8_t miso, uint8_t sck, uint8_t cs);
    void end(void);
    void beginTransaction(SPISettings settings);
    void endTransaction(void);
    void setBitOrder(uint8_t bitOrder);
    void setClockDivider(uint8_t clockDiv);
    void setDataMode(uint8_t dataMode);
    uint8_t transfer(uint8_t data);
    void transfer(void *buf, size_t count);
    void usingInterrupt(uint8_t interruptNumber);
    void notUsingInterrupt(uint8_t interruptNumber);
};

extern SPIClass SPI;

#endif
