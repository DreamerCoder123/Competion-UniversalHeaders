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
HUSKYLENS husky;                  // X 320 Y 240
const short int husky_xm = 320;   // 哈士奇x最大值320
const short int husky_ym = 240;   // 哈士奇y最大值240
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
            husky.customText((String() + F("ID:") + huskylens_result.ID + F(" CenterX:") + huskylens_result.xCenter + F(" CenterY:") + huskylens_result.yCenter), 0, 0);
            return true;
        }
    }
    return false;
}
bool turntable_husky(Arm arm1, Arm arm2) // 依据哈士奇识别的结果调整角度舵机的位置
{
    const char sensitivity = 5;
    if (!huskylens_scan())
    {
        return;
    }
    short int error = -1 * (huskylens_result.xCenter - husky_xm / 2);
    short int mapp = map(error, -1 * husky_xm, husky_xm, -100, +100);
    turnTable.FastMove_withOutDelay(constrain(turnTable.currentPulse + mapp, 200, 2600));
    huskylens_scan();
    short int NewError = huskylens_result.xCenter - husky_xm / 2;
    husky.customText("Error:" + String(mapp) + String(abs(NewError) < sensitivity ? " OK Suki" : " Waiting"), 0, 0);
    arm1.insistace(30);
    arm2.insistace(30);
    return abs(NewError) < sensitivity;
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
    long long ct = millis();
    do
    {
        int cx = (millis() - ct);
        husky.customText("Please wait..." + String(cx), 0, 0);
    } while (millis() - ct < 5000);
}
void loop()
{
    while (!turntable_husky(Arm_grabber, Arm_basket))
    {
        
    }
}