#include "stm32f10x.h"
#include "Tracking.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

// 定义循迹传感器的GPIO引脚
// 定义循迹传感器的GPIO引脚
#define TRACKING_SENSOR_1_PIN   GPIO_Pin_4
#define TRACKING_SENSOR_2_PIN   GPIO_Pin_5
#define TRACKING_SENSOR_3_PIN   GPIO_Pin_6
#define TRACKING_SENSOR_4_PIN   GPIO_Pin_7

#define TRACKING_SENSOR_PORT_A  GPIOA

/**
  * @brief  初始化循迹模块的GPIO引脚
  * @param  无
  * @retval 无
  */
void Tracking_Init(void)
{
    // 开启GPIOA的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 初始化 PA4, PA5, PA6, PA7
    GPIO_InitStructure.GPIO_Pin = TRACKING_SENSOR_1_PIN | TRACKING_SENSOR_2_PIN | TRACKING_SENSOR_3_PIN | TRACKING_SENSOR_4_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(TRACKING_SENSOR_PORT_A, &GPIO_InitStructure);
}

/**
  * @brief  读取4个循迹传感器的状态
  * @param  无
  * @retval 返回一个8位无符号整数，每一位代表一个传感器的状态。
  *         从低位到高位（Bit0 -> Bit3）依次对应传感器1到4。
  *         检测到黑线为1，否则为0。
  */
uint8_t Tracking_ReadStatus(void)
{
    uint8_t status = 0;

    if (GPIO_ReadInputDataBit(TRACKING_SENSOR_PORT_A, TRACKING_SENSOR_1_PIN) == 1) { status |= 0x01; } // S1 -> Bit0
    if (GPIO_ReadInputDataBit(TRACKING_SENSOR_PORT_A, TRACKING_SENSOR_2_PIN) == 1) { status |= 0x02; } // S2 -> Bit1
    if (GPIO_ReadInputDataBit(TRACKING_SENSOR_PORT_A, TRACKING_SENSOR_3_PIN) == 1) { status |= 0x04; } // S3 -> Bit2
    if (GPIO_ReadInputDataBit(TRACKING_SENSOR_PORT_A, TRACKING_SENSOR_4_PIN) == 1) { status |= 0x08; } // S4 -> Bit3

    return status;
}