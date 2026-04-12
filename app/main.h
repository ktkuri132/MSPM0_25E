#ifndef __MAIN_H
#define __MAIN_H

#include <OLED.h>
#include <control.h>
#include <df_key.h>
#include <df_spi.h>
#include <driver.h>
#include <encoder.h>
#include <gray_nomcu.h>
#include <pid.h>
#include <shell.h>


extern shell Shell;               // Shell协议结构体实例
extern Sysfpoint Shell_Sysfpoint; // 系统函数指针结构体实例
extern EnvVar env_vars[];         // 环境变量数组
extern DeviceFamily Device_info;  // 设备信息结构体实例
extern dev_model_t Drivers_model_poor[];
extern sys_run_time_t sys_runtime; // 系统运行时间结构体实例
extern Encoder Eleft;
extern Encoder Eright;
extern systrl pid_switch;
extern PID pid_speed_left;
extern PID pid_speed_right;
extern PID pid_position;
extern PID pid_turn;
extern Kt Key_SET;
extern Kt Key_UP;
extern Kt Key_DOWN;
extern Kt Key_RETURN;
extern Kt Key_ESC;
extern Kert Key_SET_Handler;
extern Kert Key_UP_Handler;
extern Kert Key_DOWN_Handler;
extern Kert Key_RETURN_Handler;
extern Kert Key_ESC_Handler;

extern int Normal_ERROR;        // 误差值存储变量
#define GRAY_ERROR Normal_ERROR // 误差值存储在Normal_ERROR中

extern Move_Control move_ctrl;

void Control();
void Stop_when_out_of_line(void);

#endif