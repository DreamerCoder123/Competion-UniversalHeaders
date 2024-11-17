#pragma once
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include "Constants.h"
HUSKYLENS husky;                                 // X 320 Y 240
SoftwareSerial huskylens_softwareSerial(51, 52); // 哈士奇软串口接点
HUSKYLENSResult huskylens_result;                // 哈士奇结果存储
const short int husky_xm = 320;                  // 哈士奇x最大值320
const short int husky_ym = 240;                  // 哈士奇y最大值240
namespace husky_related
{
    bool huskylens_scan(short int ID) // 哈士奇扫描视野内的标签，返回特定标签值
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
                huskylens_result = husky.read(); // 传入的参数仅仅带有id
                Serial.println(String() + F("ID:") + huskylens_result.ID + F(" CenterX:") + huskylens_result.xCenter + F(" CenterY:") + huskylens_result.yCenter);
                husky.customText((String() + F("ID:") + huskylens_result.ID + F(" CenterX:") + huskylens_result.xCenter + F(" CenterY:") + huskylens_result.yCenter), 0, 0);
                return true;
            }
        }
        return false;
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
            const char sensitivity = 20; // 识别的精确度
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
                wheels.run(RUN_TOWARDS); // 前进
            }
            else if (error < 0)
            {
                wheels.run(RUN_AFTERWARDS); // 后退
            }
            delay(20); // 防止重复计算
            // 计算误差
            husky_related::huskylens_scan(ID);
            short int NewError = huskylens_result.xCenter - husky_xm / 2;
            husky.customText("Error:" + String(NewError) + String(abs(NewError) < sensitivity ? " OK" : " Waiting"), 0, 0);
            return abs(error) < sensitivity;
        }
    }
}