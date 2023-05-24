#ifndef CAR_V2_WIT_PRIVATE_PROTOCOL_H
#define CAR_V2_WIT_PRIVATE_PROTOCOL_H

/*WIT commands*/
static char WIT_unlock[5] = {
  0xFF,0xAA,0x69,0x88,0xB5
};

static char WIT_ACCCALSW[5] = {
  0xFF,0xAA,0x01,0x01,0x00
};

static char WIT_reset_yaw[5] = {
  0xFF,0xAA,0x01,0x04,0x00
};

static char WIT_sleep[5] = {
  0xFF,0xAA,0x22,0x01,0x00
};

static char WIT_set_band_width_98Hz[5] = {
  0xFF,0xAA,0x1F,0x02,0x00
};

static char WIT_set_algorithm_six_axis[5] = {
  0xFF,0xAA,0x24,0x01,0x00
};

static char WIT_set_output_ac_gyro_angle[5] = {
  0xFF,0xAA,0x02,0x0E,0x00
};

static char WIT_save[5] = {
  0xFF,0xAA,0x00,0x00,0x00
};

static char WIT_read_acc[5] = {
  0xFF,0xAA,0x27,0x34,0x00
};

static char WIT_read_gyro[5] = {
  0xFF,0xAA,0x27,0x37,0x00
};

static char WIT_read_angle[5] = {
  0xFF,0xAA,0x27,0x3d,0x00
};

/*include*/
#include "usart_safe.h"

/*define*/
#define WIT_cmd(cmd) print_USARTx(&huart2, cmd)
#define WIT_caculate(Low, High) (1.0 * (short)(((short)High<<8)|Low) / 32768)
#define WIT_data self_USART2

/*typedef*/
typedef struct {
    float x;
    float y;
    float z;
} WIT_direction_t;

typedef struct {
    WIT_direction_t angle;
    WIT_direction_t gyro;
    WIT_direction_t acc;
} WIT_sensor_t;

extern WIT_sensor_t WIT_sensor;

void WIT_init(void);
int WIT_check_sum(void);
void WIT_analysis_data(void);
void WIT_reset_sensor(WIT_sensor_t* sensor);

#endif //CAR_V2_WIT_PRIVATE_PROTOCOL_H
