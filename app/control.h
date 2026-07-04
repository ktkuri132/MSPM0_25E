#ifndef __CONTROL_H
#define __CONTROL_H

#include <stdint.h>
#include <stdio.h>

#include "cmsis_gcc.h"

typedef struct systrl systrl;  // 前向声明systrl结构体

typedef union {
	struct {
		uint8_t PID_speed_left_Controlor : 1;	// 左轮速度PID控制器标志位
		uint8_t PID_speed_right_Controlor : 1;	// 右轮速度PID控制器标志位
		uint8_t PID_position_Controlor : 1;		// 位置PID控制器标志位
	};
	uint8_t all_flags;	// 用于一次性设置或清除所有标志位
} PID_Controlor_Switch;

struct systrl {
	PID_Controlor_Switch PID_Controlor_Switch;					   // PID控制器开关状态
	void (*ENABLE_PID_speed_left_Controlor)(systrl* controlor);	   // 启用左轮速度PID控制器函数指针
	void (*DISABLE_PID_speed_left_Controlor)(systrl* controlor);   // 禁用左轮速度PID控制器函数指针
	void (*ENABLE_PID_speed_right_Controlor)(systrl* controlor);   // 启用右轮速度PID控制器函数指针
	void (*DISABLE_PID_speed_right_Controlor)(systrl* controlor);  // 禁用右轮速度PID控制器函数指针
	void (*ENABLE_PID_position_Controlor)(systrl* controlor);	   // 启用位置PID控制器函数指针
	void (*DISABLE_PID_position_Controlor)(systrl* controlor);	   // 禁用位置PID控制器函数指针
	void (*ENABLE_ALL_PID_Controlors)(systrl* controlor);		   // 启用所有PID控制器函数指针
	void (*DISABLE_ALL_PID_Controlors)(systrl* controlor);		   // 禁用所有PID控制器函数指针
};

__STATIC_INLINE void ENABLE_PID_speed_left_Controlor(systrl* controlor) {
	controlor->PID_Controlor_Switch.PID_speed_left_Controlor = 1;
}

__STATIC_INLINE void DISABLE_PID_speed_left_Controlor(systrl* controlor) {
	controlor->PID_Controlor_Switch.PID_speed_left_Controlor = 0;
}

__STATIC_INLINE void ENABLE_PID_speed_right_Controlor(systrl* controlor) {
	controlor->PID_Controlor_Switch.PID_speed_right_Controlor = 1;
}

__STATIC_INLINE void DISABLE_PID_speed_right_Controlor(systrl* controlor) {
	controlor->PID_Controlor_Switch.PID_speed_right_Controlor = 0;
}

__STATIC_INLINE void ENABLE_PID_position_Controlor(systrl* controlor) {
	controlor->PID_Controlor_Switch.PID_position_Controlor = 1;
}

__STATIC_INLINE void DISABLE_PID_position_Controlor(systrl* controlor) {
	controlor->PID_Controlor_Switch.PID_position_Controlor = 0;
}

__STATIC_INLINE void ENABLE_ALL_PID_Controlors(systrl* controlor) {
	controlor->PID_Controlor_Switch.all_flags = 0x07;  // 设置所有控制器标志位
}

__STATIC_INLINE void DISABLE_ALL_PID_Controlors(systrl* controlor) {
	controlor->PID_Controlor_Switch.all_flags = 0x00;  // 清除所有控制器标志位
}

typedef struct Move_Control Move_Control;  // 前向声明Move_Control结构体

typedef enum {
	LEFT_CORNER = 1,
	RIGHT_CORNER = 2,
	STATUS_1 = 0x11,
	STATUS_2 = 0x12,
	STATUS_3 = 0x13,
	STATUS_4 = 0x14,
	STATUS_5 = 0x15,
	STATUS_6 = 0x16,
	STATUS_7 = 0x17,
} Move_Control_statue_encode;

typedef union {
	struct {
		uint8_t Left_Corner : 1;	// 左转弯标志位
		uint8_t Right_Corner : 1;	// 右转弯标志位
		uint8_t Straight : 1;		// 直行标志位
		uint8_t Turn_Ready : 1;		// 转向预备标志位
		uint8_t Turning : 1;		// 转向中标志位
		uint8_t Turn_started : 1;	// 转向已开始标志位
		uint8_t Turn_finished : 1;	// 转向已完成标志位
		uint8_t Inline : 1;			// 环境标志位,1-巡线 ,0-完全脱离黑线
	};
	uint8_t all_flags;	// 用于一次性设置或清除所有标志位
} Move_Control_Status;


struct Move_Control {
	Move_Control_Status status;					// 运动控制状态
	Move_Control_statue_encode current_state;	// 当前状态编码
	uint8_t corner;								// 当前检测到的转弯方向,0-无转弯,1-左转,2-右转
	int corner_count;							// 连续检测到转弯的计数器,绝对值表示连续转弯次数,正数表示左转,负数表示右转
	void (*Update)(Move_Control* controlor);	// 运动控制更新函数指针
	uint8_t (*Judge)(Move_Control* controlor);	// 左右转弯判断函数指针
};

