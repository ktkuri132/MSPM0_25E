#include <df_key.h>
#include <ti_msp_dl_config.h>

bool Key_SET_Read(Kt *key) {
  return (DL_GPIO_readPins(KEY_1_PORT, KEY_1_SET_PIN) == 0);
}

bool Key_UP_Read(Kt *key) {
  return (DL_GPIO_readPins(KEY_2_PORT, KEY_2_UP_PIN) == 0);
}

bool Key_DOWN_Read(Kt *key) {
  return (DL_GPIO_readPins(KEY_2_PORT, KEY_2_DOWN_PIN) == 0);
}

bool Key_RETURN_Read(Kt *key) {
  return (DL_GPIO_readPins(KEY_2_PORT, KEY_2_RETURN_PIN) == 0);
}

bool Key_ESC_Read(Kt *key) {
  return (DL_GPIO_readPins(KEY_2_PORT, KEY_2_ESC_PIN) == 0);
}

void led_on() {
    DL_GPIO_setPins(LED_PORT, LED_RED_PIN); // 点亮LED
}

void led_off() {
    DL_GPIO_clearPins(LED_PORT, LED_RED_PIN); // 熄灭LED
}
