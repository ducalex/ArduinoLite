#ifndef ArduinoLite_h
#define ArduinoLite_h

#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "stdlib.h"
#include "unistd.h"
#include "WString.h"
#include "Print.h"

typedef bool boolean;
typedef uint8_t byte;
typedef unsigned int word;

#define ARDUINO 100 // Some libraries need this

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

void analogWrite(uint8_t pin, long val);
long analogRead(uint8_t pin);

#define attachInterrupt(pin, cb, mode) attachInterruptArg(pin, cb, NULL, mode);
#define attachInterruptArg(pin, cb, arg, mode)
#define detachInterrupt(pin)

#define micros()  ((unsigned long)esp_timer_get_time())
#define millis()  ((unsigned long)(esp_timer_get_time() / 1000ULL))
#define delay(ms)  usleep((ms) * 1000)
#define delayMicroseconds(us)  usleep(us)
#define yield()  vPortYield()
#define NOP()  asm volatile ("nop")
#define PGM_P  const char *
#define PROGMEM

#define pgm_read_byte(addr)   (*(const unsigned char *)(addr))
#define pgm_read_word(addr)   ({ typeof(addr) _addr = (addr); *(const unsigned short *)(_addr); })
#define pgm_read_dword(addr)  ({ typeof(addr) _addr = (addr); *(const unsigned long *)(_addr); })
#define pgm_read_float(addr)  ({ typeof(addr) _addr = (addr); *(const float *)(_addr); })
#define pgm_read_ptr(addr)    ({ typeof(addr) _addr = (addr); *(void * const *)(_addr); })

#define bitRead(value, bit)  (((value) >> (bit)) & 0x01)
#define bitSet(value, bit)   ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitval) (bitval ? bitSet(value, bit) : bitClear(value, bit))
#define lowByte(value)  ((uint8_t)(value))
#define highByte(value) ((uint8_t)((value) >> 8))

#ifdef __cplusplus
#include <cmath>
#include <algorithm>
using std::abs;
using std::cos;
using std::sin;
using std::tan;
using std::isnan;
using std::isinf;
using std::ceil;
using std::floor;
using std::pow;
using std::sqrt;
template<typename T, typename U, typename V> T constrain(T amt, U low, V high);
template<typename T> T map(T x, T in_min, T in_max, T out_min, T out_max);
template<typename T, typename U> T max(T a, U b);
template<typename T, typename U> T min(T a, U b);
template<typename T> long round(T n);
#endif

void randomSeed(long seed);
long random(long min, long max);
long random(long max);

void interrupts();
void noInterrupts();

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout);

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);

#endif
