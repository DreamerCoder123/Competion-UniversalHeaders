#include "Sonar.h"
Sonar test(5,4);
void setup()
{
    Serial.begin(9600);
}
void loop()
{
    Serial.println(test.avg_distance());
}