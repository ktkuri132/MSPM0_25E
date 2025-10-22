#include <main.h>
#include <pid.h>
#include <tb6612.h>

void Control(){
    pid_speed_left.PID_Update(&pid_speed_left, (float)Eleft.Val*1.0f);
    pid_speed_right.PID_Update(&pid_speed_right, (float)Eright.Val*1.0f);
    PWMA((int16_t)pid_speed_right.output);
    PWMB((int16_t)pid_speed_left.output);
}