#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "ENCODER.h"
#include "Control.h"
#include "Buzzer.h"
#include "LED.h"
#include "Tracking.h"
#include "math.h" // 添加此行，用于PI和fabs等数学函数

// --- 任务选择宏定义 ---
#define TASK_1 1
#define TASK_2 2
// #define TASK_3 3 // 待实现
// #define TASK_4 4 // 待实现

#define CURRENT_TASK TASK_0 // 在这里修改，选择要执行的任务

// 全局变量，供Control.c使用
int left_current_pulses;
int right_current_pulses;

int main(void)
{
    // --- 初始化 ---
    OLED_Init();
    Motor_Init();
    Encoder_Init();
    Buzzer_Init();
    LED_Init();
    Tracking_Init(); // 循迹模块初始化
	
    Delay_ms(1000); // 等待1秒，准备开始
    
    #if CURRENT_TASK == TASK_1
        // --- 执行任务1: A -> B ---
        OLED_Clear();
        OLED_ShowString(1, 1, "Task 1: A -> B");
        Delay_ms(1000);

        OLED_Clear();
        OLED_ShowString(1, 1, "State: MOVING");
        move_straight(100, 300); // 行驶100cm，最大速度150

        OLED_Clear();
        OLED_ShowString(1, 1, "State: ARRIVED B");
        node_alert();
        
        OLED_Clear();
        OLED_ShowString(1, 1, "Task 1 Complete!");

    #elif CURRENT_TASK == TASK_2
        // --- 执行任务2: A -> B -> C -> D -> A ---
        OLED_Clear();
        OLED_ShowString(1, 1, "Task 2: A->B->C->D->A");
        Delay_ms(1000);

        // 1. A -> B (直线)
        OLED_Clear();
        OLED_ShowString(1, 1, "State: A->B");
        move_straight(100, 150); // 行驶100cm
        node_alert();            // 到达B点，声光提示
        Delay_ms(500);           // 稍作停留

        // 2. B -> C (圆弧循迹，直到离开黑线)
        OLED_Clear();
        OLED_ShowString(1, 1, "State: B->C");
        follow_line_until_no_line(120); // 循迹圆弧，直到离开黑线
        node_alert();                   // 到达C点，声光提示
        Delay_ms(500);                  // 稍作停留

        // 3. C -> D (直线)
        OLED_Clear();
        OLED_ShowString(1, 1, "State: C->D");
        move_straight(100, 150); // 行驶100cm
        node_alert();            // 到达D点，声光提示
        Delay_ms(500);           // 稍作停留

        // 4. D -> A (圆弧循迹，直到离开黑线)
        OLED_Clear();
        OLED_ShowString(1, 1, "State: D->A");
        follow_line_until_no_line(120); // 循迹圆弧，直到离开黑线
        node_alert();                   // 到达A点，声光提示
        Delay_ms(500);                  // 稍作停留
        
        OLED_Clear();
        OLED_ShowString(1, 1, "Task 2 Complete!");

    #else
    // --- 其他任务 ---
    Clear_Encoder_Count(); // 清零编码器计数
    while(1)
    {   // turn_degrees(90, 300); // 旋转测试
        int left_encoder = Read_Left_Encoder();    //编码器读取测试
        int right_encoder = Read_Right_Encoder();
        
        // 在OLED上显示
        OLED_ShowString(2, 1, "L:");
        OLED_ShowSignedNum(2, 3, left_encoder, 5); // 在第2行显示左编码器值
        
        OLED_ShowString(3, 1, "R:");
        OLED_ShowSignedNum(3, 3, right_encoder, 5); // 在第3行显示右编码器值
        
        Delay_ms(100); // 延时100毫秒，方便观察
    }
    #endif
}
