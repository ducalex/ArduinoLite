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
    return host_init;
}

bool SPIClass::begin(uint8_t mosi, uint8_t miso, uint8_t sck, uint8_t cs)
{
    end(); // Clear previous settings

    spi_bus_config_t buscfg = {
        .mosi_io_num = mosi,
        .miso_io_num = miso,
        .sclk_io_num = sck,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 2048
    };

    host_init = spi_bus_initialize(host, &buscfg, 2) == ESP_OK;
    device_cs = cs;

    return host_init;
}

void SPIClass::end()
{
    if (spi != nullptr) {
        spi_bus_remove_device(spi);
        spi = nullptr;
    }
    if (host_init == true) {
        spi_bus_free(host);
        host_init = false;
    }
}

void SPIClass::beginTransaction(SPISettings settings)
{
    /*
    spi_device_interface_config_t devcfg = {
        .mode = settings.dataMode,
        .clock_speed_hz = settings.clock,
        .spics_io_num = device_cs,
        .queue_size = 7,
        .pre_cb = nullptr,
    };

    if (spi_bus_add_device(host, &devcfg, &spi) != ESP_OK) {
        // start transaction
        memset(&transaction, 0, sizeof(transaction));
    }
    */
}

void SPIClass::endTransaction(void)
{
    spi_device_transmit(spi, &transaction);
    spi_bus_remove_device(spi);
    spi = nullptr;
}

uint8_t SPIClass::transfer(uint8_t data)
{
    return 0;
}

void SPIClass::transfer(void *buf, size_t count)
{

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
