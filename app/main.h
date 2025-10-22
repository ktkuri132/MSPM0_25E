#ifndef __MAIN_H
#define __MAIN_H

#include <driver.h>
#include <shell.h>
#include <df_spi.h>
#include <OLED.h>
#include <gray_nomcu.h>
#include <encoder.h>
#include <pid.h>

extern shell Shell; // Shell协议结构体实例
extern Sysfpoint Shell_Sysfpoint; // 系统函数指针结构体实例
extern EnvVar env_vars[]; // 环境变量数组
extern DeviceFamily Device_info; // 设备信息结构体实例
extern dev_model_t Drivers_model_poor[];
extern sys_run_time_t sys_runtime; // 系统运行时间结构体实例
extern Encoder Eleft;
extern Encoder Eright;
extern PID pid_speed_left;
extern PID pid_speed_right;

void Control();


#endif