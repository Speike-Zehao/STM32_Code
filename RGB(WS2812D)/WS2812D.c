//
// Created by Speike on 2021/2/23.
//

#include "WS2812D.h"
#include "gpio.h"

///RGB1定义--------------------------------------------------------------
#define RGB1_PORT GPIOA
#define RGB2_PORT GPIOA
uint16_t RGB1_PIN = RGB1_OUT_Pin;
uint16_t RGB2_PIN = RGB2_OUT_Pin;
///---------------------------------------------------------------------

///一个Nop函数所需时间为1/50 us或20ns---------------

static void T0H(){
    HAL_GPIO_WritePin(RGB1_PORT,RGB1_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(RGB2_PORT,RGB2_PIN,GPIO_PIN_SET);
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();
    //共计 240~340ns
}

static void T0L(){
    HAL_GPIO_WritePin(RGB1_PORT,RGB1_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RGB2_PORT,RGB2_PIN,GPIO_PIN_RESET);
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();
    //共计 860~960ns
}

static void T1H(){
    HAL_GPIO_WritePin(RGB1_PORT,RGB1_PIN,GPIO_PIN_SET);
    HAL_GPIO_WritePin(RGB2_PORT,RGB2_PIN,GPIO_PIN_SET);
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();__NOP();
}
static void T1L(){
    HAL_GPIO_WritePin(RGB1_PORT,RGB1_PIN,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RGB2_PORT,RGB2_PIN,GPIO_PIN_RESET);
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
    __NOP();
}

static void T0(){
    T0H();
    T0L();
}
static void T1(){
    T1H();
    T1L();
}

static void delay_us(uint32_t us){
    uint32_t tickstart = HAL_GetTick();
    uint32_t wait = us;

    HAL_RCC_GetHCLKFreq()/1000000;// 1us中断一次，即HAL_Delay函数延时基准为1us
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000000);

    /* Add a freq to guarantee minimum wait */
    if (wait < HAL_MAX_DELAY)
    {
        wait += (uint32_t)(uwTickFreq);
    }

    while((HAL_GetTick() - tickstart) < wait)
    {
    }

    HAL_RCC_GetHCLKFreq()/1000;
}

void reset(){
    delay_us(350);
}


///---------------------------------------------------------------------

static void RGB_WR_BYTE(uint8_t value){
    for (int i = 0; i < 8; ++i) {
        if (value&0x80) T1();
        else T0();
        value <<= 1;
    }
}

void RGB_WR_PIXEL(uint8_t green,uint8_t red,uint8_t blue)
{
    RGB_WR_BYTE(green);
    RGB_WR_BYTE(red);
    RGB_WR_BYTE(blue);
}