#include "encoder.h"

encoder hall_left;
encoder hall_right;

void encoder_reset(encoder* hall)
{
  hall->enc1 = 0;
  hall->pre_enc1 = 0;
  hall->enc2 = 0;
  hall->direction = 0;
  hall->counter = 0;
  hall->enc = 0;
  hall->htimx = NULL;
}

void encoder_init(void)
{
  encoder_reset(&hall_left);
  encoder_reset(&hall_right);
  hall_right.htimx = &htim3;
  hall_left.htimx = &htim4;
}

void encoder_update(encoder hall)
{
  hall.direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(hall.htimx);
  hall.enc1 = (uint32_t)(__HAL_TIM_GET_COUNTER(hall.htimx));

  if((hall.direction == 0) && (hall.enc1 < hall.pre_enc1))
    hall.enc2++;

  if((hall.direction == 1) && (hall.enc1 > hall.pre_enc1))
    hall.enc2--;

  hall.pre_enc1 = hall.enc1;
  hall.enc = hall.enc2<<16 | hall.enc1;
}

void start_encoder_debug(void const * argument)
{
  for(;;)
  {
    encoder_update(hall_left);
    encoder_update(hall_right);
    osDelay(1);
  }
}