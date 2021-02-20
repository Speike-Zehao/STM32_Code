#include "stdio.h"

KEIL5
/* USER CODE BEGIN 4 */
int fputc(int ch,FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch,1,HAL_MAX_DELAY);
    return ch;
}//重写该函数以便在串口上运用printf
/* USER CODE END 4 */
///Editing all of above to enable your USART put messages to computer.
///(Here is usart1,STM32CubeMX give its structure name of 'huart1')

Clion 重定向流和keil不同
void __io_putchar(uint8_t ch)
{
    HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,0xFFFF);
    //return (ch);
}


//串口初始化
static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
}
