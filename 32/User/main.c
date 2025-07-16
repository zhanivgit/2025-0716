#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h" // 用于fabs函数
#include "ENCODER.h" // 包含编码器头文件
#include "Tracking.h" // 包含循迹模块头文件
#include "Control.h"  // 包含控制算法头文件

// 全局变量，供Control.c使用
int left_current_pulses;
int right_current_pulses;


int main(void)
{
    // --- 初始化 ---
    OLED_Init();
    Motor_Init();
    Encoder_Init();
    Tracking_Init(); // 初始化循迹模块
	
		int tracking_speed = 150; // 设定循迹速度

    OLED_ShowString(1, 1, "State: TRACKING");

    while(1)
    {
        // 1. 读取传感器状态
        uint8_t sensor_status = Tracking_ReadStatus();
        
        // 2. 根据状态计算偏差
        int error = Tracking_Calculate_Error(sensor_status);
        
        // 3. 调用PID函数计算调整值
        int adjustment = Tracking_PID_Calculate(error);

        // 4. 计算左右轮速度
        int left_speed = tracking_speed - adjustment;
        int right_speed = tracking_speed + adjustment;

        // 5. 设置电机速度
        MotorA_SetSpeed(left_speed);
        MotorB_SetSpeed(right_speed);

        // OLED显示调试信息
        OLED_ShowString(2, 1, "Err: ");
        OLED_ShowSignedNum(2, 5, error, 4);
        OLED_ShowString(3, 1, "PID: ");
        OLED_ShowSignedNum(3, 5, adjustment, 5);
        OLED_ShowString(4, 1, "L/R: ");
        OLED_ShowSignedNum(4, 5, left_speed, 4);
        OLED_ShowSignedNum(4, 10, right_speed, 4);
    }
}
