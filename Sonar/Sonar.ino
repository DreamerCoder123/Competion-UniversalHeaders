#include "Sonar.h"
Sonar mySonar(5,4);
void setup()
{
    Serial.begin(9600);
}
void loop()
{
    Serial.println(mySonar.avg_distance());
}