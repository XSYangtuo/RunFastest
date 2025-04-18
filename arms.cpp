#include<Arduino.h>
#include <Servo.h>
#include "pins.h"
// 创建舵机对象
Servo servoLeft;
Servo servoRight;
// 定义单向门控制引脚
const int servoPin = 6;
int leftDegreeNow = 90;//当前角度
int leftTargetdegree = 90;//目标角度
void armUp(){
    leftTargetdegree = 90;
}
void armDown(){
    leftTargetdegree = 180;
}
void armLoop(){
    // while (degreeNow < targetdegree) {
    //     degreeNow++;
    //     servoLeft.write(degreeNow);
    //     delay(10);
    //   }
    //   while (degreeNow > targetdegree) {
    //     degreeNow--;
    //     servoLeft.write(degreeNow);
    //     delay(10);
    //   }
    while (leftDegreeNow < leftTargetdegree) {
        leftDegreeNow++;
        servoLeft.write(leftDegreeNow);
        servoRight.write(180-leftDegreeNow);
        delay(10);
    }
    while (leftDegreeNow > leftTargetdegree) {
        leftDegreeNow--;
        servoLeft.write(leftDegreeNow);
        servoRight.write(180-leftDegreeNow);
        delay(10);
    }
}
void armSetup() {
  // 将舵机连接到指定引脚
  servoLeft.attach(PIN_armleft);
  servoRight.attach(PIN_armright);
}
