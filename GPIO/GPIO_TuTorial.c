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
