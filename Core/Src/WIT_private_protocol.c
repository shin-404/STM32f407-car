#include "WIT_private_protocol.h"

WIT_sensor_t WIT_sensor;

void WIT_reset_sensor(WIT_sensor_t* sensor)
{
  sensor->angle.x = 0;
  sensor->angle.y = 0;
  sensor->angle.z = 0;
  sensor->gyro.x = 0;
  sensor->gyro.y = 0;
  sensor->gyro.z = 0;
  sensor->acc.x = 0;
  sensor->acc.y = 0;
  sensor->acc.z = 0;
}

void WIT_init(void)
{
  WIT_cmd(WIT_unlock);
  HAL_Delay(10);
  WIT_cmd(WIT_ACCCALSW);
  HAL_Delay(10);
  WIT_cmd(WIT_set_band_width_98Hz);
  HAL_Delay(10);
  WIT_cmd(WIT_set_algorithm_six_axis);
  HAL_Delay(10);
  WIT_cmd(WIT_set_output_ac_gyro_angle);
  HAL_Delay(10);
  WIT_cmd(WIT_save);
  HAL_Delay(10);
}

int WIT_check_sum(void)
{
  char SUMCRC = 0;

  if(WIT_data.Rxbuf[0] != 0x55)
    return 0;

  if(!WIT_data.is_recept || WIT_data.Rx_buf_len != 11)
    return 0;

  SUMCRC = WIT_data.Rxbuf[0]
            + WIT_data.Rxbuf[1]
              + WIT_data.Rxbuf[2]
                + WIT_data.Rxbuf[3]
                  + WIT_data.Rxbuf[4]
                    + WIT_data.Rxbuf[5]
                      + WIT_data.Rxbuf[6]
                        + WIT_data.Rxbuf[7]
                          + WIT_data.Rxbuf[8]
                            + WIT_data.Rxbuf[9];
  /********************************************/
  /*                                          */
  /*                                          */
  /*                                          */
  /*    |------------|                        */
  /*    |     |      |                        */
  /*    |_____|______|                        */
  /*    |     |      |                        */
  /*    |     |      |        /LOVELY HOUSE/  */
  /*    |------------|                        */
  /*                           |---------|    */
  /*                           |         |    */
  /*                           |         |    */
  /*                           |        0|    */
  /*                           |         |    */
  /*                           |         |    */
  /********************************************/

  if(SUMCRC != WIT_data.Rxbuf[10])
    return 0;

  return 1;
}

void WIT_analysis_data(void)
{
  HAL_NVIC_DisableIRQ(USART2_IRQn);
  switch(WIT_data.Rxbuf[1])
  {
    case 0x51:
      WIT_sensor.acc.x = 16 * 9.8 * WIT_caculate(WIT_data.Rxbuf[2], WIT_data.Rxbuf[3]);
      WIT_sensor.acc.y = 16 * 9.8 * WIT_caculate(WIT_data.Rxbuf[4], WIT_data.Rxbuf[5]);
      WIT_sensor.acc.z = 16 * 9.8 * WIT_caculate(WIT_data.Rxbuf[6], WIT_data.Rxbuf[7]);
      break;
    case 0x52:
      WIT_sensor.gyro.x = 2000 * WIT_caculate(WIT_data.Rxbuf[2], WIT_data.Rxbuf[3]);
      WIT_sensor.gyro.y = 2000 * WIT_caculate(WIT_data.Rxbuf[4], WIT_data.Rxbuf[5]);
      WIT_sensor.gyro.z = 2000 * WIT_caculate(WIT_data.Rxbuf[6], WIT_data.Rxbuf[7]);
      break;
    case 0x53:
      WIT_sensor.angle.x = 180 * WIT_caculate(WIT_data.Rxbuf[2], WIT_data.Rxbuf[3]);
      WIT_sensor.angle.y = 180 * WIT_caculate(WIT_data.Rxbuf[4], WIT_data.Rxbuf[5]);
      WIT_sensor.angle.z = 180 * WIT_caculate(WIT_data.Rxbuf[6], WIT_data.Rxbuf[7]);
      break;
  }
  print_USARTx(&huart1, "%f %f %f %f %f %f %f %f %f\n",
               WIT_sensor.acc.x, WIT_sensor.acc.y, WIT_sensor.acc.z,
               WIT_sensor.gyro.x, WIT_sensor.gyro.y, WIT_sensor.gyro.z,
               WIT_sensor.angle.x, WIT_sensor.angle.y, WIT_sensor.angle.z);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
}
