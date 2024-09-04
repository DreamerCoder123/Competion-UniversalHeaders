#pragma once
class qtis
{
private:
    unsigned char pin;

public:
    bool Getstatus();
    qtis(unsigned char pin);
};
qtis::qtis(unsigned char pin)
{
    pinMode(pin,INPUT);
    this->pin=pin;
}
bool qtis::Getstatus(){
    return digitalRead(this->pin);
}