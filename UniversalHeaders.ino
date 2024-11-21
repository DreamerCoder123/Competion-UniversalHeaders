#include "Servo\Arm.h"
#include "Constants.h"
#include "huskyControl.h"
#define DEBUGGING false
long long current_timec = millis();
long long current_time_husky = millis();
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
}
bool while_catch(short int id)
{
    if (husky_related::detectID(id))
    {
        wheels.run(RUN_TOWARDS);
        while (true)
        {
            if (((id) == 1) ? (r_num != 2) : (l_num != 2)) // 自动检测
            {
                while (!husky_related::cooperate::avaiblility_check(id))
                {
                    long long current_time = millis();
                    current_timec = current_time;
                    while (!husky_related::detectID(id))
                    {
                        // 如果丢失了目标
                        if (millis() - current_time > 2000)
                        {

                            // 丢失目标超过两秒
                            return false;
                        }
                    }
                }
                // 对齐完毕
                Arm_opreations::Catch_Book::catchbook(id);
                return true;
            }
            else
            {
                return false;
                husky.customText("No empty book space", 0, 0);
            }
        }
    }
}
void while_chan(short int id)
{
    char Bookshelf = (id == 1) ? 7 : 6;
    // 如果检测到放置id=2的整齐书框
    if ((Bookshelf == 7 ? r_num : l_num) != 0)
    {

        // 如果左边或右边有书
        long long current_time = millis();
        while (!husky_related::cooperate::avaiblility_check(Bookshelf))
        {
            if (current_time - millis() > 2000)
            {
                // 丢失目标超过两秒
                return;
            }
        }
        // 对齐完毕
        Arm_opreations::Chan_book::chanbook(Bookshelf);
    }
    else
    {
        qti_related::qti_run();
        husky.customText("No ok book for " + String(Bookshelf), 0, 0);
    }
}

void loop()
{
    qti_related::qti_run();
    if (husky_related::detectID(6))
    {
        wheels.run(RUN_TOWARDS);
        // 检测到放置id=2的大书框
    }
    if (husky_count > 0)
    {
        current_time_husky = millis();
    }
    // 速度控制
    if (millis() - current_time_husky > 3000)
    {
        // 3秒没有检测到标签，提升速度
        speedLeft = 75;
        speedRight = 75;
    }
    else
    {
        speedLeft = 85;
        speedRight = 85;
    }
    current_timec = millis();
    if (husky_related::detectID(5))
    {
        while (millis() - current_timec < 4000 && (l_num != 2 || r_num != 2))
        {
            qti_related::qti_run();
            while_catch(1);
            while_catch(2);
            // 检测到乱书框内的书
            current_timec = millis();
            // 抓取1，2号书
        }
        // 如果在5秒内没有检测到目标，则放弃抓取
    }
    if (husky_related::detectID(6))
    {
        while (millis() - current_timec < 5000)
        {
            while_chan(2);
        }
    }
    if (husky_related::detectID(7))
    {
        while (millis() - current_timec < 5000)
        {
            while_chan(1);
        }
    }
}