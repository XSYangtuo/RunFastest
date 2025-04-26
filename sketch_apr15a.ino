#include"communication.h" 
#include "arms.h" 
#include "wheel.h"
#include "strategy.h"
void setup() {
  Serial.begin(9600);
  communicationSetup();
  wheelSetup();
  armSetup();
}
void loop() {
  //Serial.println("loop");
  armLoop();
  communicationLoop();
  strategyLoop();
  if(Serial.available()>0){
    char serialGet = Serial.read();
    if(serialGet=='1'){
      armUp();
    }
    if(serialGet=='2'){
      armDown();
    }
    if(serialGet=='3'){
      setWheel(70,0);
      delay(1000);
      setWheel(-70,0);
      delay(1000);
      setWheel(0,70);
      delay(1000);
      setWheel(0,-70);
      delay(1000);
      stopWheel();
    }
    if(serialGet=='4'){
      int* sensorStatus = getSensor();
      Serial.print(sensorStatus[0]);
      Serial.print(sensorStatus[1]);
      Serial.print(sensorStatus[2]);
      Serial.print(sensorStatus[3]);
      Serial.print(sensorStatus[4]);
      Serial.print(sensorStatus[5]);
      Serial.println(sensorStatus[6]);
    }
    if(serialGet == '5'){
      Serial.println(getWaveDistance());
    }
  }
  if(getButton(0)){
    Serial.println("button1");
  }
  if(getButton(1)){
    Serial.println("button2");
  }
  if(getButton(2)){
    Serial.println("button3");
  }
  if(getButtonOnce(0)){
    setStrategy(1);
    Serial.println("button1 once");
  }
  if(getButtonOnce(1)){
    Serial.println("button2 once");
    stopAllStrategy();
    stopWheel();
  }
  if(getButtonOnce(2)){
    Serial.println("button3 once");
     //setWheel(-70,70);
    
    setStrategy(0);
  }
}
// #include "wheel.h"
// #include "pins.h"
// // 编码器脉冲计数
// volatile long encoderLeftCount = 0;
// volatile long encoderRightCount = 0;

// // 上次测速时间
// unsigned long lastTime = 0;
// // 测速间隔（毫秒）
// const unsigned long interval = 100;

// // 编码器每转脉冲数
// const int pulsesPerRevolution = 11;  // 根据实际情况调整

// // 轮子周长（厘米）
// const float wheelCircumference = 20.0;  // 根据实际情况调整

// // 左编码器 A 相中断服务函数
// void leftEncoderAISR() {
//   if (digitalRead(PIN_encoderla) == digitalRead(PIN_encoderlb)) {
//     encoderLeftCount++;
//   } else {
//     encoderLeftCount--;
//   }
// }

// // 右编码器 A 相中断服务函数
// void rightEncoderAISR() {
//   if (digitalRead(PIN_encoderra) == digitalRead(PIN_encoderrb)) {
//     encoderRightCount++;
//   } else {
//     encoderRightCount--;
//   }
// }

// void setup() {
//   // 初始化串口通信
//   Serial.begin(9600);

//   // 设置编码器引脚为输入模式
//   pinMode(PIN_encoderla, INPUT_PULLUP);
//   pinMode(PIN_encoderlb, INPUT_PULLUP);
//   pinMode(PIN_encoderra, INPUT_PULLUP);
//   pinMode(PIN_encoderrb, INPUT_PULLUP);

//   // 附加中断服务函数
//   attachInterrupt(digitalPinToInterrupt(PIN_encoderla), leftEncoderAISR, CHANGE);
//   attachInterrupt(digitalPinToInterrupt(PIN_encoderra), rightEncoderAISR, CHANGE);

//   // 记录开始时间
//   lastTime = millis();
// }

// void loop() {
//   // setWheel(100,100);
//   unsigned long currentTime = millis();
//   if (currentTime - lastTime >= interval) {
//     // 保存当前脉冲计数
//     long leftCount = encoderLeftCount;
//     long rightCount = encoderRightCount;
//     Serial.print("Left Count: ");
//     Serial.println(leftCount);
//     // 重置脉冲计数
//     encoderLeftCount = 0;
//     encoderRightCount = 0;
//     // 计算速度（厘米/秒）
//     float leftSpeed = (leftCount / (float)pulsesPerRevolution) * wheelCircumference / (interval / 1000.0);
//     float rightSpeed = (rightCount / (float)pulsesPerRevolution) * wheelCircumference / (interval / 1000.0);

//     // 输出速度到串口
//     Serial.print("Left Speed: ");
//     Serial.print(leftSpeed);
//     Serial.print(" cm/s, Right Speed: ");
//     Serial.print(rightSpeed);
//     Serial.println(" cm/s");

//     // 更新上次测速时间
//     lastTime = currentTime;
//   }
// }    
