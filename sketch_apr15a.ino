#include"communication.h" 
#include "arms.h" 
#include "wheel.h"
#include "strategy.h"
int straghting = 0;
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
  if(straghting == 1){
    straight(70);
  }
  if(Serial.available()>0){
    char serialGet = Serial.read();
    if(serialGet=='1'){
      armUp();
    }
    if(serialGet=='2'){
      armDown();
    }
    if(serialGet=='3'){
      setWheel(100,-100);
      delay(5000);
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
    Serial.println("button1 once");
    straghting = 1;
  }
  if(getButtonOnce(1)){
    Serial.println("button2 once");
    stopWheel();
    straghting = 0;
  }
  if(getButtonOnce(2)){
    Serial.println("button3 once");
  }
}
// 定义引脚
// const int sclkPin = 30;  // SCLK 时钟引脚
// const int rclkPin = 28;  // RCLK 锁存时钟引脚
// const int d10Pin = 26;  // D10 数据引脚（这里假定功能，可按需调整）

// // 数码管段码表，对应0 - 9数字显示（共阴极）
// byte digitCodes[] = {
//   B00111111, // 0
//   B00000110, // 1
//   B01011011, // 2
//   B01001111, // 3
//   B01100110, // 4
//   B01101101, // 5
//   B01111101, // 6
//   B00000111, // 7
//   B01111111, // 8
//   B01101111  // 9
// };

// void setup() {
//   Serial.begin(9600);
//   pinMode(sclkPin, OUTPUT);
//   pinMode(rclkPin, OUTPUT);
//   pinMode(d10Pin, OUTPUT);
// }

// // 函数：在指定数码管位置显示数字
// void displayDigit(int digitPos, int digit) {
//   digitalWrite(rclkPin, LOW);
//   // 这里简单模拟数据发送，实际需按通信协议调整
//   // 假设 D10 引脚用于发送位选信号
//   digitalWrite(d10Pin, (0x01 << digitPos)); 
//   // 发送段码，显示对应数字
//   for (int i = 0; i < 8; i++) {
//     digitalWrite(sclkPin, LOW);
//     if (digitCodes[digit] & (1 << i)) {
//       digitalWrite(d10Pin, HIGH);
//     } else {
//       digitalWrite(d10Pin, LOW);
//     }
//     delay(10);
//     digitalWrite(sclkPin, HIGH);
//   }
//   digitalWrite(rclkPin, HIGH);
// }

// void loop() {
//   // 在第0位数码管显示0
//   Serial.println("loop");
//   displayDigit(0, 0); 
//   delay(1000);
//   // 在第1位数码管显示1
//   displayDigit(1, 1); 
//   delay(1000);
//   // 在第2位数码管显示2
//   displayDigit(2, 2); 
//   delay(1000);
//   // 在第3位数码管显示3
//   displayDigit(3, 3); 
//   delay(1000);
// }