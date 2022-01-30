//
// Created by Speike on 2022/1/30.
//

#ifndef USART1000_BM2166_FINGER_COMMUNICATION_H
#define USART1000_BM2166_FINGER_COMMUNICATION_H

#endif //USART1000_BM2166_FINGER_COMMUNICATION_H

#include "main.h"
#include "stdio.h"
#include "main.h"
#include "usartNew.h"

#define FINGER USART2
#define Cmd 0x01
#define Data 0x02
#define End 0x08
#define total_page 50

#define standard_delay 2000

//RGB指令集
#define RGB_MODE_BREATH 0x01
#define RGB_MODE_BLINK 0X02
#define RGB_MODE_OPEN 0X03
#define RGB_MODE_CLOSE 0X04

#define RGB_COLOR_RED 0X01
#define RGB_COLOR_GREEN 0X02
#define RGB_COLOR_YELLOW 0X03
#define RGB_COLOR_BLUE 0X04
#define RGB_COLOR_PINK 0X05
#define RGB_COLOR_SKYBLUE 0X06
#define RGB_COLOR_WHITE 0X07
#define RGB_COLOR_STRANGE 0X20
#define RGB_COLOR_VERYSTRANGE 0X30

#define RGB_CIRCULAR_INFINITY 0X00


typedef struct
{
    uint16_t pageID;//指纹ID
    uint16_t mathscore;//匹配得分
}SearchResult;

uint8_t PS_GetImage(void);
uint8_t PS_GenChar(uint8_t BufferID);
uint8_t PS_Search(uint8_t BufferID,uint16_t StartPage,uint16_t PageNum,SearchResult *Result);
uint8_t Handshake();
void Aura_Config(uint8_t mode,uint8_t speed,uint8_t color,uint8_t circulation);
