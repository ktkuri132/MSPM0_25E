#include "encoder.h"
#include "dev_model_core.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"
#include <ti/driverlib/m0p/dl_interrupt.h>
#include <driver.h>

Encoder Eleft;
Encoder Eright;

int encoder_init(dev_arg_t arg) {
    (void)arg; // 忽略参数
  // 编码器引脚外部中断
  NVIC_EnableIRQ(GPIOB_INT_IRQn);
  return 0; // 返回0表示成功
}

void GROUP1_IRQHandler_CallBack(void) // 中断服务函数
{
  uint32_t gpioB;
  /**********************编码器读取***********************/
  gpioB = DL_GPIO_getEnabledInterruptStatus(
      GPIOB, EnconderA_PIN1_PIN | EnconderA_PIN2_PIN | EnconderB_PIN3_PIN |
                 EnconderB_PIN4_PIN);
  if ((gpioB & EnconderA_PIN1_PIN) == EnconderA_PIN1_PIN) {
    // Pin0上升沿
    if (!DL_GPIO_readPins(GPIOB, EnconderA_PIN2_PIN)) // P1为高电平
    {
      Eleft.Count--;
    } else // P1为低电平
    {
      Eleft.Count++;
    }
  } else if ((gpioB & EnconderA_PIN2_PIN) == EnconderA_PIN2_PIN) {
    // Pin1上升沿
    if (!DL_GPIO_readPins(GPIOB, EnconderA_PIN1_PIN)) // P0为高电
    {
      Eleft.Count++;
    } else // P1为低电平
    {
      Eleft.Count--;
    }
  }

  if ((gpioB & EnconderB_PIN3_PIN) != 0) {
    if (!DL_GPIO_readPins(GPIOB, EnconderB_PIN4_PIN)) {
      Eright.Count++;
    } else {
      Eright.Count--;
    }
  } else if ((gpioB & EnconderB_PIN4_PIN) != 0) {
    if (!DL_GPIO_readPins(GPIOB, EnconderB_PIN3_PIN)) {
      Eright.Count--;
    } else {
      Eright.Count++;
    }
  }
  DL_GPIO_clearInterruptStatus(GPIOB, EnconderA_PIN1_PIN | EnconderA_PIN2_PIN |
                                          EnconderB_PIN3_PIN |
                                          EnconderB_PIN4_PIN);
}


void Encoder_GetVal() {
    Eleft.Val = Eleft.Count;
    Eright.Val = Eright.Count;

    Eleft.Count = 0;
    Eright.Count = 0;
}