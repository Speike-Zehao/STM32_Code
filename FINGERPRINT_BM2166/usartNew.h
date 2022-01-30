//
// Created by Speike on 2022/1/14.
//

#ifndef USART1000_USARTNEW_H
#define USART1000_USARTNEW_H

#endif //USART1000_USARTNEW_H

#include "usart.h"

#define REC_LENGTH 400

void FINGER_UART_Start_IT(UART_HandleTypeDef huart,uint16_t length_of_data);
void FINGER_Callback(UART_HandleTypeDef huart);