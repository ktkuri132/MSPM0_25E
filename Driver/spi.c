#include "OLED.h"
#include <driver.h>

void MSP_SPI_GPIO_Port_Init(void) {

}

int oled_init(dev_arg_t a){
    OLED_Init();
    return 0;
}

void MSP_SPI_SCK(uint8_t state){
    if (state) {
        DL_GPIO_setPins(OLED_SCL_D0_PORT, OLED_SCL_D0_PIN);
    } else {
        DL_GPIO_clearPins(OLED_SCL_D0_PORT, OLED_SCL_D0_PIN);
    }
}

void MSP_SPI_MOSI(uint8_t state){
    if (state) {
        DL_GPIO_setPins(OLED_SDA_D1_PORT, OLED_SDA_D1_PIN);
    } else {
        DL_GPIO_clearPins(OLED_SDA_D1_PORT, OLED_SDA_D1_PIN);
    }
}

uint8_t MSP_SPI_MISO(void) {

}

void MSP_SPI_CS(uint8_t state){

}

void MSP_SPI_CS2(uint8_t state){
    if (state) {
        DL_GPIO_setPins(OLED_DC_PORT, OLED_DC_PIN);
    } else {
        DL_GPIO_clearPins(OLED_DC_PORT, OLED_DC_PIN);
    }
}

void MSP_SPI_CS3(uint8_t state){
    if (state) {
        DL_GPIO_setPins(OLED_RES_PORT, OLED_RES_PIN);
    } else {
        DL_GPIO_clearPins(OLED_RES_PORT, OLED_RES_PIN);
    }
}