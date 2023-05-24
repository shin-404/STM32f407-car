#include "sensor.h"

data_car_t car;

void all_sensor_init(void)
{
  WIT_reset_sensor(&WIT_sensor);
  WIT_init();
  encoder_init();

  /*band data*/
  car.six_axis = &WIT_sensor;
  car.hall_left = &hall_left;
  car.hall_right = &hall_right;

}
