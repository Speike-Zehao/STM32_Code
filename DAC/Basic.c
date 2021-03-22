HAL_DAC_Start(&hdac,DAC_CHANNEL_1);//使能DAC
 HAL_DAC_SetValue(&hdac,DAC1_CHANNEL_1,DAC_ALIGN_12B_R,2048);//预期输出电压3.3/2=1.15V

//除了直接写值来改变电压以外，还可以在CubeMX里配置外部事件，如定时器事件触发。
//DAC集成了2个输出缓存，可以用来减少输出阻抗，无需外部运放即可直接驱动外部负载。
