#ifndef ArduinoLite_h
#define ArduinoLite_h

#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "unistd.h"
#include "WString.h"

#ifdef __cplusplus
#include <algorithm>
#include <cmath>
using std::abs;
using std::cos;
using std::sin;
using std::tan;
using std::max;
using std::min;
#endif

typedef bool boolean;
typedef uint8_t byte;
typedef unsigned int word;

#define F_CPU (CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ * 1000000U)

#define LSBFIRST 0
#define MSBFIRST 1

#define LOW             0x0
#define HIGH            0x1
#define INPUT           GPIO_MODE_INPUT|(GPIO_FLOATING << 8)
#define INPUT_PULLUP    GPIO_MODE_INPUT|(GPIO_PULLUP_ONLY << 8)
#define INPUT_PULLDOWN  GPIO_MODE_INPUT|(GPIO_PULLDOWN_ONLY << 8)
#define OUTPUT          GPIO_MODE_OUTPUT|(GPIO_FLOATING << 8)

#define pinMode(pin, mode)  gpio_set_direction((gpio_num_t)(pin), (gpio_mode_t)((mode) & 0xFF)); \
                            gpio_set_pull_mode((gpio_num_t)(pin), (gpio_pull_mode_t)((mode) >> 8))
#define digitalWrite(pin, val)  gpio_set_level((gpio_num_t)(pin), (uint32_t)(val))
#define digitalRead(pin)        gpio_get_level((gpio_num_t)(pin))
#define digitalPinIsValid(pin)      ((pin) < 40)
#define digitalPinCanOutput(pin)    ((pin) < 34)
#define digitalPinToInterrupt(pin)  (digitalPinIsValid(pin) ? (pin) : -1)
#define digitalPinHasPWM(pin)       (digitalPinCanOutput(pin))

#define analogWrite(pin, val)
#define analogRead(pin)

#define attachInterrupt(pin, cb, mode)
#define attachInterruptArg(pin, cb, arg, mode)
#define detachInterrupt(pin)

#define micros()  ((unsigned long)esp_timer_get_time())
#define millis()  ((unsigned long)(esp_timer_get_time() / 1000ULL))
#define delay(ms)  delayMicroseconds((ms) * 1000)
#define delayMicroseconds(us)  usleep(us)
#define yield()  vPortYield()
#define NOP()  asm volatile ("nop")
#define PROGMEM

#define pgm_read_byte(addr)   (*(const unsigned char *)(addr))
#define pgm_read_word(addr)   ({ typeof(addr) _addr = (addr); *(const unsigned short *)(_addr); })
#define pgm_read_dword(addr)  ({ typeof(addr) _addr = (addr); *(const unsigned long *)(_addr); })
#define pgm_read_float(addr)  ({ typeof(addr) _addr = (addr); *(const float *)(_addr); })
#define pgm_read_ptr(addr)    ({ typeof(addr) _addr = (addr); *(void * const *)(_addr); })

inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

inline void interrupts() {}
inline void noInterrupts() {}

// To do:
// pulseIn()
// pulseInLong()
// shiftIn()
// shiftOut()
// bit()
// bitClear()
// bitRead()
// bitSet()
// bitWrite()
// highByte()
// lowByte()

#endif
