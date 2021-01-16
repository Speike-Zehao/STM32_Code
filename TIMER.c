__HAL_TIM_CLEAR_IT(&htim10,TIM_IT_UPDATE);//清除TIMER10的中断标志，防止一开始就中断。
HAL_TIM_Base_Start_IT(&htim10); //初始化定时器，使能TIMER10的更新中断,注意根据定时器的不同选择不一样的htim，这个值在tim.c 里面有定义。
HAL_TIM_Base_Start(&htim10); //初始化定时器，但不使能更新中断。
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){}
//定时器中断服务函数

//以下是单通道基本定时器的初始化函数
static void MX_TIM10_Init(void)
{
  htim10.Instance = TIM10;//定时器序号
  htim10.Init.Prescaler = 16799;//分频系数
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;//计数模式
  htim10.Init.Period = 9999;//计数周期
  //以下不知道干嘛的，为默认设置
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; 
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }

}
