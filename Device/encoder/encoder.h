#ifndef __ENCODER_H
#define __ENCODER_H

#include <stdint.h>

typedef struct{
    int32_t Count;
    int32_t Val;
} Encoder;

void GROUP1_IRQHandler_CallBack(void);
void Encoder_GetVal() ;


#endif
