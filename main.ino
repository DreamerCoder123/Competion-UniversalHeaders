#include "Servo\Arm.h"
#include "qtis\car_qtis.h"
#include "DcMotor\DcMotor.h"
#include "Sonar\Sonar.h"
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include "servopoints.h"
unsigned char arms_list[6] = {10, 9, 8, 13, 12, 11};
Arm arms;
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
bool turntable_husky(Arm arms) // 依据哈士奇识别的结果调整角度舵机的位置
{
    const char sensitivity = 10; // 识别的精确度
    if (!huskylens_scan())
    {
        return false;
    }
    short int error = -1 * (huskylens_result.xCenter - husky_xm / 2); // 识别到的物体在哈士奇在屏幕上的误差
    short int mapp = map(error, -1 * husky_xm, husky_xm, -200, +200); // 对哈士奇识别到的差值
    turnTable.FastMove_withOutDelay(constrain(turnTable.currentPulse + mapp, 200, 2600));
    huskylens_scan();
    short int NewError = huskylens_result.xCenter - husky_xm / 2;
    husky.customText("Error:" + String(mapp) + String(abs(NewError) < sensitivity ? " OK" : " Waiting"), 0, 0);
    arms.insistace(10);
    return abs(error) < sensitivity;
}
void setup()
{
    Serial.begin(115200);
    arms.init(arms_list, 6);
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
    } while (millis() - ct < 3000);
}
void loop()
{
    while (DUBUGGING)
        arms.test_arm();
    short int temp = 0;
    for (int i = 0; i < 20; i++)
    {
        temp += turntable_husky(arms);
        Serial.println(temp);
        husky.customText(String(temp), 0, 0);
        if (temp > 13 && huskylens_scan())
        {
            arms.Slow_move(GRABBER_READY, 100);
            arms.insistace(1000);
            arms.Slow_move(GRABBER_DOWN, 100);
            arms.insistace(1000);
            arms.Slow_move(GRABBER_GRAB, 100);
            arms.insistace(1000);
            arms.Slow_move(GRABBER_READY, 100);
            arms.insistace(3000);
            arms.Slow_move(GRABBER_RELEASE_1, 200);
            arms.insistace(1000);
            arms.Slow_move(GRABBER_RELEASE_2,100);
            arms.insistace(1000);
            arms.Slow_move(GRABBER_READY, 100);
            arms.insistace(1000);
            temp = 0; // 防止重复执行
            break;
        }
        else
        {
            arms.insistace(20);
        }
    }
}