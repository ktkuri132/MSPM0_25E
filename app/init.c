#include "main.h"
shell Shell = {
    .Shell_Init = false,               // Shell未初始化
    .c = 0,                            // 初始化接收字符
    .Res_len = 0,                      // 初始化接收长度
    .UART_NOTE = 0,                    // 初始化串口节点
    .RunStae = 0,                      // 初始化运行状态
    .Data_Receive = USART1_ReceiveChar // 数据接收函数指针
};

SSAS spi_Dev = {
    .Soft_SPI_GPIO_Port_Init = MSP_SPI_GPIO_Port_Init, // SPI GPIO端口初始化函数
    .Soft_SPI_SCK = MSP_SPI_SCK,                       // SCK线控制函数
    .Soft_SPI_MOSI = MSP_SPI_MOSI,                     // MOSI线控制函数
    .Soft_SPI_MISO = MSP_SPI_MISO,                     // 读取MISO线状态
    .Soft_SPI_CS = MSP_SPI_CS,                         // CS线控制函数
    .Soft_SPI_CS2 = MSP_SPI_CS2,                       // CS2线控制函数
    .Soft_SPI_CS3 = MSP_SPI_CS3                        // CS3线控制函数
};

Sysfpoint Shell_Sysfpoint;

DeviceFamily Device_info = {.Architecture = "cortex-m0plus",
                            .DeviceName = "MSPM0G3507",
                            .OS = "BareMetal",
                            .Device = "MSPM0G3x",
                            .User = "M Klio",
                            .Password = "133990",
                            .Version = "1.0.0"};

sys_run_time_t sys_runtime = {
    .count = 0, .senior_count = 0, .sec = 0, .min = 0, .hour = 0};

dev_model_t Drivers_model_poor[] = {{
                                        .device_name = "NVIC", // 设备名称
                                        .init = NVIC_Init,     // 设备初始化函数
                                        .enable = NULL,        // 设备使能函数
                                        .disable = NULL,       // 设备禁用函数
                                        .arg.ptr = NULL // 传递给设备的参数指针
                                    },
                                    {
                                        .device_name = "OLED", // 设备名称
                                        .init = oled_init,     // 设备初始化函数
                                        .enable = NULL,        // 设备使能函数
                                        .disable = NULL,       // 设备禁用函数
                                        .arg.ptr = NULL // 传递给设备的参数指针
                                    },
                                    {
                                        .device_name = "Gray", // 设备名称
                                        .init = Gray_Init,     // 设备初始化函数
                                        .enable = NULL,        // 设备使能函数
                                        .disable = NULL,       // 设备禁用函数
                                        .arg.ptr = NULL // 传递给设备的参数指针
                                    },
                                    {
                                        .device_name = "Encoder", // 设备名称
                                        .init = encoder_init, // 设备初始化函数
                                        .enable = NULL,       // 设备使能函数
                                        .disable = NULL,      // 设备禁用函数
                                        .arg.ptr = NULL // 传递给设备的参数指针
                                    },
                                    {.device_name = "", // 空字符串表示数组结束
                                     .init = NULL,
                                     .enable = NULL,
                                     .disable = NULL,
                                     .arg.ptr = NULL}

};

EnvVar env_vars[] = {
    {NULL} // 环境变量列表结束标志
};