#include "Servo\Arm.h"
#include "qtis\car_qtis.h"
#include "DcMotor\DcMotor.h"
#include "Sonar\Sonar.h"
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
unsigned char list_basket[3] = {13, 12, 11};
unsigned char list_grabber[3] = {10, 9, 8};
Arm Arm_basket;     // 小车有篮子的机械臂
Arm Arm_grabber;    // 小车带有抓手的机械臂
Servo turnTable(2); // 小车转盘 2450-350 脉宽增加顺时针转动
SoftwareSerial huskylens_softwareSerial(51, 52);
HUSKYLENSResult huskylens_result; // 哈士奇结果存储
HUSKYLENS husky;
bool huskylens_scan()
{
    if (!husky.request())
    {
    }
    else if (!husky.isLearned())
    {
    }
    else
    {
        if (husky.available())
        {
            huskylens_result = husky.read();
            Serial.println(String() + F("ID:") + huskylens_result.ID + F(" CenterX:") + huskylens_result.xCenter + F(" CenterY:") + huskylens_result.yCenter);
            return true;
        }
    }
    return false;
}
void setup()
{
    Serial.begin(115200);
    Arm_basket.init(list_basket, 3);
    Arm_grabber.init(list_grabber, 3);
    // 初始机械臂对象
    huskylens_softwareSerial.begin(9600);
    while (!husky.begin(huskylens_softwareSerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(1000);
    }
    // 哈士奇开机自检
}
void loop()
{
    huskylens_scan();
}