# Overview
Integration between Raspberry Pi Pico and ST7735 LCD display using SPI. This is a project I used to start learning about embedded programming.
- jaeg's [pico-st7735](https://github.com/jaeg/pico-st7735) repository was a very helpful resource to help me understand how the datasheet can be translated to code.

Currently, this program just powers on the display and draws some pixels. My next step is to create a wrapper to simplify drawing rectangles to the display.
# Hardware Setup
I wrote this to work with this display: [ST7735 Display](https://www.amazon.com/JESSINIE-Display-Arduino-128x160-Interface/dp/B0D31BGJWF?crid=2Q2KVXUFMIG50&dib=eyJ2IjoiMSJ9.a0L_drOaew8cKO7aMcplregfow70tPskr9NF6asfKDtp5BGatvhNQa_7Gweb96WIhZHDcPD4CdQmzY2xka8AgaCJzD4M77n-siBc8ES-Is2aZedd-y1XcoMpYPckUomoX8Mid--cMnYWw8k5spYS093RX43KKPgauLt78wDu2N5DlHtsfxA_2517oqQ5ViDZQihXo4X7zxLGI1Zyu9vsgm9MDEKGJi1LdytkfGWLg0o.KJ8hvTqy0ncEOc8wuIb84jZGaL6FeJA6Z07WdgM1z0w&dib_tag=se&keywords=ST7735+display&qid=1776713580&sprefix=st7735+display%2Caps%2C222&sr=8-3)
The code can be configured to use different pins on the Pico (See the table on the [RP2040 datasheet](https://pip-assets.raspberrypi.com/categories/814-rp2040/documents/RP-008371-DS-1-rp2040-datasheet.pdf?disposition=inline#io-user-bank-function-table) for the options), but these are the ones used by my code:

| Pico Pin | Display Pin | Description |
| -------- | ----------- | ----------- |
| GP 0     | DC          |             |
| GP 1     | RES         |             |
| GP 17    | CS          |             |
| GP 18    | SCL         |             |
| GP 19    | SDA         |             |
| GND      | GND         |             |
| 3v3      | VCC         |             |

# Usage
## Setting up the Pico
I followed the Raspberry Pi Getting Started guide [here.](https://pip-assets.raspberrypi.com/categories/610-raspberry-pi-pico/documents/RP-008276-DS-1-getting-started-with-pico.pdf?disposition=inline)

Once the pico sdk is installed, run the following commands to build the program:
```shell
# create a build directory
mkdir build
cd build
# make the project
cmake ..
make
```

The `st7735.uf2` file can then be flashed to the Pico to run the program.
