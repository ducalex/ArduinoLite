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
    i2c_cmd_handle_t cmd;
    bool init = false;

    uint8_t rxBuffer[128];
    uint8_t rxIndex = 0;
    uint8_t rxCount = 0;

  public:
    TwoWire(int8_t num);
    ~TwoWire();
    bool begin(int sda = -1, int scl = -1);
    void setClock(uint32_t);
    void end(void);

    // void onReceive(void (*)(int));
    // void onRequest(void (*)(void));

    void beginTransmission(int address);
    uint8_t endTransmission(bool sendStop = true);
    uint8_t requestFrom(int address, size_t size, bool sendStop = true);

    int available(void);
    void flush(void);
    int peek(void);
    int read(void);

    int readBytes(uint8_t* data, size_t size);
    int readBytes(char* data, size_t size) {return readBytes((uint8_t*)data, size); }

    size_t write(uint8_t b);
    size_t write(const uint8_t* data, size_t size);
    size_t write(const char* str) { return write((uint8_t*)str, strlen(str)); }
    size_t write(int data) { return write((uint8_t)data); }
};

extern TwoWire Wire;
extern TwoWire Wire1;

#endif
