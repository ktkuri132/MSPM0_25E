#include "main.h"

#include <gray_nomcu.h>
#include <stdio.h>
#include <tb6612.h>

void SET_KEY_Pressed() {
	printf("SET KEY is Pressed\n");
	led_on();
}

void SET_KEY_Released() {
	printf("SET KEY is Released\n");
	pid_switch.ENABLE_ALL_PID_Controlors(&pid_switch);	// 启用所有PID控制器
	led_off();
}

void ESC_KEY_Pressed() { printf("ESC KEY is Pressed\n"); }

int main() {
	SYSCFG_DL_init();						  // 初始化MSP驱动库
	dev_model_core_init(Drivers_model_poor);  // 初始化设备池
	// MCU_Shell_Init(&Shell, &Device_info); // 初始化Shell
	while (1) {
		Normal_ERROR = GRAY_GetDigtalError(Get_digtal());  // 获取数字量误差值
		move_ctrl.Update(&move_ctrl);					   // 更新运动控制状态
		// Task_Switch_Tick_Handler(&Shell_Sysfpoint);		   // 任务切换处理
		No_Mcu_Ganv_Sensor_Task_With_tick(&gray);  // 运行灰度传感器任务
		Stop_when_out_of_line();				   // 当完全脱离黑线时停止电机
		Key_Event(&Key_SET_Handler, &Key_SET, 0, SET_KEY_Pressed, NULL, SET_KEY_Released,
				  NULL);  // 当按键被按下时执行Start_when_Key_Pressed函数
						  // OLED_Printf(0,0,OLED_6X8,"status: 0x%x", move_ctrl.current_state);  // 在OLED上显示误差值
						  // OLED_Printf(0,8,OLED_6X8,"Turning: %d", move_ctrl.status.Turning);  // 在OLED上显示误差值
						  // OLED_Update();
	}
	return 0;
}
