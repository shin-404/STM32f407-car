#include "usart_safe.h"

self_USART_t self_USART1;
self_USART_t self_USART2;

static int inHandlerMode (void) //若在中断中__get_IPSR()返回1，否则返回0
{
  return __get_IPSR();
}

void print_USARTx(struct __UART_HandleTypeDef* USARTx, char *format, ...)
{
  char buf[64];
  if(inHandlerMode() != 0)
  {
    taskDISABLE_INTERRUPTS();
  }
  else
  {
    while(HAL_UART_GetState(USARTx) == HAL_UART_STATE_BUSY_TX)//若串口忙则挂起此任务
      taskYIELD();
  }
  va_list ap;
  va_start(ap, format);
  vsprintf(buf, format, ap);

  if(USARTx == &huart2)
    HAL_UART_Transmit(USARTx, (uint8_t *)buf, 5, 100);
  else
    HAL_UART_Transmit(USARTx, (uint8_t *)buf, strlen(buf), 100);

  va_end(ap);
  if(inHandlerMode() != 0)
    taskENABLE_INTERRUPTS();
}

