#include "Servo\Arm.h"
#include "qtis\qtis.h"
#include "DcMotor\DcMotor.h"
#include "Sonar\Sonar.h"
unsigned char list_basket[3] = {13, 12, 11};
unsigned char list_grabber[3] = {10, 9, 8};
Arm Arm_basket;     // 小车有篮子的机械臂
Arm Arm_grabber;    // 小车带有抓手的机械臂
Servo turnTable(2); // 小车转盘
void setup()
{
    Arm_basket.init(list_basket, 3);
    Arm_grabber.init(list_grabber, 3);
    // 初始机械臂对象
}
void loop()
{
    Arm_grabber.insistace(200);
    Arm_basket.insistace(200);
}