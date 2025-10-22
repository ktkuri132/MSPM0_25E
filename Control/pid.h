#ifndef __PID__H
#define __PID__H

#include <math.h>
#include <stdint.h>



typedef struct PID_TypeDef {
    /* function  */
    void (*PID_Update)(struct PID_TypeDef *, float);
    /* data */
    float error;
    float last_error;
    float integral;
    float derivative;

    float target;
    float current;
    // 积分限幅
    float max_integral;
    float output;
    // 输出限幅
    float max_output;
    float min_output;
    float Kp;
    float Ki;
    float Kd;

} PID;

void PID_for_speed(PID *pid,float speed);

#endif
