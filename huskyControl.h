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
                // husky.customText((String() + F("ID:") + huskylens_result.ID + F(" CenterX:") + huskylens_result.xCenter + F(" CenterY:") + huskylens_result.yCenter), 0, 0);
            }
        }
        return false;
    }

    void process_husky_result(short int ID)
    {
        //! 获取最右边的方块
        HUSKYLENSResult t_data[10];
        short int length = husky.countBlocks(ID); // 获取识别到的ID的数量
        for (int i = 0; i < length; i++)
        {
            huskylens_scan(ID);           // 扫描
            t_data[i] = huskylens_result; // 获取结果并存储到数组
        }
        // 获取t_data中中心点的x坐标的最大值
        HUSKYLENSResult max_data = t_data[0];
        for (int i = 1; i < length; i++)
        {
            if (t_data[i].xCenter > max_data.xCenter)
            {
                max_data = t_data[i];
            }
        }
        // 获取到了最大值，也就是最右边的方块
        huskylens_result = max_data;
        Serial.println(String() + F("ID:") + huskylens_result.ID + F(" CenterX:") + huskylens_result.xCenter + F(" CenterY:") + huskylens_result.yCenter);
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
        bool align(short int ID, short int secret)
        {
            huskylens_scan(ID);//!勿删
            const char sensitivity = 15;                                 // 识别的精确度
            short int error = (huskylens_result.xCenter - husky_xm / 2); // 识别到的物体在哈士奇在屏幕上的误差
            if (husky.count(ID) == 0)
            {
                // 如果没有识别到物体，则不进行任何操作
                wheels.run(0, 0);
                return false;
            }
            huskylens_scan(ID);

            if (abs(error) < sensitivity)
            {
                wheels.run(0, 0); // 如果在误差允许范围内->不动
            }
            else if (error > 0)
            {
                wheels.run(RUN_TOWARDS); // 前进
                Serial.println("向前行进");
            }
            else if (error < 0)
            {
                wheels.run(RUN_AFTERWARDS); // 后退
                Serial.println("向后倒车");
            }
            delay(20);
            husky_related::huskylens_scan(ID);
            process_husky_result(ID);
            short int NewError = huskylens_result.xCenter - husky_xm / 2;
            husky.customText(String(NewError) + "secret:" + String(secret), 0, 0);
            return abs(error) < sensitivity;
        }
        // 是否可以发放下架子
        bool Acessbility(short int ID)
        {
            while (true)
            {
                align(ID, 0);
                // short int sum = 0;
                // for (int secret = 0; secret < 20; secret++)
                // {
                //     if (sum > 10)
                //     {
                //         Serial.println("对齐成功，可以发放下");
                //         return true;
                //     }
                // }
                // Serial.println("正在循环中... 对齐函数Accessbility()");
            }
        }
    }
}