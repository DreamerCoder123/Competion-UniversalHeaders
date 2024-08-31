#include "DcMotor.h"
DcMotor mymotor(3,11,9,10);
void setup()
{
}
void loop()
{
    mymotor.run(255,255);
}