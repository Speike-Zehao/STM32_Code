//
// Created by SimilarTriangles on 2022/4/14.
//

#include "myi2c_hal.h"

void iic_write(I2C_HandleTypeDef *hi2c,uint8_t devaddr_7bit,struct command *cmd){
    HAL_I2C_Mem_Write(hi2c,devaddr_7bit<<1,cmd->cmdaddr,1,cmd->parameters,cmd->para_length,100);
}

void iic_read(I2C_HandleTypeDef *hi2c,uint8_t devaddr_7bit,uint8_t iic_data[],uint16_t data_length){
    HAL_I2C_Master_Receive(hi2c,(devaddr_7bit<<1)+1,iic_data,data_length,100);
}
