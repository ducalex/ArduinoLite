#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "SPI.h"

SPIClass::SPIClass(spi_host_device_t bus)
{
    host = bus;
}

bool SPIClass::begin()
{
    return true;
}

bool SPIClass::begin(uint8_t mosi, uint8_t miso, uint8_t sck, uint8_t cs)
{
    if (spi != nullptr) {
        end();
    }
    /*
    spi_bus_config_t buscfg = {
        .mosi_io_num = mosi,
        .miso_io_num = miso,
        .sclk_io_num = sck,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 2048
    };

    spi_device_interface_config_t devcfg = {
        .mode = 0,
        .clock_speed_hz = SPI_MASTER_FREQ_16M,
        .spics_io_num = cs,
        .queue_size = 7,
        .pre_cb = nullptr,
    };

    if (spi_bus_initialize(host, &buscfg, 2) != ESP_OK) {
        return false;
    }

    if (spi_bus_add_device(host, &devcfg, &spi) != ESP_OK) {
        return false;
    }
    */
    return true;
}

void SPIClass::end()
{
    if (spi != nullptr) {
        spi_bus_remove_device(spi);
        spi_bus_free(host);
    }
}

void SPIClass::beginTransaction(SPISettings settings)
{
    memset(&transaction, 0, sizeof(transaction));
}

void SPIClass::endTransaction(void)
{
    spi_device_transmit(spi, &transaction);
}

void SPIClass::setBitOrder(uint8_t bitOrder)
{
    //
}

void SPIClass::setClockDivider(uint8_t clockDiv)
{
    //
}

void SPIClass::setDataMode(uint8_t dataMode)
{
    //
}

uint8_t SPIClass::transfer(uint8_t data)
{
    return 0;
}

void SPIClass::transfer(void *buf, size_t count)
{
    //
}

void SPIClass::usingInterrupt(uint8_t interruptNumber)
{
    //
}

void SPIClass::notUsingInterrupt(uint8_t interruptNumber)
{
    //
}

SPIClass SPI(VSPI_HOST);
