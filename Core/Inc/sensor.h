#ifndef CAR_V2_SENSOR_H
#define CAR_V2_SENSOR_H

#include "WIT_private_protocol.h"
#include "encoder.h"

/*typedef*/
typedef struct {
  WIT_sensor_t* six_axis;
  encoder* hall_left;
  encoder* hall_right;
} data_car_t;

extern data_car_t car;

void all_sensor_init(void);

#endif //CAR_V2_SENSOR_H
