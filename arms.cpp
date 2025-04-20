#include<Arduino.h>
#include <Servo.h>
#include "pins.h"
// 创建舵机对象
Servo servoLeft;
Servo servoRight;
int leftDegreeNow = 90;//当前角度
int leftTargetdegree = 90;//目标角度
void armUp(){
    leftTargetdegree = 90;
}
void armDown(){
    leftTargetdegree = 180;
}
void armLoop(){
    while (leftDegreeNow < leftTargetdegree) {
        leftDegreeNow++;
        servoLeft.write(leftDegreeNow);
        // 注意两个舵机的转向相反
        servoRight.write(180-leftDegreeNow);
        delay(10);
        Serial.print("leftDegreeNow:");
        Serial.println(leftDegreeNow);
    }
    while (leftDegreeNow > leftTargetdegree) {
        leftDegreeNow--;
        servoLeft.write(leftDegreeNow);
        servoRight.write(180-leftDegreeNow);
        delay(10);
        Serial.print("leftDegreeNow:");
        Serial.println(leftDegreeNow);
    }
}
void armSetup() {
  // 将舵机连接到指定引脚
  servoLeft.attach(PIN_armleft);
  servoRight.attach(PIN_armright);
}
