#include "Wire.h"

TwoWire::TwoWire(int8_t num):
    num((i2c_port_t)num)
{}

TwoWire::~TwoWire()
{
    end();
}

bool TwoWire::begin()
{
    if (init == false) {
        ESP_LOGE("I2C", "SDA and SCL pins must be set in first begin() call");
    }
    return init;
}

bool TwoWire::begin(int sdaPin, int sclPin)
{
    end(); // Clear the previous driver
    sda = (gpio_num_t)sdaPin;
    scl = (gpio_num_t)sclPin;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = sda;
    conf.scl_io_num = scl;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 200000;
    i2c_param_config(num, &conf);
    init = (i2c_driver_install(num, conf.mode, 0, 0, 0) == ESP_OK);
    if (!init) {
        ESP_LOGE("I2C", "Failed to start the i2c driver");
    }
    return init;
}

void TwoWire::end(void)
{
    if (init == true) {
        i2c_driver_delete(num);
        init = false;
    }
}

void TwoWire::setClock(uint32_t frequency)
{
    //i2cSetFrequency(i2c, frequency);
}

void TwoWire::beginTransmission(int address, i2c_rw_t type)
{
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (address << 1) | type, true);
}

uint8_t TwoWire::endTransmission(bool sendStop)
{
    if (cmd != nullptr) {
        i2c_master_stop(cmd);
        i2c_master_cmd_begin(num, cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(cmd);
    }
    cmd = nullptr;
    return 0;
}

uint8_t TwoWire::requestFrom(int address, size_t size, bool sendStop)
{
    beginTransmission(address, I2C_MASTER_READ);
    if (size > 1) {
        i2c_master_read(cmd, rxBuffer, size - 1, I2C_MASTER_ACK);
    }
    i2c_master_read(cmd, rxBuffer + (size - 1), 1, I2C_MASTER_NACK);
    endTransmission();
    rxCount = size;
    rxIndex = 0;
    return size;
}

int TwoWire::available(void)
{
    return rxCount - rxIndex;
}

int TwoWire::read(void)
{
    return (rxIndex < rxCount) ? rxBuffer[rxIndex++] : -1;
}

int TwoWire::peek(void)
{
    return (rxIndex < rxCount) ? rxBuffer[rxIndex] : -1;
}

size_t TwoWire::write(uint8_t data)
{
    return (i2c_master_write_byte(cmd, data, true) == ESP_OK) ? 1 : 0;
}

size_t TwoWire::write(const uint8_t* data, size_t size)
{
    return (i2c_master_write(cmd, (uint8_t*)data, size, true) == ESP_OK) ? size : 0;
}


TwoWire Wire = TwoWire(0);
TwoWire Wire1 = TwoWire(1);
