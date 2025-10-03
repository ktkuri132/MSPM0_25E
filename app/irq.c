#include <shell.h>
#include <driver.h>
#include "main.h"
#include "shell_style.h"
#include <stddef.h>

void SysTick_Handler(void)
{
    sys_runtimer(&sys_runtime);
    Task_tick(&gray);
    if(sys_runtime.count % 10 == 0) // 每10ms执行一次速度计算
    {
        Encoder_GetVal();
    }
}

void TIMER_0_INST_IRQHandler(){
    switch (DL_TimerA_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMERA_IIDX_ZERO:
            Control();
            break;
        default:
            break;
    }
}

void UART_0_IRQHandler_CallBack(){
    if(Shell.Data_Receive != NULL){
        BIE_UART(NULL, &Shell_Sysfpoint, &Shell, env_vars, &Device_info);
    }
}

void GROUP1_IRQHandler(void){
    GROUP1_IRQHandler_CallBack();
}