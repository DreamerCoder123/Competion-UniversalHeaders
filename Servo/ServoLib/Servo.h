/**
 * @author Haozhe Li
 * @warning 请在ino文件内标注Serial.begin(9600)
 * @warning 脉宽长度400-2600
 */
#pragma once
class Servo
{
private:
    int Servo_pin;

public:
    short int currentPulse; // 标注了现在的脉宽
    Servo(int servo_pin);
    Servo() {};
    void FastMove_withOutDelay(short int pulse); // 不保证准确性和稳定性的函数，没有延迟
    bool ServoTest(bool while_enable);           // 测试函数，可以测试单个电机的脉宽值
};
Servo::Servo(int servo_pin)
{
    this->Servo_pin = servo_pin;
    pinMode(this->Servo_pin, OUTPUT);
    // 400-2500
    FastMove_withOutDelay(1200);
}
void Servo::FastMove_withOutDelay(short int pulse)
{
    digitalWrite(this->Servo_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(this->Servo_pin, LOW);
    this->currentPulse = pulse;
}
bool Servo::ServoTest(bool while_enable)
{
    bool temp=false;                                   // 垃圾
    const short int servo_test_sensitivity = 50; // 这个变量设置了Servo测试的灵敏度
    do
    {
        switch (Serial.read())
        {
        case 'u':
            this->currentPulse += servo_test_sensitivity;
            // going up
            break;
        case 'd':
            // going down
            this->currentPulse -= servo_test_sensitivity;
            break;
        case 'q':
            temp = true; // 退出当前调试的机械
            Serial.print("Dubugging     TargetPulse");
            Serial.println(this->currentPulse);
        }
        FastMove_withOutDelay(this->currentPulse);
    } while (while_enable);
    return temp;
}