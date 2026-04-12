#include "gray_nomcu.h"
#include "driver.h"

No_MCU_Sensor gray;
unsigned short Anolog[8] = {0};
unsigned short white[8] = {3310, 3284, 3185, 3219, 3157, 3243, 3200, 3273};
unsigned short black[8] = {1837, 1280, 801, 540, 370, 690, 170, 610};
unsigned short Normal[8];
int Normal_ERROR = 0;

/* 函数功能：采集8个通道的模拟值并进行均值滤波
   参数说明：result - 存储8个通道处理结果的数组 */
void Get_Analog_value(unsigned short *result) {
  unsigned char i, j;
  unsigned int Anolag = 0;
  // 遍历8个传感器通道（3位地址线组合）
  for (i = 0; i < 8; i++) {
    // 通过地址线组合切换传感器通道（注意取反逻辑）
    Switch_Address_0(!(i & 0x01)); // 地址线0，对应bit0
    Switch_Address_1(!(i & 0x02)); // 地址线1，对应bit1
    Switch_Address_2(!(i & 0x04)); // 地址线2，对应bit2

    // 每个通道采集8次ADC值进行均值滤波
    for (j = 0; j < 8; j++) {
      Anolag += Get_adc_of_user(); // 累加ADC采样值
    }
    if (!Direction)
      result[i] = Anolag / 8; // 计算平均值
    else
      result[7 - i] = Anolag / 8; // 计算平均值
    Anolag = 0;                   // 重置累加器
  }
}

/* 函数功能：将模拟值转换为数字信号（二值化处理）
   参数说明：
   adc_value - 原始ADC值数组
   Gray_white - 白色阈值数组
   Gray_black - 黑色阈值数组
   Digital - 输出的数字信号（按位表示） */
void convertAnalogToDigital(unsigned short *adc_value,
                            unsigned short *Gray_white,
                            unsigned short *Gray_black,
                            unsigned char *Digital) {
  for (int i = 0; i < 8; i++) {
    if (adc_value[i] > Gray_white[i]) {
      *Digital |= (1 << i); // 超过白阈值置1（白色）
    } else if (adc_value[i] < Gray_black[i]) {
      *Digital &= ~(1 << i); // 低于黑阈值置0（黑色）
    }
    // 中间灰度值保持原有状态
  }
}

/* 函数功能：归一化ADC值到指定范围
   参数说明：
   adc_value - 原始ADC值数组
   Normal_factor - 归一化系数数组
   Calibrated_black - 校准黑值数组
   result - 存储归一化结果的数组
   bits - ADC最大量程值（如255/1024等） */
void normalizeAnalogValues(unsigned short *adc_value, double *Normal_factor,
                           unsigned short *Calibrated_black,
                           unsigned short *result, double bits) {
  for (int i = 0; i < 8; i++) {
    unsigned short n;
    // 计算归一化值（减去黑电平后缩放）
    if (adc_value[i] < Calibrated_black[i])
      n = 0; // 低于黑电平归零
    else
      n = (adc_value[i] - Calibrated_black[i]) * Normal_factor[i];

    // 限幅处理
    if (n > bits) {
      n = bits;
    }
    result[i] = n;
  }
}

/* 函数功能：传感器结构体初始化（首次初始化）
   参数说明：sensor - 传感器结构体指针 */
void No_MCU_Ganv_Sensor_Init_Frist(No_MCU_Sensor *sensor) {
  // 清零所有校准数据和状态
  memset(sensor->Calibrated_black, 0, 16);
  memset(sensor->Calibrated_white, 0, 16);
  memset(sensor->Normal_value, 0, 16);
  memset(sensor->Analog_value, 0, 16);

  // 初始化归一化系数
  for (int i = 0; i < 8; i++) {
    sensor->Normal_factor[i] = 0.0;
  }

  // 初始化状态变量
  sensor->Digtal = 0;
  sensor->Time_out = 0;
  sensor->Tick = 0;
  sensor->ok = 0; // 标记未完成校准
}

/* 函数功能：传感器完整初始化（带校准参数）
   参数说明：
   sensor - 传感器结构体指针
   Calibrated_white - 校准白值数组
   Calibrated_black - 校准黑值数组 */
