#pragma once
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include "Constants.h"                           // X 320 Y 240
SoftwareSerial huskylens_softwareSerial(51, 52); // 哈士奇软串口接点
HUSKYLENSResult huskylens_result;                // 哈士奇结果存储
const short int husky_xm = 320;                  // 哈士奇x最大值320
const short int husky_ym = 240;                  // 哈士奇y最大值240
short int husky_count = 0;
namespace husky_related
{
    //! 已验证
    bool huskylens_scan(short int ID) // 哈士奇扫描视野内的标签，返回特定标签值，获取x最大的标签值
    {
        if (!husky.request(ID))
        {
        }
        else if (!husky.isLearned())
        {
        }
        else
        {
            if (husky.available())
            {
                husky_count = husky.count();
                short length = husky.count(ID); // 获取特定id标签的个数
                HUSKYLENSResult maxresult = husky.get(ID, 0);
                for (int i = 0; i < length; i++)
                {
                    if (maxresult.xCenter < husky.get(ID, i).xCenter)
                    {
                        maxresult = husky.get(ID, i);
                    }
                }
                huskylens_result = maxresult;
                // 获取最大值标签的中心坐标
                Serial.println(String() + F("ID:") + huskylens_result.ID + F(" CenterX:") + huskylens_result.xCenter + F(" CenterY:") + huskylens_result.yCenter);
                husky.customText((String() + F("ID:") + huskylens_result.ID + F(" CenterX:") + huskylens_result.xCenter + F(" CenterY:") + huskylens_result.yCenter), 0, 0);
                return true;
            }
        }
        return false;
    }
    bool detectID(short int ID)
    {
        return huskylens_scan(ID);
    }
    namespace init
    {
        // 这段函数用于哈士奇的初始化，如果初始化未成功将陷入循环，请在setup() 函数内调用
        void init()
        {
            huskylens_softwareSerial.begin(9600);
            while (!husky.begin(huskylens_softwareSerial))
            {
                Serial.println("HuskyLens not found,Please check connection and try again.");
                delay(1000);
            }
        }
    }
    // 用于合作的命名空间
    namespace cooperate
    {
        // 依据哈士奇识别的结果调整角度舵机的位置
        bool align(short int ID)
        {
            const float k = 0.8;
            const char sensitivity = 15; // 识别的精确度
            if (!husky_related::huskylens_scan(ID))
            {
                wheels.run(0, 0);
                husky.customText("No avaible Object Found", 0, 0);
                return false;
            }
            short int error = -1 * (huskylens_result.xCenter - husky_xm / 2); // 识别到的物体在哈士奇在屏幕上的误差
            if (abs(error) < sensitivity)
            {
                wheels.run(0, 0); // 如果在误差允许范围内->不动
            }
            else if (error > 0)
            {
                short int speed = constrain(abs(error) * k, 55, 100);
                wheels.run(speed, speed); // 前进
            }
            else if (error < 0)
            {
                short int speed = constrain(-1 * abs(error) * k, -100, -55);
                wheels.run(speed, speed); // 后退
            }
            delay(5);
            Serial.println(String("Aligning:") + String(error));
            // 计算误差
            husky_related::huskylens_scan(ID);
            short int NewError = huskylens_result.xCenter - husky_xm / 2;
            husky.customText("Error:" + String(NewError) + String(abs(NewError) < sensitivity ? " OK" : " Waiting"), 0, 0);
            return abs(error) < sensitivity;
        }
        bool avaiblility_check(short int ID, float percentage = 0.5, float less_percentage = 0.3)
        {
            const short int total = 50;
            short int sum = 0;
            for (int qi = 0; qi < total; qi++)
            {
                sum += align(ID) ? 1 : 0;
                if (1.0 * sum / qi > percentage && qi > less_percentage * total)
                {
                    return true;
                }
                Serial.println(String("Avability Check:") + String(1.0 * sum / qi));
            }
            return false;
        }
    }
}