# 基于STM32的WS2812/SK2812驱动

## ws2812_spi.c

SPI接口配置如下：

1.摩托罗拉，MSB First

2.Baud Rate = 6.4Mbps（附近）

3.更改驱动内的`spi handler`和`RGB_Length`