void No_MCU_Ganv_Sensor_Init(No_MCU_Sensor *sensor,
                             unsigned short *Calibrated_white,
                             unsigned short *Calibrated_black) {
  No_MCU_Ganv_Sensor_Init_Frist(sensor);

  // 根据配置设置ADC量程
  if (Sensor_ADCbits == _8Bits)
    sensor->bits = 255.0;
  else if (Sensor_ADCbits == _10Bits)
    sensor->bits = 1024.0;
  else if (Sensor_ADCbits == _12Bits)
    sensor->bits = 4096.0;
  else if (Sensor_ADCbits == _14Bits)
    sensor->bits = 16384.0;

  // 设置采样超时时间（基础版/青春版）
  if (Sensor_Edition == Class)
    sensor->Time_out = 1;
  else
    sensor->Time_out = 10;

  double Normal_Diff[8];
  unsigned short temp;

  for (int i = 0; i < 8; i++) {
    // 确保白值 > 黑值（必要时交换）
    if (Calibrated_black[i] >= Calibrated_white[i]) {
      temp = Calibrated_white[i];
      Calibrated_white[i] = Calibrated_black[i];
      Calibrated_black[i] = temp;
    }

    // 计算灰度阈值（1:2和2:1分界点）
    sensor->Gray_white[i] = (Calibrated_white[i] * 2 + Calibrated_black[i]) / 3;
    sensor->Gray_black[i] = (Calibrated_white[i] + Calibrated_black[i] * 2) / 3;

    // 保存校准数据
    sensor->Calibrated_black[i] = Calibrated_black[i];
    sensor->Calibrated_white[i] = Calibrated_white[i];

    // 处理无效校准数据（全黑/全白/相等情况）
    if ((Calibrated_white[i] == 0 && Calibrated_black[i] == 0) ||
        (Calibrated_white[i] == Calibrated_black[i])) {
      sensor->Normal_factor[i] = 0.0; // 无效通道
      continue;
    }

    // 计算归一化系数
    Normal_Diff[i] = (double)Calibrated_white[i] - (double)Calibrated_black[i];
    sensor->Normal_factor[i] = sensor->bits / Normal_Diff[i];
  }
  sensor->ok = 1; // 标记初始化完成
}

/* 函数功能：传感器主任务（无定时器版本）*/
void No_Mcu_Ganv_Sensor_Task_Without_tick(No_MCU_Sensor *sensor) {
  Get_Analog_value(sensor->Analog_value); // 采集数据
  convertAnalogToDigital(sensor->Analog_value, sensor->Gray_white,
                         sensor->Gray_black, &sensor->Digtal); // 二值化处理
  normalizeAnalogValues(sensor->Analog_value, sensor->Normal_factor,
                        sensor->Calibrated_black, sensor->Normal_value,
                        sensor->bits); // 归一化处理
}

/* 函数功能：传感器主任务（带定时器版本）*/
void No_Mcu_Ganv_Sensor_Task_With_tick(No_MCU_Sensor *sensor) {
  if (sensor->Tick >= sensor->Time_out) // 检查是否到达采样周期
  {
    // 执行数据采集和处理
    Get_Analog_value(sensor->Analog_value);
    convertAnalogToDigital(sensor->Analog_value, sensor->Gray_white,
                           sensor->Gray_black, &sensor->Digtal);
    normalizeAnalogValues(sensor->Analog_value, sensor->Normal_factor,
                          sensor->Calibrated_black, sensor->Normal_value,
                          sensor->bits);
    sensor->Tick = 0; // 重置定时器
  }
}

/* 函数功能：定时器tick递增 */
void Task_tick(No_MCU_Sensor *sensor) { sensor->Tick++; }

/* 函数功能：获取数字信号状态 */
unsigned char Get_Digtal_For_User(No_MCU_Sensor *sensor) {
  return sensor->Digtal; // 返回8位数字状态（每位对应一个传感器）
}

uint8_t Get_digtal(void) { return (uint8_t)gray.Digtal; }

/* 函数功能：获取归一化后的数据
   返回值：1-成功 0-未初始化 */
unsigned char Get_Normalize_For_User(No_MCU_Sensor *sensor,
                                     unsigned short *result) {
  if (!sensor->ok)
    return 0;
  else {
    memcpy(result, sensor->Normal_value, 16); // 拷贝归一化数据
    return 1;
  }
}

/* 函数功能：获取原始校准数据
   返回值：1-成功 0-未初始化 */
unsigned char Get_Anolog_Value(No_MCU_Sensor *sensor, unsigned short *result) {
  Get_Analog_value(sensor->Analog_value); // 重新采集数据
  memcpy(result, sensor->Analog_value, 16);
  if (!sensor->ok)
    return 0;
  else
    return 1;
}

/************************************************功能测试函数**********************************/

static unsigned char rx_buff[256] = {0};

void Gray_Show_Anolog(No_MCU_Sensor *sensor) {
  // 获取传感器模拟量结果(有黑白值初始化后返回1 没有返回 0)
  if (Get_Anolog_Value(sensor, Anolog)) {
    sprintf((char *)rx_buff, "Anolog %d-%d-%d-%d-%d-%d-%d-%d\r\n", Anolog[0],
            Anolog[1], Anolog[2], Anolog[3], Anolog[4], Anolog[5], Anolog[6],
            Anolog[7]);
    USART1_SendString((char *)rx_buff);
    memset(rx_buff, 0, 256);
  }
}

