//
// Created by Speike on 2022/1/30.
//

#include "BM2166_Finger_Communication.h"

extern uint16_t USART_STA;
extern uint8_t RECBUFF[];

uint8_t BM2166_STATE= 0;
uint8_t Open_the_door = 0;

uint32_t Addr = 0xffffffff;

void UART_SendByte(uint8_t data){
    while((USART2->SR&0X40)==0);
    USART2->DR = data;
}

void send_Head(){
    UART_SendByte(0xEF);
    UART_SendByte(0x01);
}

void send_Addr(){
    UART_SendByte(Addr>>24);
    UART_SendByte(Addr>>16);
    UART_SendByte(Addr>>8);
    UART_SendByte(Addr>>0);
}

void send_KindofPack(uint8_t Kind){
    UART_SendByte(Kind);
}

void send_Length(uint16_t Length){
    UART_SendByte(Length>>8);
    UART_SendByte(Length);
}

void send_Command(uint8_t cmd){
    UART_SendByte(cmd);
}
void send_Verify(uint16_t Verify){
    UART_SendByte(Verify>>8);
    UART_SendByte(Verify);
}

uint8_t *findResponsePackage(uint16_t delay) {
    if (RECBUFF[0]==0xEF && RECBUFF[6]==0X07){
        USART_STA=0;
        return RECBUFF;
    }
    else return 0;
}

uint8_t PS_GetImage(void)
{
    uint16_t temp;
    uint8_t ensure;
    uint8_t *data;

    send_Head();
    send_Addr();
    send_KindofPack(Cmd);
    send_Length(0x03);
    send_Command(0x01);
    temp =  0x01+0x03+0x01;
    send_Verify(temp);

    HAL_Delay(100);

    data=findResponsePackage(100);

    if(data)
        ensure=data[9];
    else
        ensure=0xff;
    return ensure;
}

uint8_t PS_GenChar(uint8_t BufferID)
{
    uint16_t temp;
    uint8_t  ensure;
    uint8_t  *data;
    send_Head();
    send_Addr();
    send_KindofPack(Cmd);
    send_Length(0x04);
    send_Command(0x02);
    UART_SendByte(BufferID);
    temp = 0x01+0x04+0x02+BufferID;
    send_Verify(temp);

    HAL_Delay(230);

    data=findResponsePackage(200);
    if(data)
        ensure=data[9];
    else
        ensure=0xff;
    return ensure;
}

//------------------------------未启用的功能（可用于录入指纹）------------------------------
////合并特征（生成模板）PS_RegModel
////功能:将CharBuffer1与CharBuffer2中的特征文件合并生成 模板,结果存于CharBuffer1与CharBuffer2
////说明:  模块返回确认字
//uint8_t PS_RegModel(void)
//{
//    uint16_t temp;
//    uint8_t  ensure;
//    uint8_t  *data;
//    send_Head();
//    send_Addr();
//    send_KindofPack(0x01);//命令包标识
//    send_Length(0x03);
//    send_Command(0x05);
//    temp = 0x01+0x03+0x05;
//    send_Verify(temp);
//
//    data=findResponsePackage(2000);
//    if(data)
//        ensure=data[9];
//    else
//        ensure=0xff;
//    return ensure;
//}
////储存模板 PS_StoreChar
////功能:将 CharBuffer1 或 CharBuffer2 中的模板文件存到 PageID 号flash数据库位置。
////参数:  BufferID @ref charBuffer1:0x01	charBuffer1:0x02
////       PageID（指纹库位置号）
////说明:  模块返回确认字
//uint8_t PS_StoreChar(uint8_t BufferID,uint16_t PageID)
//{
//    uint16_t temp;
//    uint8_t  ensure;
//    uint8_t  *data;
//    send_Head();
//    send_Addr();
//    send_KindofPack(0x01);//命令包标识
//    send_Length(0x06);
//    send_Command(0x06);
//    {
//        UART_SendByte(BufferID);
//        UART_SendByte(PageID>>8);
//        UART_SendByte(PageID);
//    }
//
//    temp = 0x01+0x06+0x06+BufferID
//           +(PageID>>8)+(uint8_t)PageID;
//    send_Verify(temp);
//    data=findResponsePackage(2000);
//    if(data)
//        ensure=data[9];
//    else
//        ensure=0xff;
//    return ensure;
//}
////删除模板 PS_DeletChar
////功能:  删除flash数据库中指定ID号开始的N个指纹模板
////参数:  PageID(指纹库模板号)，N删除的模板个数。
////说明:  模块返回确认字
//uint8_t PS_DeletChar(uint16_t PageID,uint16_t N)
//{
//    uint16_t temp;
//    uint8_t  ensure;
//    uint8_t  *data;
//    send_Head();
//    send_Addr();
//    send_KindofPack(0x01);//命令包标识
//    send_Length(0x07);
//    send_Command(0x0C);
//    UART_SendByte(PageID>>8);
//    UART_SendByte(PageID);
//    UART_SendByte(N>>8);
//    UART_SendByte(N);
//    temp = 0x01+0x07+0x0C
//           +(PageID>>8)+(uint8_t)PageID
//           +(N>>8)+(uint8_t)N;
//    send_Verify(temp);
//    data=findResponsePackage(2000);
//    if(data)
//        ensure=data[9];
//    else
//        ensure=0xff;
//    return ensure;
//}
////清空指纹库 PS_Empty
////功能:  删除flash数据库中所有指纹模板
////参数:  无
////说明:  模块返回确认字
//uint8_t PS_Empty(void)
//{
//    uint16_t temp;
//    uint8_t  ensure;
//    uint8_t  *data;
//    send_Head();
//    send_Addr();
//    send_KindofPack(0x01);//命令包标识
//    send_Length(0x03);
//    send_Command(0x0D);
//    temp = 0x01+0x03+0x0D;
//    send_Verify(temp);
//    data=findResponsePackage(2000);
//    if(data)
//        ensure=data[9];
//    else
//        ensure=0xff;
//    return ensure;
//}


