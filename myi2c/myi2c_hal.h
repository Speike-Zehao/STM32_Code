//
// Created by SimilarTriangles on 2022/4/14.
//

#ifndef I2C_TEST3_MYI2C_HAL_H
#define I2C_TEST3_MYI2C_HAL_H

#endif //I2C_TEST3_MYI2C_HAL_H

#include "i2c.h"
#include "stdio.h"
#include "stdint.h"

struct command{
    uint8_t cmdaddr;//i2c设备，指令子寄存器地址
    uint8_t parameters[16];//指令内容
    uint16_t para_length;//指令内容长度
};

void iic_write(I2C_HandleTypeDef *hi2c,uint8_t devaddr_7bit,struct command *cmd);
void iic_read(I2C_HandleTypeDef *hi2c,uint8_t devaddr_7bit,uint8_t iic_data[],uint16_t data_length);