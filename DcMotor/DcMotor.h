// Author : 李昊哲
// Date: 2024/8/30
#pragma once
class DcMotor
{
public:
    DcMotor(short int red_l, short int black_l, short int red_r, short int black_r);
    void run(short int speedL, short int speedR);

private:
    short int red_l, black_l, red_r, black_r;
};

DcMotor::DcMotor(short int red_l, short int black_l, short int red_r, short int black_r)
{
    pinMode(red_l, OUTPUT);
    pinMode(black_l, OUTPUT);
    pinMode(red_r, OUTPUT);
    pinMode(black_r, OUTPUT);
    this->red_l = red_l;
    this->black_l = black_l;
    this->red_r = red_r;
    this->black_r = black_r;
}
void DcMotor::run(short int speedL, short int speedR)
{
    speedL = constrain(speedL, -255, 255);
    speedR = constrain(speedR, -255, 255);
    // 左边直流电机
    if (speedL > 0)
    {
        analogWrite(this->red_l, speedL);
        digitalWrite(this->black_l, 0);
    }
    else if (speedL < 0)
    {
        digitalWrite(this->red_l, 0);
        analogWrite(this->black_l, -1 * speedL);
    }
    else
    {
        digitalWrite(this->red_l, 0);
        digitalWrite(this->black_l, 0);
    }
    // 右边直流电机
    if (speedR > 0)
    {
        analogWrite(this->red_r, speedR);
        digitalWrite(this->black_r, 0);
    }
    else if (speedR < 0)
    {
        digitalWrite(this->red_r, 0);
        analogWrite(this->black_r, -1 * speedR);
    }
    else
    {
        digitalWrite(this->red_r,0);
        digitalWrite(this->black_r,0);
    }
}