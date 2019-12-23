ArduinoLite is a lightweight Arduino library for the ESP32. My goal was to provide the minimum needed to be able to use Arduino sensors libraries with little to no change.

Arduino-esp32 is a great project but it is just a port of Arduino-esp8266 and as such it contains custom, incomplete, 
and often buggy implementations of the various peripherals (I2C, SD Card, Wifi, SPI, etc). This becomes an issue if
most of your project is written in native esp-idf code as it may cause conflicts or hard to track down bugs. ArduinoLite
is a wrapper around the native esp-idf API.

## Features

Currently implemented:
- The basic functions (pinMode, digitalWrite, millis, etc)
- The Wire library
- The WiFi library
- The String library

To be implemented:
- SPI

Could be added for convenience:
- Stream/Print/Serial (To make display libraries work with no changes)
- SD (to avoid all the boilerplate esp-idf code)

Out of scope:
- The rest


## Credits:
- The WString is taken from Arduino (AVR)
