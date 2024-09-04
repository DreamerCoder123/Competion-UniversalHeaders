#include "qtis.h"
qtis myqti(8);
void setup(){
Serial.begin(115200);
}
void loop(){
    Serial.println(myqti.Getstatus());
}