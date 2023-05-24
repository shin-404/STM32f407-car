#ifndef CAR_V2_USART_SAFE_H
#define CAR_V2_USART_SAFE_H

#include "FreeRTOS.h"
#include "main.h"
#include "task.h"
#include "usart.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MAX_BUF 256

typedef struct {
    char Rxbuf[MAX_BUF];
    char is_recept;
    int Rx_buf_len;
    char temp;
} self_USART_t;

extern self_USART_t self_USART1;
extern self_USART_t self_USART2;

void print_USARTx(struct __UART_HandleTypeDef* USARTx, char *format, ...);

#endif //CAR_V2_USART_SAFE_H
