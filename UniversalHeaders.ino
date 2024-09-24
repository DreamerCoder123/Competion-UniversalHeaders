#include "Servo\Arm.h"
#include "var.h"
#include "huskyControl.h"
DcMotor wheels(4,5,6,7);
void setup()
{
    Serial.begin(115200);
    arms.init(arms_list, 6);
    arms.Slow_move(Arm_opreations::Arm_points::GRABBER_READY, 200);
}
void loop()
{
    while (DUBUGGING)
    {
        arms.test_arm();
    }
    wheels.run(255,255);
}