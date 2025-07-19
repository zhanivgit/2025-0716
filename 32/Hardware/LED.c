#include "LED.h"
#include "Delay.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

// 定义LED连接的GPIO端口和引脚
#define LED_GPIO_PORT    GPIOB
#define LED_GPIO_PIN     GPIO_Pin_9
#define LED_GPIO_CLK     RCC_APB2Periph_GPIOB

void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
    
    // 初始状态为关闭
    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN); // 假设高电平点亮，先熄灭
}

void LED_On(void)
{
    GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN); // 低电平点亮
}

void LED_Off(void)
{
    GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN); // 高电平熄灭
}

void LED_Turn(void)
{
    if (GPIO_ReadOutputDataBit(LED_GPIO_PORT, LED_GPIO_PIN) == 0)
    {
        GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
    }
    else
    {
        GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);
    }
}

void LED_Blink(uint32_t duration_ms, uint8_t times)
{
    for (uint8_t i = 0; i < times; i++)
    {
        LED_On();
        Delay_ms(duration_ms / 2);
        LED_Off();
        Delay_ms(duration_ms / 2);
    }
}
