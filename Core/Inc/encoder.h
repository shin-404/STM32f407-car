#ifndef CAR_V2_ENCODER_H
#define CAR_V2_ENCODER_H

#include "tim.h"
#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"

/*typedef*/
typedef struct
{
    int direction;
    int counter;
    int enc1;
    int pre_enc1;
    int enc2;
    int enc;
    TIM_HandleTypeDef* htimx;
} encoder;

extern encoder hall_left;
extern encoder hall_right;

void encoder_init(void);
void encoder_update(encoder hall);
void encoder_reset(encoder* hall);
void start_encoder_debug(void const * argument);

#endif //CAR_V2_ENCODER_H
