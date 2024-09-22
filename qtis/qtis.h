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
class New_qtis
{
public:
    New_qtis(qtis *qti);
    short int _qtiread();

private:
    qtis qti[4];
    const short int PINS_MAX = 4;
};
New_qtis::New_qtis(qtis *qti)
{
    for (int i = 0; i < PINS_MAX; i++)
    {
        this->qti[i] = qti[i]; // 对所有的qti进行初始化
    }
}
short int New_qtis::_qtiread()
{
    // 统一以向右为正
    short int total = 0;
    for (int i = 0; i < this->PINS_MAX; i++)
    {
        total += this->qti[i].getWeight();
    }
    return total;
}