# StatsDisplay_client

[![GitHub version](https://img.shields.io/badge/version-v1.0.0-blue.svg)](https://github.com/narfel/gpxrt/blob/main/README.md)
[![License](https://img.shields.io/badge/license-MIT-green)](https://github.com/narfel/StatsDisplay_client/blob/master/LICENSE)

Arduino sketch that receives data over a serial connection and displays it on a 16x2 LCD screen. It is intended to work with the companion program StatsDisplay.


## Description

> A small windows application that sends stats such as CPU temperature, memory usage, etc. to a 16x2 display over a serial connection.


## How to use

* Upload the Arduino using the Arduino IDE or any other compatible tool. The serial port and baud rate must match the settings of the sender program.
* I have it running on a D1 Mini Esp8266 board, but it will run on everything that can use the LCD lib below. I tested it with an old Arduino Nano and it runs fine.

## Dependencies

The sketch uses [this](https://github.com/johnrickman/LiquidCrystal_I2C) LiquidCrystal library to control the LCD display. It expects the data to be sent in a specific format, as described in the comments of the code.

## License

Copyright (c) 2023 Narfel.

Usage is provided under the MIT License. See [LICENSE](https://github.com/narfel/StatsDisplay_client/blob/master/LICENSE) for the full details.