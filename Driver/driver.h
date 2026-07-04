#ifndef __DRIVER_H
#define __DRIVER_H

#include <dev_model_core.h>
#include <df_key.h>
#include <mspm0g350x.h>
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
uint8_t USART1_ReceiveChar(void *None, uint8_t *data);
int usart1_init(dev_arg_t arg);
int usart1_start(dev_arg_t arg);
int usart1_stop(dev_arg_t arg);

int encoder_init(dev_arg_t arg);

void delay_us(uint32_t nus);
void dealy_ms(uint32_t nms);

void MSP_IIC_GPIO_Port_Init(void);
void MSP_IIC_SDA_IN(void);
void MSP_IIC_SDA_OUT(void);
uint8_t MSP_IIC_READ_SDA(void);

void led_on();
void led_off();

bool Key_SET_Read(Kt *key);
bool Key_UP_Read(Kt *key);
bool Key_DOWN_Read(Kt *key);
bool Key_RETURN_Read(Kt *key);
bool Key_ESC_Read(Kt *key);
#endif