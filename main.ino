#include "Servo\Arm.h"
#include "qtis\qtis.h"
#include "DcMotor\DcMotor.h"
#include "Sonar\Sonar.h"
unsigned char list_basket[3] = {13, 12, 11};
unsigned char list_grabber[3] = {10, 9, 8};
Arm Arm_basket;
Arm Arm_grabber;
void setup()
{
    Arm_basket.init(list_basket, 3);
    Arm_grabber.init(list_grabber, 3);
    // 初始机械臂对象
}
void loop()
{
    Arm_basket.insistace(20);
    Arm_grabber.insistace(20);
}