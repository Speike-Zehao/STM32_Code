//
// Created by SimilarTriangles on 2022/4/14.
//

#include "aht10.h"
#include "myi2c_hal.h"
#define aht10_Addr 0x38

//接受数据的数组
uint8_t data[6]={0};

static struct command start_convert={
        .cmdaddr=0xac,
        .parameters={0x33,0x00},
        .para_length=2
};

static struct command init={
        .cmdaddr=0xe1,
        .parameters={0x08,0x00},
        .para_length=2
};

void aht10_init(){
    iic_write(&hi2c1,aht10_Addr,&init);
}

static void aht10_start(){
    iic_write(&hi2c1,aht10_Addr,&start_convert);
}

static void aht10_read_data(){

    iic_read(&hi2c1,aht10_Addr,data,6);

    for (int i = 0; i < 6; ++i) {
        printf("data[%d],%d\r\n",i,data[i]);
    }
    printf("\r\n");
}

void aht10_work(){
    aht10_start();
    aht10_read_data();
}


