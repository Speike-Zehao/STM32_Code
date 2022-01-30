//
// Created by Speike on 2022/1/14.
//

#include "usartNew.h"
#include "main.h"
#include "tim.h"
#include "usart.h"

#define FINGER USART2

uint8_t RxBuffer[1];//缓存：接收1位数据后进入中断处理
uint8_t RECBUFF[REC_LENGTH];//接收到的数据，不超过USART_REC_LENGTH位
uint16_t USART_STA = 0;//状态标志



//使能接收中断
void FINGER_UART_Start_IT(UART_HandleTypeDef huart,uint16_t length_of_data){
    UART_Start_Receive_IT(&huart,RxBuffer,length_of_data);
}

//接收中断回调函数，数据以\r\n结尾
//void FINGER_Callback(UART_HandleTypeDef huart){
//    if (huart.Instance==USART2){
//        if (USART_STA&0X80){
//        }//接收已完成
//        else{
//            if (USART_STA&0X40){
//                if (*RxBuffer!=0x0a) USART_STA=0; //没接收到\n，重新接收数据
//                else USART_STA |= 0X80;//标记最后一位为1，已经接收完数据
//            }//接收到\r，判断是否接收到\n
//            else{
//                RECBUFF[USART_STA&0X3FFF]=*RxBuffer;
//                USART_STA++;
//                if (USART_STA>(USART_REC_LENGTH-1)) USART_STA=0;
//            }
//        }
//    }
//}

//定时器3中断服务函数
void TIM6_IRQHandler(void)
{
    if(__HAL_TIM_GET_FLAG(&htim6, TIM_FLAG_UPDATE) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(&htim6, TIM_IT_UPDATE) !=RESET)
        {
            __HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE);
            USART_STA|=0x8000;	//标记接收完成
            __HAL_TIM_DISABLE(&htim6);//关闭定时器6
        }
    }
}

//串口2中断服务函数,注意设置中断优先级。
//通过判断接收连续2个字符之间的时间差不大于100ms来决定是不是一次连续的数据.
//如果2个字符接收间隔超过100ms,则认为不是1次连续数据.也就是超过100ms没有接收到
//任何数据,则表示此次接收完毕.
//接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
void USART2_IRQHandler(void)
{
    uint8_t Res;
    if((__HAL_UART_GET_FLAG(&huart2,UART_FLAG_RXNE)!=RESET))//接收到数据
    {
        HAL_UART_Receive(&huart2,&Res,1,1000);
        if((USART_STA&0x8000)==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
        {
            if(USART_STA<100)		//还可以接收数据
            {
                __HAL_TIM_SET_COUNTER(&htim6,0);//计数器清空
                if(USART_STA==0)
                    __HAL_TIM_ENABLE(&htim6);  //使能定时器6
                RECBUFF[USART_STA++]=Res;		//记录接收到的值
            }else
            {
                USART_STA|=0X8000;					//强制标记接收完成
            }
        }
    }
}