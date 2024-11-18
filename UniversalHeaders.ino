#include "Servo\Arm.h"
#include "Constants.h"
#include "huskyControl.h"
#define DEBUGGING false
#define point true
void setup()
{
    Serial.begin(115200);                            // HardwareSerial  init
    arms.init(arms_list, 7);                         // arms initlaization
    husky_related::init::init();                     // husky initlaization
    husky.writeAlgorithm(ALGORITHM_TAG_RECOGNITION); // 转换到标签识别模式
    Serial.println("huskyLens Ready!");              // 打印提示信息
    arms.Slow_move(Arm_opreations::qti_points, 50);
    while (DEBUGGING)
    {
        arms.QtConnection();                      // 启用于pythonQt的链接
        Serial.println("Warning Debugging Mode"); // 打印提示信息
    }
    while (point)
    {
        Arm_opreations::Chan_book::chanbook_left();
        // arms.insistace(1500);
        // Arm_opreations::Catch_Book::catchbook(1);
        // arms.insistace(1000);
        // Arm_opreations::Catch_Book::catchbook(2);
        // arms.insistace(3000);
        // Arm_opreations::Chan_book::chanbook(5);
        // Arm_opreations::Chan_book::release_book();
        // Arm_opreations::Chan_book::chanbook(6);
        // Arm_opreations::Chan_book::release_book();
    }
}
// ID1,2
void loop()
{
    qti_related::qti_run();
    if (husky_related::detectID(6))
    {
        wheels.run(RUN_TOWARDS);
        //检测到放置id=2的大书框
    }
    if (husky_related::detectID(1))
    {
        wheels.run(RUN_TOWARDS);
        while (true)
        {
            if (r_num <= 1)
            {
                while (!husky_related::cooperate::avaiblility_check(1))
                {
                    long long current_time = millis();
                    while (!husky_related::detectID(1))
                    {
                        // 如果丢失了目标
                        if (millis() - current_time > 2000)
                        {
                            // 丢失目标超过两秒
                            return;
                        }
                    }
                }
                // 对齐完毕
                Arm_opreations::Catch_Book::catchbook(1);
                break;
            }
            else
            {
                break;
            }
        }
    }
    if (husky_related::detectID(2))
    {
        wheels.run(RUN_TOWARDS);
        while (true)
        {
            if (l_num <= 1)
            {
                while (!husky_related::cooperate::avaiblility_check(2))
                {
                    long long current_time = millis();
                    while (!husky_related::detectID(1))
                    {
                        // 如果丢失了目标
                        if (millis() - current_time > 2000)
                        {
                            // 丢失目标超过两秒
                            return;
                        }
                    }
                }
                // 对齐完毕
                Arm_opreations::Catch_Book::catchbook(2);
                break;
            }
            else
            {
                break;
            }
        }
    }
}