// 前向声明，供内联函数使用
extern uint8_t Get_digtal(void);

__STATIC_INLINE int is_left_corner_pattern(uint8_t digital) {
	// 左直角常见码型（黑=0, 白=1）
	return (digital == 0xC0) || (digital == 0xE0) || (digital == 0xF0);
}

__STATIC_INLINE int is_right_corner_pattern(uint8_t digital) {
	// 右直角码型为左侧镜像
	return (digital == 0x1F) || (digital == 0xFF) || (digital == 0x0F) || (digital == 0x07);
}

__STATIC_INLINE int is_middle_pattern(uint8_t digital) {
	// 直行码型为中间黑线
	return (digital == 0x7E) || (digital == 0x3C) || (digital == 0x18);
}

__STATIC_INLINE uint8_t LR_Judge(Move_Control* controlor) {
	(void)controlor;

	uint8_t digital = Get_digtal();
	uint8_t dir = 0;

	// 全白：未检测到黑线
	if (digital == 0xFF) {
		controlor->status.Inline = 0;  // 设置完全脱离黑线标志
		return 0;
	}
	controlor->status.Inline = 1;  // 清除完全脱离黑线标志

	// 纯数字量模式识别
	if (is_left_corner_pattern(digital)) {
		dir = LEFT_CORNER;
	} else if (is_right_corner_pattern(digital)) {
		dir = RIGHT_CORNER;
	}
	return dir;
}

__STATIC_INLINE void move_control_update(Move_Control* controlor) {
	controlor->corner = controlor->Judge(controlor);
	if (!controlor->status.Turning && !controlor->status.Turn_started) {  // 未处于转向状态,正常状态检测,默认巡线模式
		if (controlor->status.Inline && controlor->corner) {			  // 在线且检测到转弯
			controlor->status.Left_Corner = (controlor->corner == LEFT_CORNER);
			controlor->status.Right_Corner = (controlor->corner == RIGHT_CORNER);
			controlor->status.Turn_Ready = 1;
			controlor->current_state = STATUS_1;
		} else if (controlor->status.Inline && !controlor->corner) {  // 在线上但未检测到转弯,正常巡线
			if (!controlor->status.Turn_Ready) {						  // 当从转角向前滑行的时候,会有一段过渡期,此时会短暂的在线上.
				controlor->status.Left_Corner = 0;
				controlor->status.Right_Corner = 0;
				controlor->status.Straight = 1;
				controlor->current_state = STATUS_2;
			}
		} else if (!controlor->status.Inline && !controlor->corner) {  // 出线了，但未检测到转弯,完全脱离黑线,此时检查是否有转向预备
			if (controlor->status.Turn_Ready) {						   // 如果之前有转向预备，说明是正常转向检测后出线，进入转向中状态
				controlor->status.Turn_Ready = 0;					   // 清除转向预备标志
				controlor->status.Turning = 1;						   // 设置转向中标志
				controlor->status.Turn_started = 1;					   // 设置转向已开始标志
				controlor->status.Straight = 0;						   // 清除直行标志
				controlor->current_state = STATUS_3;
			} else {							  //* 否则说明是在出线前没有检测到转弯，可能是误判或特殊情况，直接重置状态
				controlor->status.all_flags = 0;  // 清除所有状态
				controlor->current_state = STATUS_4;
			}
		} else if (!controlor->status.Inline && controlor->corner) {  //* 出线了，但检测到转弯,此时肯定出现异常状态
			controlor->status.Left_Corner = 0;
			controlor->status.Right_Corner = 0;
			controlor->status.Straight = 0;
			controlor->current_state = STATUS_5;
		}
	} else if (controlor->status.Turning && controlor->status.Turn_started) {
		if (controlor->status.Inline) {		// 转向中但又在线上了,说明转向过程中又回到了线上
			controlor->status.Turning = 0;	// 清除转向中标志
			controlor->corner_count++;
		}
	} else if (!controlor->status.Turning && controlor->status.Turn_started) {	// 转向已开始但不在转向中,说明转向完成阶段
		controlor->status.Turn_started = 0;										// 清除转向已开始标志
		controlor->status.Turn_finished = 1;									// 设置转向已完成标志
		controlor->current_state = STATUS_6;
	}
	// 转向完成后重置状态,准备下一次转向检测
	if (controlor->status.Turn_finished) {	// 转向完成后,重置状态,准备下一次转向检测
		controlor->status.Left_Corner = 0;
		controlor->status.Right_Corner = 0;
		controlor->status.Turn_finished = 0;
		controlor->current_state = STATUS_7;
	}
}

#endif