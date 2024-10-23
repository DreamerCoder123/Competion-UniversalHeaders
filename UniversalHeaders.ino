#include "Servo\Arm.h"
#include "var.h"
#include "huskyControl.h"
#define DEBUGGING false
void setup()
{
    Serial.begin(115200);                            // HardwareSerial  init
    arms.init(arms_list, 7);                         // arms initlaization
    husky_related::init::init();                     // husky initlaization
    husky.writeAlgorithm(ALGORITHM_TAG_RECOGNITION); // 转换到标签识别模式
    arms.Slow_move(Arm_opreations::Arm_points::qti_points, 100);
    while (DEBUGGING)
    {
        arms.QtConnection();
    }
    
}
void loop()
{
    Arm_opreations::catchbook_right();
    Arm_opreations::catchbook_right_();
}
