#include "Arm.h"
#include "servoDefition.h"
Arm first_arm;
void setup()
{
    Serial.begin(9600);
    short int array[3] = {15, 14, 19};
    first_arm.init(array, 3); // 初始化手臂
}
void loop()
{
    first_arm.test_arm();

}