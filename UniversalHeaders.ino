#include "Servo\Arm.h"
#include "var.h"
#include "huskyControl.h"
void setup()
{
    Serial.begin(115200);    // HardwareSerial  init
    arms.init(arms_list, 7); // arms initlaization
    // husky_related::init::init(); // husky initlaization
}
void loop()
{
    while (DUBUGGING)
    {
        arms.test_arm();
    }
    arms.Slow_move(Arm_opreations::Arm_points::qti_points, 200); // qti line tracking arm position
    while (true)
    {
        qti_related::qti_run(); // 自动巡线
        // Serial.println(QTI_LOWDEG[0].getWeight());
    }
}