////精确比对两枚指纹特征 PS_Match
////功能:精确比对CharBuffer1 与CharBuffer2 中的特征文件
////模块返回确认字
//uint8_t PS_Match(void)
//{
//    uint16_t temp;
//    uint8_t  ensure;
//    uint8_t  *data;
//    send_Head();
//    send_Addr();
//    send_KindofPack(Cmd);//命令包标识
//    send_Length(0x03);
//    send_Command(0x03);
//    temp = 0x01+0x03+0x03;
//    send_Verify(temp);
//    data=findResponsePackage(2000);
//    if(data)
//        ensure=data[9];
//    else
//        ensure=0xff;
//    return ensure;
//}


//搜索指纹 PS_Search
//功能:以CharBuffer1或CharBuffer2中的特征文件搜索整个或部分指纹库.若搜索到，则返回页码。
//参数:  BufferID @ref CharBuffer1	CharBuffer2
//说明:  模块返回确认字，页码（相配指纹模板）
uint8_t PS_Search(uint8_t BufferID,uint16_t StartPage,uint16_t PageNum,SearchResult *Result)
{

    uint8_t *p;
    p=RECBUFF;

    uint16_t temp;
    uint8_t  response;
    uint8_t  *data;
    send_Head();
    send_Addr();
    send_KindofPack(Cmd);//命令包标识
    send_Length(0x08);
    send_Command(0x04);
    UART_SendByte(BufferID);
    UART_SendByte(StartPage>>8);
    UART_SendByte(StartPage);
    UART_SendByte(PageNum>>8);
    UART_SendByte(PageNum);
    temp = 0x01+0x08+0x04+BufferID
           +(StartPage>>8)+(uint8_t)StartPage
           +(PageNum>>8)+(uint8_t)PageNum;
    send_Verify(temp);


    HAL_Delay(180);
    data=findResponsePackage(5000);

    printf("Search Receive package:");
    do {
        printf("%x ",*p);
        p++;

    }while(p-RECBUFF<16||*p!=0);
    printf("\n");

    if(data)
    {
        response = data[9];
        Result->pageID=(data[10]<<8)+data[11];
        Result->mathscore=(data[12]<<8)+data[13];
    }
    else
        response = 0xff;
    return response;
}

uint8_t Handshake(){

    uint8_t *data;
    uint8_t response;

    send_Head();
    send_Addr();
    send_KindofPack(Cmd);
    send_Length(0x03);
    send_Command(0x35);
    send_Verify(Cmd+0x03+0x35);

    HAL_Delay(100);

    data= findResponsePackage(standard_delay);
    if (data) return data[9];
    else return 0xff;

    return response;
}

void Aura_Config(uint8_t mode,uint8_t speed,uint8_t color,uint8_t circulation){
    send_Head();
    send_Addr();
    send_KindofPack(Cmd);
    send_Length(0x07);
    send_Command(0x3c);
    UART_SendByte(mode);
    UART_SendByte(speed);
    UART_SendByte(color);
    UART_SendByte(circulation);
    send_Verify(Cmd+0x07+0x3c+mode+speed+color+circulation);

}