//
// Created by JZH on 2021/2/1.
//

#include "iic.h"

#define I2CSPEED 50

void IIC2_Delay() {
    volatile int v;
    int i;
    for (i = 0; i < I2CSPEED / 2; ++i) {
        v;
    }
}

GPIO_TypeDef *IIC2_SDA_Port = GPIOB ;
uint16_t IIC2_SDA_Pin = GPIO_PIN_7;

GPIO_TypeDef *IIC2_SCL_Port =GPIOB;
uint16_t IIC2_SCL_Pin = GPIO_PIN_6;

static void IIC2_SDA(int status) {
    HAL_GPIO_WritePin(IIC2_SDA_Port, IIC2_SDA_Pin, status);
}
static void IIC2_SCL(int status) {
    HAL_GPIO_WritePin(IIC2_SCL_Port, IIC2_SCL_Pin, status);
}
void IIC2_SDA_HIGH() {
    IIC2_SDA(HIGH);
}

void IIC2_SDA_LOW() {
    IIC2_SDA(LOW);
}

void IIC2_SCL_HIGH() {
    IIC2_SCL(HIGH);
}

void IIC2_SCL_LOW() {
    IIC2_SCL(LOW);
}


void IIC2_SDA_IN() {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = IIC2_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(IIC2_SDA_Port, &GPIO_InitStruct);
}

void IIC2_SDA_OUT() {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = IIC2_SDA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(IIC2_SDA_Port, &GPIO_InitStruct);
}























void IIC2_Start() {
    IIC2_SDA_HIGH();
    IIC2_SCL_HIGH();
    IIC2_Delay();
    IIC2_SDA_LOW();
    IIC2_Delay();
    IIC2_SCL_LOW();
}

void IIC2_End() {
    IIC2_SCL_LOW();
    IIC2_SDA_LOW();
    IIC2_Delay();
    IIC2_SCL_HIGH();
    IIC2_Delay();
    IIC2_SDA_HIGH();
}

void IIC2_WR_BIT(int status) {
    IIC2_SDA(status);
    IIC2_Delay();
    IIC2_SCL_HIGH();
    IIC2_Delay();
    IIC2_SCL_LOW();
    IIC2_Delay();
}

//need SDA_IN
uint8_t IIC2_RD_BIT() {
    IIC2_SCL_HIGH();
    uint8_t status = HAL_GPIO_ReadPin(IIC2_SDA_Port, IIC2_SDA_Pin);
    IIC2_Delay();
    IIC2_SCL_LOW();
    IIC2_Delay();
    return status;
}

int IIC2_Wait() {
    uint8_t time = 0;
    IIC2_SDA_HIGH();
    IIC2_SDA_IN();
    IIC2_Delay();
    IIC2_SCL_HIGH();
    IIC2_Delay();
    while (HAL_GPIO_ReadPin(IIC2_SDA_Port, IIC2_SDA_Pin)) {
        time++;
        if (time > 250) {
            IIC2_SCL_LOW();
            IIC2_SDA_OUT();
            IIC2_End();
            return 0;
        }
    }
    IIC2_SCL_LOW();
    IIC2_SDA_OUT();
    return 1;
}

void IIC2_Write(uint8_t v) {
    for (int i = 0; i < 8; i++) {
        IIC2_WR_BIT((v & (0x80)) ? HIGH : LOW);
        v <<= 1;
    }
    IIC2_Wait();
}

int IIC2_Read(int NACK) {
    uint8_t v = 0;
    IIC2_SDA_IN();
    for (int i = 0; i < 8; i++) {
        v = (v << 1u) | IIC2_RD_BIT();
    }
    IIC2_SDA_OUT();
    IIC2_WR_BIT(NACK);
    return v;
}

void initIIC2(GPIO_TypeDef *SDA, uint16_t SDA_Pin_, GPIO_TypeDef *SCL, uint16_t SCL_Pin_) {
    IIC2_SDA_Port = SDA;
    IIC2_SDA_Pin = SDA_Pin_;
    IIC2_SCL_Port = SCL;
    IIC2_SCL_Pin = SCL_Pin_;
    IIC2_SDA_HIGH();
    IIC2_SCL_HIGH();
}

