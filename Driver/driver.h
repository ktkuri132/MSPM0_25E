#ifndef __DRIVER_H
#define __DRIVER_H

#include <mspm0g350x.h>
#include <dev_model_core.h>
#include <ti_msp_dl_config.h>

int NVIC_Init(dev_arg_t arg);

int oled_init(dev_arg_t);

void MSP_SPI_SCK(uint8_t state);
void MSP_SPI_MOSI(uint8_t state);
uint8_t MSP_SPI_MISO(void);
void MSP_SPI_CS(uint8_t state);
void MSP_SPI_CS2(uint8_t state);
void MSP_SPI_CS3(uint8_t state);
void MSP_SPI_GPIO_Port_Init(void);

void USART1_SendChar(char ch);
void USART1_SendString(char *str);
uint8_t USART1_ReceiveChar(void *None,uint8_t *data);
int usart1_init(dev_arg_t arg);
int usart1_start(dev_arg_t arg);
int usart1_stop(dev_arg_t arg);

int encoder_init(dev_arg_t arg);
#endif