// 目标：实现多元机械臂的调用
#pragma once
#include "ServoLib/Servo.h"
class Arm
{
private:
    const short int Servo_limit = 10;
    short int Full_servo_index; // 所有角度舵机序号
    short int dur[7] = {1200, 1200, 1200, 1200, 1200, 1200, 1200};

public:
    Servo Servo_array[10];
    short int Servo_index = 0;
    void init(unsigned char *pins, short int length);
    void test_arm();                                         // 对手臂进行测试
    void Slow_move(short int *pulse_array, short int speed); // 手臂运动
    void insistace(short int time);
    void QtConnection();
};
/**
 * @brief Initialize the robot arm with the given pin numbers and number of joints.
 *
 * This function will initialize the robot arm by setting up the servo motors
 * with the given pin numbers. It will also store the number of joints in the
 * robot arm. If the number of joints is greater than the maximum allowed, it will
 * print an error message and enter an infinite loop.
 *
 * @param pins The array of pin numbers for the servo motors.
 * @param length The number of joints in the robot arm.
 */
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
/**
 * @brief A simple debugging function for testing all the joints of the robot arm.
 *
 * This function will go through each joint of the robot arm and test its servo
 * motor. It will print the current pulse of each servo motor and wait for the
 * user to input a command. If the command is 'q', it will move on to the next
 * joint. If the command is 'u' or 'd', it will increase or decrease the current
 * pulse of the servo motor. If the command is any other character, it will exit
 * the function. The function will also exit if the user has finished testing
 * all the joints.
 */
void Arm::test_arm()
{
    bool next_bool = false;
    short int current_debugging = 0;
    while (1)
    {
        if (next_bool)
        {
            for (int i = 0; i < this->Full_servo_index; i++)
                Serial.print(String(this->Servo_array[i].currentPulse) + String(" ,"));
            Serial.println();
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
/**
 * @brief Gradually moves the arm to the specified pulse positions at a given speed.
 *
 * This function calculates the difference between the current and target pulse
 * positions for each servo in the arm, and then gradually moves each servo
 * to its target position in steps, determined by the given speed. After reaching
 * the target positions, it compensates by maintaining the final positions for a
 * short duration.
 *
 * @param pulse_array An array of target pulse values for each servo.
 * @param speed The number of steps to divide the movement, affecting the speed of motion.
 */
void Arm::Slow_move(short int *pulse_array, short int speed)
{
    short int deltaPulse[10];
    const short int Pulse_steps = speed;
    for (int i = 0; i < this->Full_servo_index; i++)
    {
        deltaPulse[i] = (pulse_array[i] - this->Servo_array[i].currentPulse);
        // 对每一个角度舵机进行差值计算
    }
    for (int i = 0; i < Pulse_steps; i++)
    {
        for (int j = 0; j < this->Full_servo_index; j++)
        {
            this->Servo_array[j].FastMove_withOutDelay(this->Servo_array[j].currentPulse + deltaPulse[j] / Pulse_steps);
        }
        delay(10);
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
/**
 * @brief Keep the current pose for a specified duration.
 *
 * This function is used to keep the current pose of the robotic arm for a
 * specified duration. It is often used to keep the pose of the arm while
 * performing a specific action, such as grasping an object.
 *
 * @param times The duration to keep the current pose
 */
void Arm::insistace(short int times)
{
    unsigned long currentTime = millis();
    while (millis() - currentTime < times)
    {
        for (int i = 0; i < this->Full_servo_index; i++)
        {
            this->Servo_array[i].FastMove_withOutDelay(this->Servo_array[i].currentPulse);
        }
    }
}
void Arm::QtConnection()
{
    while (true)
    {
        if (Serial.available())
        {                                                       // 检查串口是否有数据可读
            String receivedData = Serial.readStringUntil('\n'); // 读取串口数据直到换行符
            int index = 2;
            int temp = receivedData[0] - '0';
            int dur = 0;

            // this->insistace(100);

            while (index < receivedData.length())
            {
                dur = dur * 10 + (receivedData[index] - '0');
                index++;
            }
            this->dur[temp] = dur;
        }
        this->Slow_move(this->dur, 1);
    }
}
