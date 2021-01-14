#include "stdio.h"

/* USER CODE BEGIN 4 */
int fputc(int ch,FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch,1,HAL_MAX_DELAY);
    return ch;
}//重写该函数以便在串口上运用printf
/* USER CODE END 4 */
///Editing all of above to enable your USART put messages to computer.
///(Here is usart1,STM32CubeMX give its structure name of 'huart1')

