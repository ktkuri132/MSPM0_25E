#include "main.h"
#include "OLED.h"
#include <gray_nomcu.h>
#include <stdint.h>
#include <stdio.h>
#include <tb6612.h>


int main() {
    SYSCFG_DL_init(); // 初始化MSP驱动库
    dev_model_core_init(Drivers_model_poor); // 初始化设备池
    MCU_Shell_Init(&Shell, &Device_info); // 初始化Shell


    while (1) {
        Task_Switch_Tick_Handler(&Shell_Sysfpoint); // 任务切换处理
        No_Mcu_Ganv_Sensor_Task_With_tick(&gray); // 运行灰度传感器任务
        OLED_Printf(0, 0, OLED_6X8, "%d", GRAY_GetAnalogError()); // 显示误差值
        OLED_Printf(0, 16, OLED_6X8, "L:%d     R:%d", Eleft.Val,
                    Eright.Val); // 显示编码器计数值
        OLED_Printf(0, 24, OLED_6X8, "%f", pid_speed_left.output);
        OLED_Printf(0, 32, OLED_6X8, "%f", pid_speed_right.output);
        OLED_Update();
    }
    return 0;
}
