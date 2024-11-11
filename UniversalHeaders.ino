#include "Servo\Arm.h"
#include "Constants.h"
#include "huskyControl.h"
#define DEBUGGING false
void setup()
{
    Serial.begin(115200);                            // HardwareSerial  init
    arms.init(arms_list, 7);                         // arms initlaization
    // husky_related::init::init();                     // husky initlaization
    husky.writeAlgorithm(ALGORITHM_TAG_RECOGNITION); // 转换到标签识别模式
    Serial.println("huskyLens Ready!");              // 打印提示信息
    while (DEBUGGING)
    {
        arms.QtConnection(); // 启用于pythonQt的链接
    }
}
void loop()
{
    
}