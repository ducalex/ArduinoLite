#include "Arduino.h"

void analogWrite(uint8_t pin, long val)
{
}

long analogRead(uint8_t pin)
{
    return 0;
}

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return 0;
}

unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return 0;
}

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{
    uint8_t output = 0;

    for (int i = 0; i < 8; i++) {
        digitalWrite(clockPin, HIGH);
        if (bitOrder == LSBFIRST){
            output |= digitalRead(dataPin) << i;
        } else {
            output |= digitalRead(dataPin) << (7 - i);
        }
        digitalWrite(clockPin, LOW);
    }

    return output;
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
    for (int i = 0; i < 8; i++){
        if (bitOrder == LSBFIRST){
            digitalWrite(dataPin, (value & (1 << i)) ? HIGH : LOW);
        } else {
            digitalWrite(dataPin, (value & (1 << (7 - i))) ? HIGH : LOW);
        }
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);
    }
}

inline void interrupts()
{
    //
}

inline void noInterrupts()
{
    //
}

inline long random(long max)
{
    return random(0, max);
}

inline long random(long min, long max)
{
    long value = min;
    do {
        value = esp_random();
    } while (value < min || value > max);
    return value;
}

inline void randomSeed(long seed)
{
}

template <typename T, typename U, typename V>
inline T constrain(T amt, U low, V high)
{
    return max(min(amt, high), low);
}

template <typename T>
inline T map(T x, T in_min, T in_max, T out_min, T out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

template <typename T, typename U>
inline T max(T a, U b)
{
    return std::max(a, (T)b);
}

template <typename T, typename U>
inline T min(T a, U b)
{
    return std::min(a, (T)b);
}

template <typename T>
inline long round(T n)
{
    return ((n) >= 0 ? (long)((n) + 0.5) : (long)((n)-0.5));
}
