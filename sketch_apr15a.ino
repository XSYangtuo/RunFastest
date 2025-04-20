// // 定义 L298N 控制引脚
// const int IN1 = 48;
// const int IN2 = 46;
// const int IN3 = 44;
// const int IN4 = 42;
// const int ENA = 10;
// const int ENB = 9;

// void setup() {
//   // 初始化串口通信，波特率为 9600
//   Serial.begin(9600);
//   // 设置引脚为输出模式
//   pinMode(IN1, OUTPUT);
//   pinMode(IN2, OUTPUT);
//   pinMode(IN3, OUTPUT);
//   pinMode(IN4, OUTPUT);
//   pinMode(ENA, OUTPUT);
//   pinMode(ENB, OUTPUT);

//   // 初始化电机速度
//   analogWrite(ENA, 200);
//   analogWrite(ENB, 200);
// }

// void loop() {
//   if (Serial.available() > 0) {
//     // 读取串口输入的字符
//     char input = Serial.read();
//     if (input == '1') {
//       // 控制左电机前进
//       digitalWrite(IN1, HIGH);
//       digitalWrite(IN2, LOW);

//       // 控制右电机前进
//       digitalWrite(IN3, HIGH);
//       digitalWrite(IN4, LOW);

//       // 小车前进一段时间，这里设置为 1 秒
//       delay(1000);

//       // 停止小车
//       digitalWrite(IN1, LOW);
//       digitalWrite(IN2, LOW);
//       digitalWrite(IN3, LOW);
//       digitalWrite(IN4, LOW);
//     }
//   }
// }  
#include"communication.h" 
#include "arms.h" 
void setup() {
  Serial.begin(9600);
  communicationSetup();
  armSetup();
}
void loop() {
  //Serial.println("loop");
  armLoop();
  if(Serial.available()>0){
    char serialGet = Serial.read();
    if(serialGet=='1'){
      armUp();
    }
    if(serialGet=='2'){
      armDown();
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
}