// 目标：实现多元机械臂的调用
#pragma once
#include "ServoLib/Servo.h"
class Arm
{
private:
    const short int Servo_limit = 10;
    Servo Servo_array[10];
    short int Full_servo_index; // 所有角度舵机序号
public:
    short int Servo_index = 0;
    void init(unsigned char *pins, short int length);
    void test_arm();                                         // 对手臂进行测试
    void Slow_move(short int *pulse_array, short int speed); // 手臂运动
    void insistace(short int time);
};
void Arm::init(unsigned char *pins, short int length)
{
    for (int i = 0; i < length; i++)
    {
        Servo_array[i] = Servo(pins[i]); // 进行多自由度舵机的初始化
    }
    this->Full_servo_index = length; // 存储角度舵机的数量
    if (this->Servo_limit < length)  //! 对输入电机进行合法性检查
    {
        Serial.println("[Error] Too many joints!");
        while (1)
            ;
    }
}
void Arm::test_arm()
{
    bool next_bool = false;
    short int current_debugging = 0;
    while (1)
    {
        if (next_bool)
        {
            Serial.println("Last motor debugging:");
            Serial.println(current_debugging);
            current_debugging++;
            next_bool = false; // 防止下次跳过
        }
        //! 对当前调试机器的合法度检查
        if (this->Full_servo_index <= current_debugging)
        {
            return; // TODO 简单粗暴地操作，退出即可QwQ
        }
        if (this->Servo_array[current_debugging].ServoTest(false))
        {
            //! 进行下一次的调试
            next_bool = true;
        }
        for (int i = 0; i < Full_servo_index; i++)
        {
            // 对机械臂进行保持
            this->Servo_array[i].FastMove_withOutDelay(this->Servo_array[i].currentPulse);
        }
    }
}
void Arm::Slow_move(short int *pulse_array, short int speed)
{
    short int deltaPulse[10];
    const short int Pulse_steps = speed;
    for (int i = 0; i < this->Full_servo_index; i++)
    {
        deltaPulse[i] = pulse_array[i] - this->Servo_array[i].currentPulse;
        // 对每一个角度舵机进行差值计算
    }
    for (int i = 0; i < Pulse_steps; i++)
    {
        for(int x=0;x<3;x++){
            for (int j = 0; j < this->Full_servo_index; j++)
            {
                this->Servo_array[j].FastMove_withOutDelay(this->Servo_array[j].currentPulse += deltaPulse[j] / Pulse_steps);

            }
        }
    }
    // ! 对机械臂的状态进行补偿
    for (int i = 0; i < this->Full_servo_index; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            this->Servo_array[i].FastMove_withOutDelay(pulse_array[i]);
            
        }
        delay(20);
    }
}
void Arm::insistace(short int times)
{
    unsigned long long currentTime = millis();
    while (millis() - currentTime < times)
    {
        for (int i = 0; i < this->Full_servo_index; i++)
        {
            this->Servo_array[i].FastMove_withOutDelay(this->Servo_array[i].currentPulse);
        }
        delay(20);
    }
}