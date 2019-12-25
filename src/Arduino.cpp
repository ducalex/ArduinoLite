#include "Arduino.h"

inline void interrupts()
{

}

inline void noInterrupts()
{

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

inline long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
