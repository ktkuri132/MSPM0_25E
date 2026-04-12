#include <pid.h>
#include <tb6612.h>

#include "main.h"

void Control() {
	// 速度环
	if (pid_switch.PID_Controlor_Switch.PID_speed_left_Controlor) {
		pid_speed_left.PID_Update(&pid_speed_left, (float)Eleft.Val * 1.0F);
	} else {
		pid_speed_left.output = 0;
	}
	if (pid_switch.PID_Controlor_Switch.PID_speed_right_Controlor) {
		pid_speed_right.PID_Update(&pid_speed_right, (float)Eright.Val * 1.0F);
	} else {
		pid_speed_right.output = 0;
	}

	// 方向环：只读取状态标志，不做传感器检测
	if (move_ctrl.status.Turning) {
		// 转向中：根据方向施加固定差速
		if (move_ctrl.status.Left_Corner) {
			led_on();
			PWMA((int16_t)(pid_turn.output));
			PWMB((int16_t)(-pid_turn.output));	// 左轮反转
		} else if (move_ctrl.status.Right_Corner) {
			led_on();
			PWMA((int16_t)(-pid_turn.output));	// 右轮反转
			PWMB((int16_t)(pid_turn.output));
		}
	} else {
		// 正常巡线：位置PID修正
		if (pid_switch.PID_Controlor_Switch.PID_position_Controlor) {
			pid_position.PID_Update(&pid_position, (float)GRAY_ERROR * 1.0F);
		} else {
			pid_position.output = 0;
		}
		PWMA((int16_t)(pid_speed_right.output - pid_position.output));
		PWMB((int16_t)(pid_speed_left.output + pid_position.output));
	}
}

int Start_when_Key_Pressed() {
	// 保留
	return 0;  // 按键未被按下，继续运行
}

/* 当完全脱离黑线时停止电机 */
void Stop_when_out_of_line(void) {
	if (!move_ctrl.status.Inline && !move_ctrl.status.Turning && !move_ctrl.status.Turn_started) {	// 在线上且不在转向状态，继续正常控制
		pid_switch.DISABLE_ALL_PID_Controlors(&pid_switch);
	}
}

int Stop_when_Key_Pressed() {
	// 保留
	return 0;  // 按键未被按下，继续运行
}
