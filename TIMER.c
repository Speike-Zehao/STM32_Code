__HAL_TIM_CLEAR_IT(&htim10,TIM_IT_UPDATE);//清除TIMER10的中断标志，防止一开始就中断。
HAL_TIM_Base_Start_IT(&htim10); //使能TIMER10的更新中断,注意根据定时器的不同选择不一样的htim，这个值在tim.c 里面有定义。
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){}
//定时器中断服务函数
