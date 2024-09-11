#pragma once
class qtis
{
private:
    unsigned char pin;
    unsigned char weight; // 设定当前qti权重

public:
    bool getWeight();
    qtis(unsigned char pin, unsigned char weight);
};
qtis::qtis(unsigned char pin, unsigned char weight)
{
    pinMode(pin, INPUT);
    this->pin = pin;
    this->weight = weight;
}
bool qtis::getWeight()
{
    return digitalRead(this->pin) * this->weight; // 返回加权数
}