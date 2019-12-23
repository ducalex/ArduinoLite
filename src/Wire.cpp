#include "Wire.h"

TwoWire::TwoWire(int8_t num):
    num((i2c_port_t)num)
{}

TwoWire::~TwoWire()
{
    flush();
}

bool TwoWire::begin(int sdaPin, int sclPin)
{
    if (sdaPin < 0 || sclPin < 0) {
        if (init == false) {
            ESP_LOGE("I2C", "SDA and SCL pins must be set in first begin() call");
        }
    } else if (sdaPin != sda || sclPin != scl) {
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
        if (i2c_driver_install(num, conf.mode, 0, 0, 0) == ESP_OK) {
            init = true;
        } else {
            ESP_LOGE("I2C", "Failed to start the i2c driver");
        }
    }
    return init;
}

void TwoWire::end(void)
{
    i2c_driver_delete(num);
    init = false;
}

void TwoWire::setClock(uint32_t frequency)
{
    //i2cSetFrequency(i2c, frequency);
}

void TwoWire::beginTransmission(int address)
{
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_WRITE, true);
}

uint8_t TwoWire::endTransmission(bool sendStop)
{
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(num, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
    return 0;
}

uint8_t TwoWire::requestFrom(int address, size_t size, bool sendStop)
{
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (address << 1) | I2C_MASTER_READ, true);
    if (size > 1) {
        i2c_master_read(cmd, rxBuffer, size - 1, I2C_MASTER_ACK);
    }
    i2c_master_read(cmd, rxBuffer + (size - 1), 1, I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(num, cmd, 1000 / portTICK_RATE_MS);
	i2c_cmd_link_delete(cmd);
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

int TwoWire::readBytes(uint8_t* buffer, size_t size)
{
    for (int b, i = 0; i < size; ++i) {
        if ((b = read()) < 0) {
            return i;
        }
        buffer[i] = (uint8_t)b;
    }
    return size;
}

int TwoWire::peek(void)
{
    return (rxIndex < rxCount) ? rxBuffer[rxIndex] : -1;
}

void TwoWire::flush(void)
{
    //
}

size_t TwoWire::write(uint8_t data)
{
    i2c_master_write_byte(cmd, data, true);
    return 1;
}

size_t TwoWire::write(const uint8_t* data, size_t size)
{
    i2c_master_write(cmd, (uint8_t*)data, size, true);
    return size;
}


TwoWire Wire = TwoWire(0);
TwoWire Wire1 = TwoWire(1);
