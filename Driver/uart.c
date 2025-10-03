#include "dev_model_core.h"
#include "mspm0g350x.h"
#include <driver.h>
#include <dl_uart.h>
#include <stdarg.h>
#include <shell.h>

int __io_putchar(int ch){
    DL_UART_transmitDataBlocking(UART_0_INST, (uint8_t)ch); // 发送字符
    return ch; // 返回发送的字符
}

// 串口发送单个字符
void USART1_SendChar(char ch)
{
    DL_UART_transmitDataBlocking(UART_0_INST, (uint8_t)ch); // 发送字符
}

// 串口发送字符串
void USART1_SendString(char *str)
{
    while(*str)
    {
        USART1_SendChar(*str++);
    }
}

uint8_t USART1_ReceiveChar(void *None,uint8_t *data){
    (void)None; // 避免未使用参数警告
    *data = DL_UART_Main_receiveData(UART_0_INST); // 阻塞等待接收字符
    return *data; // 返回接收到的字符
}

int printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[256]; // 缓冲区大小可以根据需要调整
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    USART1_SendString(buffer); // 发送格式化字符串到USART1
    return len; // 返回发送的字符长度
}

int usart1_init(dev_arg_t arg)
{
    if(arg.ptr == NULL){
        return -1;    // 返回-1表示失败
    }
    return 0;    // 返回0表示成功
}

int usart1_start(dev_arg_t arg)
{
    (void)arg;  // 忽略参数

    return 0;  // 返回0表示成功
}

int usart1_stop(dev_arg_t arg)
{
    (void)arg;  // 忽略参数

    return 0;  // 返回0表示成功
}


void UART_0_IRQHandler_CallBack();

void UART_0_INST_IRQHandler(){
    uint8_t data;
    if(DL_UART_receiveDataCheck(UART_0_INST,&data)){
        UART_0_IRQHandler_CallBack();
    }
}
