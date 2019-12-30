ArduinoLite is a lightweight Arduino component for esp-idf (ESP32). It provides the minimum required to run many Arduino libraries and Arduino projects without modification.

Arduino-esp32 is a great project but it is a port of Arduino-esp8266 and as such it contains custom, incomplete, 
and often buggy implementations of the various peripherals (I2C, SD Card, Wifi, SPI, etc). This becomes an issue if most of your project is written in native esp-idf code as it may cause conflicts or hard to track down bugs. In contrast, ArduinoLite is a simple wrapper around the native esp-idf API.

## Features

Currently implemented:
- Most Arduino [language functions](https://www.arduino.cc/reference/en/)
- The Wire library
- The SPI library (Work in progress)
- Partial WiFi library (Only WiFi class, no WiFiClient or WiFiServer)
- The Stream, String, and Print classes

Out of scope:
- The rest

## Credits:
- The Stream, String, and Print classes are taken from Arduino (AVR)
