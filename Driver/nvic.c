#include "mspm0g350x.h"
#include <driver.h>

int NVIC_Init(dev_arg_t arg)
{
    (void)arg; // 忽略参数
    // 配置UART0中断优先级
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
    return 0; // 返回0表示成功
}
