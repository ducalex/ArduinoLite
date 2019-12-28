#include "Arduino.h"
static int8_t adc_gpios[] = {
    21, -1, 22, -1, 20, -1, -1, -1, -1, -1,
    -1, -1, 25, 24, 26, 23, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 28, 29, 27, -1, -1,
    -1, -1, 14, 15, 16, 17, 10, 11, 12, 13,
};

static adc_bits_width_t adc_resolution = ADC_WIDTH_BIT_12;


void pinMode(uint8_t pin, uint16_t mode)
{
    if (pin == 25) dac_output_disable(DAC_CHANNEL_1);
    if (pin == 26) dac_output_disable(DAC_CHANNEL_2);
    gpio_set_direction((gpio_num_t)pin, (gpio_mode_t)(mode & 0xFF));
    gpio_set_pull_mode((gpio_num_t)pin, (gpio_pull_mode_t)(mode >> 8));
}

uint8_t digitalRead(uint8_t pin)
{
    return (uint8_t)gpio_get_level((gpio_num_t)(pin));
}

void digitalWrite(uint8_t pin, uint16_t val)
{
    gpio_set_level((gpio_num_t)(pin), val);
}

uint16_t analogRead(uint8_t pin)
{
    if (pin >= 40 || adc_gpios[pin] == -1) {
        return 0;
    } else if (adc_gpios[pin] < 20) {
        adc1_channel_t channel = (adc1_channel_t)(adc_gpios[pin] - 10);
        adc1_config_width(adc_resolution);
        adc1_config_channel_atten(channel, ADC_ATTEN_DB_11);
        return adc1_get_raw(channel);
    } else {
        adc2_channel_t channel = (adc2_channel_t)(adc_gpios[pin] - 20);
        int value = 0;
        adc2_config_channel_atten(channel, ADC_ATTEN_DB_11);
        adc2_get_raw((adc2_channel_t)channel, adc_resolution, &value);
        return value;
    }
}

void analogReadResolution(uint8_t bits)
{
    if (bits >= 9 && bits <= 12) {
        adc_resolution = (adc_bits_width_t)(bits - 9);
    }
}

void analogWrite(uint8_t pin, uint16_t val)
{
    if (pin == 25) {
        dac_output_enable(DAC_CHANNEL_1);
        dac_output_voltage(DAC_CHANNEL_1, val);
    }
    if (pin == 26) {
        dac_output_enable(DAC_CHANNEL_2);
        dac_output_voltage(DAC_CHANNEL_2, val);
    }
}

void attachInterrupt(uint8_t interrupt, void (*userFunc)(void), int mode, void *arg)
{

}

void detachInterrupt(uint8_t interrupt)
{

}

inline void interrupts()
{
    //
}

inline void noInterrupts()
{
    //
}

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    timeout += micros();
    while (timeout < micros() && digitalRead(pin) == state);
    while (timeout < micros()) {
        if (digitalRead(pin) == state) {
            unsigned long pulse_start = micros();
            while (timeout < micros() && digitalRead(pin) == state);
            return micros() - pulse_start;
        }
    }
    return 0;
}

unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return pulseIn(pin, state, timeout);
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
    //
}
