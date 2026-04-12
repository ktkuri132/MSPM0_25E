#include <driver.h>
#include <shell.h>
#include <stddef.h>

#include "main.h"
#include "shell_style.h"

void SysTick_Handler(void) {
	sys_runtimer(&sys_runtime);
	Task_tick(&gray);
	Key_Tick(&Key_SET_Handler);
	if (sys_runtime.count % 10 == 0)  // 每10ms执行一次速度计算
	{
		Encoder_GetVal();
	}
}

void TIMER_0_INST_IRQHandler() {
	switch (DL_TimerA_getPendingInterrupt(TIMER_0_INST)) {
	case DL_TIMERA_IIDX_ZERO:
		Control();
		break;
	default:
		break;
	}
}

void UART_0_IRQHandler_CallBack() {
	if (Shell.Data_Receive != NULL) {
		BIE_UART(NULL, &Shell_Sysfpoint, &Shell, env_vars, &Device_info);
	}
}

void GROUP1_IRQHandler(void) {
	/* GPIOB: 编码器 + KEY_SET */
	uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(
		GPIOB, EnconderA_PIN1_PIN | EnconderA_PIN2_PIN | EnconderB_PIN3_PIN | EnconderB_PIN4_PIN | KEY_1_SET_PIN
	);

	if (gpioB & (EnconderA_PIN1_PIN | EnconderA_PIN2_PIN | EnconderB_PIN3_PIN |
				 EnconderB_PIN4_PIN)) {
		GROUP1_IRQHandler_CallBack();
	}

	if (gpioB & KEY_1_SET_PIN) {
		Key_IRQHandler(&Key_SET_Handler, &Key_SET);
		DL_GPIO_clearInterruptStatus(GPIOB, KEY_1_SET_PIN);
	}

	DL_GPIO_clearInterruptStatus(GPIOA, KEY_2_UP_PIN | KEY_2_DOWN_PIN | KEY_2_RETURN_PIN | KEY_2_ESC_PIN);
}