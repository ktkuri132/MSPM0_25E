#include <driver.h>

#include "OLED.h"


void delay_us(uint32_t nus) {
	uint32_t cycles = nus * (CPUCLK_FREQ / 1000000);
	delay_cycles(cycles);
}

void dealy_ms(uint32_t nms) {
	uint32_t cycles = nms * (CPUCLK_FREQ / 1000);
	delay_cycles(cycles);
}

void MSP_SPI_GPIO_Port_Init(void) {
}

int oled_init(dev_arg_t a) {
	OLED_Init();
	return 0;
}

void MSP_SPI_SCK(uint8_t state) {
	if (state) {
		DL_GPIO_setPins(OLED_SCL_D0_PORT, OLED_SCL_D0_PIN);
	} else {
		DL_GPIO_clearPins(OLED_SCL_D0_PORT, OLED_SCL_D0_PIN);
	}
}

void MSP_SPI_MOSI(uint8_t state) {
	if (state) {
		DL_GPIO_setPins(OLED_SDA_D1_PORT, OLED_SDA_D1_PIN);
	} else {
		DL_GPIO_clearPins(OLED_SDA_D1_PORT, OLED_SDA_D1_PIN);
	}
}

uint8_t MSP_SPI_MISO(void) {
	return 0;
}

void MSP_SPI_CS(uint8_t state) {
	(void)state;
}

void MSP_SPI_CS2(uint8_t state) {
	if (state) {
		DL_GPIO_setPins(OLED_DC_PORT, OLED_DC_PIN);
	} else {
		DL_GPIO_clearPins(OLED_DC_PORT, OLED_DC_PIN);
	}
}

void MSP_SPI_CS3(uint8_t state) {
	if (state) {
		DL_GPIO_setPins(OLED_RES_PORT, OLED_RES_PIN);
	} else {
		DL_GPIO_clearPins(OLED_RES_PORT, OLED_RES_PIN);
	}
}

void MSP_IIC_GPIO_Port_Init(void) {
	DL_GPIO_initDigitalOutput(OLED_SCL_D0_IOMUX);
	DL_GPIO_initDigitalOutput(OLED_SDA_D1_IOMUX);
	DL_GPIO_setPins(OLED_SCL_D0_PORT, OLED_SCL_D0_PIN);
	DL_GPIO_setPins(OLED_SDA_D1_PORT, OLED_SDA_D1_PIN);
}

void MSP_IIC_SDA_IN(void) {
	DL_GPIO_initDigitalInput(OLED_SDA_D1_IOMUX);
}

void MSP_IIC_SDA_OUT(void) {
	DL_GPIO_initDigitalOutput(OLED_SDA_D1_IOMUX);
}

uint8_t MSP_IIC_READ_SDA(void) {
	uint32_t val = DL_GPIO_readPins(OLED_SDA_D1_PORT, OLED_SDA_D1_PIN);
	return (val > 0) ? 1 : 0;
}