#ifndef _Wire_h_
#define _Wire_h_

#include "Arduino.h"
#include "driver/i2c.h"

class TwoWire
{
  private:
    i2c_port_t num;
    gpio_num_t sda = GPIO_NUM_MAX;
    gpio_num_t scl = GPIO_NUM_MAX;
    i2c_cmd_handle_t cmd = nullptr;
    bool init = false;

    uint8_t rxBuffer[128];
    uint8_t rxIndex = 0;
    uint8_t rxCount = 0;

  public:
    TwoWire(int8_t num);
    ~TwoWire();
    bool begin();
    bool begin(int sda, int scl);
    void setClock(uint32_t);
    void end(void);

    // void onReceive(void (*)(int));
    // void onRequest(void (*)(void));

    void beginTransmission(int address, i2c_rw_t type = I2C_MASTER_WRITE);
    uint8_t endTransmission(bool sendStop = true);
    uint8_t requestFrom(int address, size_t size, bool sendStop = true);

    int available(void);
    int peek(void);
    int read(void);
    int readBytes(uint8_t* data, size_t size);

    size_t write(uint8_t b);
    size_t write(const uint8_t* data, size_t size);
    size_t write(const char* str) { return write((uint8_t*)str, strlen(str)); }
    size_t write(int data) { return write((uint8_t)data); }
};

extern TwoWire Wire;
extern TwoWire Wire1;

#endif
