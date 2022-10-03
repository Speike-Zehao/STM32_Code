//
// Created by SimilarTriangles on 2022/9/30.
//

#include "spi.h"
#include "stdint.h"
#include "ws2812_spi.h"
#include "stdio.h"
#include "usart.h"

#define code1 0b11111000
#define code0 0b11000000

/**
 * Here to define how long the RGB string is.
 * @attention Remember to make sure what spi port does you use.
 * @attention The baud rate of SPI Interface should be aroud 6.4Mbps.
 */
#define RGB_LENGTH 5

uint8_t ws2812_data[RGB_LENGTH+1][24];


static void ws2812_start_and_stop_transmit(){
    HAL_Delay(1);
}

static void ws2812_send_buffer(uint8_t* data){
    ws2812_start_and_stop_transmit();
    HAL_SPI_Transmit(&hspi1,data,(RGB_LENGTH+1)*24,HAL_MAX_DELAY);
    ws2812_start_and_stop_transmit();
}


/**
 * @brief Used to write the same color to all the cells.
 *
 * @param red 0-255
 * @param green 0-255
 * @param blue 0-255
 */

void ws2812_write_single_color(uint8_t red,uint8_t green,uint8_t blue){

    uint8_t data;

    printf("Now to refresh data.\r\n");
    for (int i = 0; i < RGB_LENGTH; ++i) {
        data=green;
        for (int j = 0; j < 8; ++j) {
            if((data>>j)&0x01){
                ws2812_data[i][7-j]= code1;
                printf("Code1\r\n");
            }
            else{
                ws2812_data[i][7-j]=code0;
                printf("Code0\r\n");
            }
        }
        data=red;
        for (int j = 0; j < 8; ++j) {
            if((data>>j)&0x01){
                printf("Code1\r\n");
                ws2812_data[i][15-j]= code1;
            }
            else{
                printf("Code0\r\n");
                ws2812_data[i][15-j]=code0;
            }
        }
        data=blue;
        for (int j = 0; j < 8; ++j) {
            if((data>>j)&0x01){
                printf("Code1\r\n");
                ws2812_data[i][23-j]= code1;
            }
            else{
                printf("Code0\r\n");
                ws2812_data[i][23-j]=code0;
            }
        }
    }
    for (int i = 0; i < 24; ++i) {
        ws2812_data[RGB_LENGTH][i]=0x00;
    }
    ws2812_send_buffer(*ws2812_data);
}


/**
 * @brief Used to keep all the units breathing.
 * @param breath_speed 1-255, define how fast the breath speed is.
 */
void ws2812_breath(uint8_t breath_speed){

}