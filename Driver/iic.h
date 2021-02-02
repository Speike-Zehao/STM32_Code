//
// Created by JZH on 2021/2/1.
//

#ifndef OLED2_IIC_H
#define OLED2_IIC_H

#endif //OLED2_IIC_H
#ifndef __IIC_H
#define __IIC_H

#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

#include "gpio.h"

#define HIGH GPIO_PIN_SET

#define LOW GPIO_PIN_RESET

void initIIC2(GPIO_TypeDef*,uint16_t,GPIO_TypeDef*,uint16_t);
int IIC2_Read(int);
void IIC2_Write(uint8_t);
int IIC2_Wait();
void IIC2_Start();
void IIC2_End();
void IIC2_Delay();




#ifdef __cplusplus
}
#endif

#endif //MYFIRST_II_H
