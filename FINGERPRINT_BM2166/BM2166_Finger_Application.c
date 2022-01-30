//
// Created by Speike on 2022/1/30.
//

#include "BM2166_Finger_Application.h"

//初始化指纹模块
uint8_t Finger_Init(){


    uint8_t response;
    do {
        printf("Connecting BM2166 Sensor...\r\n");
        response = Handshake();
        if (response==0xff){
            printf("Communication Error.\n");
            return 0;
        }

    } while (response!=0);
    printf("Connected!\r\n");
    return 1;
}

//在现有指纹库中搜索
uint8_t Search(){

    SearchResult result;
    result.pageID=0;
    result.mathscore=0;
    if (PS_GetImage()==0) {
        printf("Finger detected!");
        if (PS_GenChar(0X01)){
            printf("Please re-put the finger.\r\n");
            return 0;
        }

        uint8_t response = PS_Search(0X01,0,100,&result);
        switch (response) {
            case 0:
                printf("Founded finger: ID=%d\r\n",result.pageID);
                Aura_Config(RGB_MODE_OPEN,0X0F,RGB_COLOR_GREEN,0);
                HAL_Delay(1000);
                Aura_Config(RGB_MODE_BREATH,0XFF,RGB_COLOR_PINK,0);
                break;
            case 0x09:

                printf("Finger is not registed.\r\n");
                Aura_Config(RGB_MODE_BLINK,0X0F,RGB_COLOR_RED,3);
                HAL_Delay(1000);
                Aura_Config(RGB_MODE_BREATH,0XFF,RGB_COLOR_YELLOW,0);

                break;
            default:
                printf("Other mistakes.\r\n");
                break;
        }
    }
    else printf("No finger.");
    return 1;
}