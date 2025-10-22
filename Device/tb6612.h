//
// Created by 34575 on 25-6-8.
//

#ifndef TB6612_H
#define TB6612_H
#include <ti_msp_dl_config.h>

// 方向控制
#define RightForward                                                           \
  do {                                                                         \
    DL_GPIO_setPins(TB6612_AIN_1_PORT, TB6612_AIN_1_PIN);                      \
    DL_GPIO_clearPins(TB6612_AIN_2_PORT, TB6612_AIN_2_PIN);                    \
  } while (0)
#define RightBackward                                                          \
  do {                                                                         \
    DL_GPIO_clearPins(TB6612_AIN_1_PORT, TB6612_AIN_1_PIN);                    \
    DL_GPIO_setPins(TB6612_AIN_2_PORT, TB6612_AIN_2_PIN);                      \
  } while (0)
#define LeftForward                                                            \
  do {                                                                         \
    DL_GPIO_setPins(TB6612_BIN_1_PORT, TB6612_BIN_1_PIN);                    \
    DL_GPIO_clearPins(TB6612_BIN_2_PORT, TB6612_BIN_2_PIN);                      \
  } while (0)
#define LeftBackward                                                           \
  do {                                                                         \
    DL_GPIO_clearPins(TB6612_BIN_1_PORT, TB6612_BIN_1_PIN);                      \
    DL_GPIO_setPins(TB6612_BIN_2_PORT, TB6612_BIN_2_PIN);                    \
  } while (0)
#define AllForward                                                             \
  do {                                                                         \
    LeftForward;                                                               \
    RightForward;                                                              \
  } while (0)
#define AllBackward                                                            \
  do {                                                                         \
    LeftBackward;                                                              \
    RightBackward;                                                             \
  } while (0)
#define AllStop                                                                \
  do {                                                                         \
    DL_GPIO_clearPins(TB6612_AIN_1_PORT, TB6612_AIN_1_PIN);                    \
    DL_GPIO_clearPins(TB6612_AIN_2_PORT, TB6612_AIN_2_PIN);                    \
    DL_GPIO_clearPins(TB6612_BIN_1_PORT, TB6612_BIN_1_PIN);                    \
    DL_GPIO_clearPins(TB6612_BIN_2_PORT, TB6612_BIN_2_PIN);                    \
  } while (0)

// 速度控制
#define PWMA(x)                                                                \
  do {                                                                         \
    if (x >= 0) {                                                              \
      RightForward;                                                            \
      DL_TimerG_setCaptureCompareValue(PWM_0_INST, x, GPIO_PWM_0_C0_IDX);      \
    } else {                                                                   \
      RightBackward;                                                           \
      DL_TimerG_setCaptureCompareValue(PWM_0_INST, -x, GPIO_PWM_0_C0_IDX);     \
    }                                                                          \
  } while (0)

#define PWMB(x)                                                                \
  do {                                                                         \
    if (x >= 0) {                                                              \
      LeftForward;                                                             \
      DL_TimerG_setCaptureCompareValue(PWM_1_INST, x, GPIO_PWM_1_C0_IDX);      \
    } else {                                                                   \
      LeftBackward;                                                            \
      DL_TimerG_setCaptureCompareValue(PWM_1_INST, -x, GPIO_PWM_1_C0_IDX);     \
    }                                                                          \
  } while (0)

#endif // TB6612_H
