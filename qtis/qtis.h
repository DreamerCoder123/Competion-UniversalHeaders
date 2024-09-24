#pragma once
class qtis
{
private:
    unsigned char pin;
    char weight; // 设定当前qti权重
public:
    short int getWeight();
    qtis(unsigned char pin, unsigned char weight);
    qtis() {};
};
qtis::qtis(unsigned char pin, unsigned char weight)
{
    pinMode(pin, INPUT);
    this->pin = pin;
    this->weight = weight;
}
short int qtis::getWeight()
{
    return (digitalRead(this->pin)) * this->weight; // 返回加权数
}

class muti_qti
{
public:
    muti_qti(qtis *qti, short int length);
    short int _qtiread();

private:
    qtis qti[4];
    const short int PINS_MAX = 4;
    short int length; // 存储数组的长度
};
muti_qti::muti_qti(qtis *qti, short int length)
{
    this->length = length; // 长度初始化
    for (int i = 0; i < PINS_MAX; i++)
    {
        this->qti[i] = qti[i]; // 对所有的qti进行初始化
    }
}
short int muti_qti::_qtiread()
{
    // 统一以向右为正
    short int total = 0;
    for (int i = 0; i < this->length; i++)
    {
        total += this->qti[i].getWeight();
    }//!读取所有的加权数
    return total;
}