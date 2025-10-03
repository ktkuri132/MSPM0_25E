#include "main.h"
#include "OLED.h"
#include <stdint.h>
#include <stdio.h>
#include <gray_nomcu.h>
#include <tb6612.h>

int main() {
    SYSCFG_DL_init();                     // 初始化MSP驱动库
    dev_model_core_init(Drivers_model_poor);        // 初始化设备池
    MCU_Shell_Init(&Shell, &Device_info);  // 初始化Shell


    PWMA(7000); // 设置右电机速度
    PWMB(800); // 设置左电机速度
    while (1) {
        Task_Switch_Tick_Handler(&Shell_Sysfpoint); // 任务切换处理
        No_Mcu_Ganv_Sensor_Task_With_tick(&gray); // 运行灰度传感器任务
        OLED_Printf(0,0,OLED_6X8,"%d",GRAY_GetAnalogError()); // 显示误差值
        OLED_Printf(8, 0, OLED_6X8, "L:%d     R:%d", Eleft.Val, Eright.Val); // 显示编码器计数值
        OLED_Update();
    }
    return 0;
}
