#pragma once
class Sonar
{
public:
    Sonar(unsigned char pin_T, unsigned char pin_E);
    unsigned char pinT, pinE;
    short int instant_distance();
    short int avg_distance();

private:
};
Sonar::Sonar(unsigned char pin_T, unsigned char pin_E)
{
    pinMode(pin_E, INPUT);
    pinMode(pin_T, OUTPUT);
    this->pinE = pin_E;
    this->pinT = pin_T;
}
short int Sonar::instant_distance()
{
    digitalWrite(this->pinT, LOW);
    digitalWrite(this->pinT, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->pinT, LOW); // 10us脉冲触发
    return pulseIn(this->pinE, 1, 18500L) / 59;
}
short int Sonar::avg_distance()
{
    const int steps = 5;
    short int total=0;
    for (int i = 0; i < steps; i++)
    {
        total+=instant_distance();
    }
    return total/steps;
}