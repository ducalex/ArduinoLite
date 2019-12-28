#ifndef ArduinoLite_h
#define ArduinoLite_h

#include "esp_system.h"
#include "esp_adc_cal.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/dac.h"
#include "stdlib.h"
#include "unistd.h"
#include "WString.h"
#include "Stream.h"

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

#define digitalPinIsValid(pin)      ((pin) < 40)
#define digitalPinToInterrupt(pin)  (digitalPinIsValid(pin) ? (pin) : -1)
#define digitalPinHasPWM(pin)       ((pin) < 36)

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define micros()  ((unsigned long)esp_timer_get_time())
#define millis()  ((unsigned long)(esp_timer_get_time() / 1000ULL))
#define delay(ms)  usleep((ms) * 1000)
#define delayMicroseconds(us)  usleep(us)
#define yield()  vPortYield()
#define NOP()  asm volatile ("nop")
#define PGM_P  const char *
#define PROGMEM

#define pgm_read_byte(addr)  (*(const unsigned char *)(addr))
#define pgm_read_word(addr)  (*(const unsigned short *)(addr))
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))

#define bitRead(value, bit)  (((value) >> (bit)) & 0x01)
#define bitSet(value, bit)   ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitval) (bitval ? bitSet(value, bit) : bitClear(value, bit))
#define lowByte(value)  ((uint8_t)(value))
#define highByte(value) ((uint8_t)((value) >> 8))


void pinMode(uint8_t pin, uint16_t mode);
uint8_t digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, uint16_t val);

uint16_t analogRead(uint8_t pin);
void analogReadResolution(uint8_t bits);
void analogWrite(uint8_t pin, uint16_t val);

void attachInterrupt(int interrupt, void (*userFunc)(void), int mode, void *arg = NULL);
void detachInterrupt(int interrupt);

void interrupts();
void noInterrupts();

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout);

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);

void randomSeed(long seed);
long random(long min, long max);
long random(long max);


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
using std::min;
using std::max;
using ::round;
template<typename T, typename U, typename V> T constrain(T amt, U low, V high);
template<typename T> T map(T x, T in_min, T in_max, T out_min, T out_max);
#endif

#endif
