#include <df_key.h>
#include <ti_msp_dl_config.h>
#include <df_iic.h>

bool Key_SET_Read(Kt *key) {
  return (DL_GPIO_readPins(KEY_1_PORT, KEY_1_SET_PIN) == 0);
}

void led_on() {
    DL_GPIO_setPins(LED_PORT, LED_RED_PIN); // 点亮LED
}

void led_off() {
    DL_GPIO_clearPins(LED_PORT, LED_RED_PIN); // 熄灭LED
}
