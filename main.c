#include "pico/stdlib.h"
#include "hardware/spi.h"

#define ST7735_CS 17 // chip select for the display
#define ST7735_RES 0
#define ST7735_DX 1
#define PICO_SCK 18
#define PICO_TX 19

void cs_select(uint8_t cs) {
    //asm volatile("nop \n nop \n nop");
    gpio_put(cs, 0);
    //asm volatile("nop \n nop \n nop"); 
}

void cs_deselect(uint8_t cs) {
    //asm volatile("nop \n nop \n nop");
    gpio_put(cs, 1);
    //asm volatile("nop \n nop \n nop");
}

void send_command(uint8_t cs, uint8_t command) {
    // pull DX low to indicate a command
    gpio_put(ST7735_DX, 0);
    // select the display by setting CS low
    cs_select(cs);
    // write command (assume command length is 1 byte)
    // pass a pointer to the command
    spi_write_blocking(spi0, &command, 1);
    // deselect the display
    cs_deselect(cs);
}

void send_data(uint8_t cs, uint8_t data) {
    // pull DX low to indicate a command
    gpio_put(ST7735_DX, 1);
    // select the display by setting CS low
    cs_select(cs);
    // write command (assume command length is 1 byte)
    // pass a pointer to the command
    spi_write_blocking(spi0, &data, 1);
    // deselect the display
    cs_deselect(cs);
}

int main() {
    // initialize spi
    // start spi clock at 10MHz
    spi_init(spi0, 4000 * 1000);
    // enable SPI functionality for selected pins, this table includes more info: https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#group_hardware_gpio_1autotoc_md0
    gpio_set_function(PICO_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PICO_TX, GPIO_FUNC_SPI);

    // these pins don't need spi functionality
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    // initialize chip select
    gpio_init(ST7735_CS);
    gpio_set_dir(ST7735_CS, GPIO_OUT);
    // a chip is selected by pulling low, so default to high
    gpio_put(ST7735_CS, 1);
    // initialize reset pin
    gpio_init(ST7735_RES);
    gpio_set_dir(ST7735_RES, GPIO_OUT);
    // according to the st7735 datasheet, reset is triggered by pulling low, so default to high
    gpio_put(ST7735_RES, 1);
    // initialize dx pin
    gpio_init(ST7735_DX);
    gpio_set_dir(ST7735_DX, GPIO_OUT);

    // display power-on sequence
    // set reset low for 10ms
    gpio_put(ST7735_RES, 0);
    sleep_ms(10);
    gpio_put(ST7735_RES, 1);
    sleep_ms(10);
    // send reset command
    send_command(ST7735_CS, 0x01);
    sleep_ms(150);
    // send sleep out command
    send_command(ST7735_CS, 0x11);
    sleep_ms(150);

    // screen config
    // set pixel full
    send_command(ST7735_CS, 0x3A);
    send_data(ST7735_CS, 0x06);
    // access control (MADCTL)
    //send_command(ST7735_CS, 0x36);
    //send_data(ST7735_CS, 0);

    // send display on command
    send_command(ST7735_CS, 0x29);
    sleep_ms(150);

    // set the screen boundaries to write to (optional, defaults to whole screen area)
    // set x start and end
    //send_command(ST7735_CS, 0x2A); // send column address set (CASET) command
    uint8_t x_start = 0;
    uint8_t x_end = 126;
    // each value requires 2 bytes of data, so send 0 for upper 8 bits
    //send_data(ST7735_CS, 0); send_data(ST7735_CS, x_start);
    //send_data(ST7735_CS, 0); send_data(ST7735_CS, x_end);
    // set y start and end
    //send_command(ST7735_CS, 0x2B); // send row address set (RASET) command
    uint8_t y_start = 0;
    uint8_t y_end = 126;
    // each value requires 2 bytes of data, so send 0 for upper 8 bits
    //send_data(ST7735_CS, 0); send_data(ST7735_CS, y_start);
    //send_data(ST7735_CS, 0); send_data(ST7735_CS, y_end);

    // write pixels to the screen
    // after every write, the display memory address is incremented
    // activate write mode
    send_command(ST7735_CS, 0x2C);
    // write rgb values
    for (int i=0; i<128*160; i++) {
        uint8_t r = 0;
        //uint8_t r = 0xFC;
        uint8_t g = 0;
        uint8_t b = 0;
        // TODO: how do we send 3 params per pixel?
        send_data(ST7735_CS, r); send_data(ST7735_CS, g); send_data(ST7735_CS, b);
    }

    // debug: turn on pico led
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
}
