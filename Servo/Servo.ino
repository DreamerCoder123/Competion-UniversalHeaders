#include "Arm.h"
short int recorded_end[]={2000,2000,2000};
short int recorded_start[]={1200,1402,1200};
Arm first_arm;
void setup(){
    Serial.begin(9600);
    short int array[3]={15,14,19};
    first_arm.init(array,3);//初始化手臂
}
void loop(){
    first_arm.Slow_move(recorded_end,40);
    first_arm.insistace(200);
    first_arm.Slow_move(recorded_start,40);
    first_arm.insistace(200);
}