void Gray_Show_Digtal(No_MCU_Sensor *sensor) {
  uint8_t Digtal = 0;
  // 获取传感器数字量结果(只有当有黑白值传入进去了之后才会有这个值！！)
  Digtal = Get_Digtal_For_User(sensor);
  sprintf((char *)rx_buff, "Digtal %d-%d-%d-%d-%d-%d-%d-%d\r\n",
          (Digtal >> 0) & 0x01, (Digtal >> 1) & 0x01, (Digtal >> 2) & 0x01,
          (Digtal >> 3) & 0x01, (Digtal >> 4) & 0x01, (Digtal >> 5) & 0x01,
          (Digtal >> 6) & 0x01, (Digtal >> 7) & 0x01);
  USART1_SendString((char *)rx_buff);
  memset(rx_buff, 0, 256);
}

void Gray_Show_Normalize(No_MCU_Sensor *sensor) {
  // 获取传感器归一化结果(只有当有黑白值传入进去了之后才会有这个值！！有黑白值初始化后返回1
  // 没有返回 0)
  if (Get_Normalize_For_User(sensor, Normal)) {
    sprintf((char *)rx_buff, "Normalize %d=%d-%d-%d-%d-%d-%d-%d-%d\r\n",
            Normal_ERROR, Normal[0], Normal[1], Normal[2], Normal[3], Normal[4],
            Normal[5], Normal[6], Normal[7]);
    USART1_SendString((char *)rx_buff);
    memset(rx_buff, 0, 256);
  }
}

/****************************************巡线接口*************************************/
/**
 * @brief 灰度传感器得到数字量误差等级，以中间为0
 * @param data 灰度传感器得到的数字量
 * @return 误差等级，范围约为[-56, 56]，中间为8
 */
int GRAY_GetDigtalError(uint8_t data) {
  static int32_t filtered_error_q8 = 0;
  static uint8_t filter_inited = 0;

  int32_t sum_index = 0;
  int32_t black_count = 0;

  // 使用所有检测到黑线的通道计算“重心”，比只取第一个黑点更平滑
  for (int i = 0; i < 8; i++) {
    if (!(data & (1 << i))) {
      sum_index += i;
      black_count++;
    }
  }

  int32_t raw_error = 0;
  if (black_count > 0) {
    // Q8 定点：center_q8 范围约 [0, 7] * 256
    int32_t center_q8 = (sum_index << 8) / black_count;
    // 中心位置 3.5 -> 896(Q8)，并保持输出尺度约为 [-56, 56]
    raw_error = (center_q8 - 896) / 16;
  }

  if (!filter_inited) {
    filtered_error_q8 = (raw_error << 8);
    filter_inited = 1;
  } else {
    int32_t target_q8 = (raw_error << 8);
    int32_t delta_q8 = target_q8 - filtered_error_q8;
    int32_t abs_delta_q8 = (delta_q8 >= 0) ? delta_q8 : -delta_q8;

    // 自适应滤波：大变化快跟随，小变化慢平滑，减少相位滞后
    if (abs_delta_q8 >= (10 << 8)) {
      // 变化很大（例如弯道/切线），直接快跟随
      filtered_error_q8 += (delta_q8 >> 1); // /2
    } else {
      // 小变化（主要是抖动噪声）慢速平滑
      filtered_error_q8 += (delta_q8 >> 3); // /8
    }
  }

  return (int)(filtered_error_q8 >> 8);
}

/**
 * @brief 获取灰度传感器的模拟量误差
 *
 * @return int 模拟量误差，具体变化量范围以黑白场校准值有关
 */
int GRAY_GetAnalogError() {
  Get_Normalize_For_User(&gray, Normal); // 获取归一化数据
  int64_t result_1 = Normal[0] + Normal[1] + Normal[2] + Normal[3];
  int64_t result_2 = Normal[4] + Normal[5] + Normal[6] + Normal[7];
  Normal_ERROR = result_1 - result_2; // 总强度（可选输出）
  // sprintf((char *)rx_buff, "AnalogError %d\r\n", result_1 - result_2);
  // USART1_SendString((char *)rx_buff);
  return Normal_ERROR;
}

/***********************************************自动校准的初始化
 * ****************************************/

int Gray_Init(dev_arg_t avg) {
  // 初始化传感器
  No_MCU_Ganv_Sensor_Init(&gray, white, black);
  return 0;
}

volatile bool gCheckADC; // ADC采集成功标志位

unsigned int adc_getValue(void) {
  unsigned int gAdcResult = 0;

  // 软件触发ADC开始转换
  DL_ADC12_startConversion(ADC12_0_INST);
  // 如果当前状态为正在转换中则等待转换结束
  while (false == gCheckADC) {
  }
  // 获取数据
  gAdcResult = DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_0);

  // 清除标志位
  gCheckADC = false;

  return gAdcResult;
}

void ADC12_0_INST_IRQHandler(void) {
  // 查询并清除ADC中断
  switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
  // 检查是否完成数据采集
  case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
    gCheckADC = true; // 将标志位置1
    break;
  default:
    break;
  }
}
