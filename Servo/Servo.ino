#include "Arm.h"
#include "servoDefition.h"
unsigned char list_basket[3]={13,12,11};
Arm Arm_basket;
void setup()
{
    Arm_basket.init(list_basket,3);
}
void loop()
{
    Arm_basket.insistace(1000);
}