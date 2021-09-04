//
// Created by Speike on 2021/9/4.
//

#include "Servo.h"
#include "tim.h"
#define MAX_ANGLE 250
#define MIN_ANGLE 50
#define DEFAULT_ANGLE 150


void servo_Init(){
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,DEFAULT_ANGLE);
}

void Rotate(uint16_t period_ms){
    uint16_t delay_time_ms = period_ms/360;//Period time over 360 gaps = how much time should CPU wait each movement of servo for it to move to specific positon.

    for (int i = DEFAULT_ANGLE; i < MAX_ANGLE; ++i) {
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,i);
        HAL_Delay(delay_time_ms);
    }
    for (int i = MAX_ANGLE; i > MIN_ANGLE; --i) {
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,i);
        HAL_Delay(delay_time_ms);
    }
    for (int i = 0; i < DEFAULT_ANGLE; ++i) {
        __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,i);
        HAL_Delay(delay_time_ms);
    }
}