    void Configure_GPIO(){
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();           
	
    GPIO_Initure.Pin=GPIO_PIN_0; //使能PB0 
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;   //GPIO运行模式：高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);  
	   
    GPIO_Initure.Alternate=GPIO_AF1_TIM2;   //GPIO复用模式：配置为定时器2的通道1
    }

    void GPIO_INIT(){
    GPIO_InitTypeDef GPIO_Initure;
    GPIO_Initure.Pin=GPIO_PIN_1; //PB1
    GPIO_Initure.Mode=GPIO_MODE_AF_PP; //复用推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP; //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH; //高速
    GPIO_Initure.Alternate= GPIO_AF2_TIM3; //PB1 复用为 TIM3_CH4 
	    //注意，Alternate Function 即AFx，x值对应的映射外设在参考手册的GPIO复用部分、芯片手册的引脚定义和映射部分给出。
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
    }


   void Reset(){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(led_GPIO_Port, &GPIO_InitStruct);
	
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);	
    HAL_Delay(5);
    __HAL_TIM_CLEAR_FLAG(&htim2,TIM_FLAG_CC1|TIM_FLAG_UPDATE);  
    __HAL_TIM_SET_COUNTER(&htim2,0);
	
    GPIO_InitStruct.Mode=GPIO_MODE_AF_PP;    
    GPIO_InitStruct.Pull=GPIO_NOPULL;         
    GPIO_InitStruct.Alternate=GPIO_AF1_TIM2;   
    HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    }//复用F429IGTx的PA5用作电容的放电接口和TIM2的channel1。有多余的IO口就不要复用。
