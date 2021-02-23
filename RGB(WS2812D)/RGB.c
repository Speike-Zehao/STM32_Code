//
// Created by Speike on 2021/2/23.
//

#include "RGB.h"
#include "WS2812D.h"
#define amount 60
#define DELAY_LEVEL 1

static uint8_t green,red,blue;

void RGB_BREATH(){
    green=0;
    red=255;
    blue=0;
    //正片开始
    for (int i = 0; i < 255; ++i) {
        for (int j = 0; j < amount; ++j) {
            RGB_WR_PIXEL(green,red,blue);
        }
        green++;
        red--;
        HAL_Delay(DELAY_LEVEL);
    }

    for (int i = 0; i < 255; ++i) {
        for (int j = 0; j < amount; ++j) {
            RGB_WR_PIXEL(green,red,blue);
        }
        green--;
        blue++;
        HAL_Delay(DELAY_LEVEL);
    }

    for (int i = 0; i < 255; ++i) {
        for (int j = 0; j < amount; ++j) {
            RGB_WR_PIXEL(green,red,blue);
        }
        blue--;
        red++;
        HAL_Delay(DELAY_LEVEL);
    }
    reset();
}