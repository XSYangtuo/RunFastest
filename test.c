


// // 定义一个数组来存储 7 个灰度传感器引脚
// const int grayscalePins[7] = {31, 33, 35, 37, 39, 41, 43};
// const int buttonPins[3] = {3,5,6};
// // 定义一个数组来存储每个引脚读取到的值
// int grayscaleValues[7];

// void setup() {
//     // 初始化串口通信，波特率为 9600
//     Serial.begin(9600);

//     // 遍历数组，将每个引脚设置为输入模式
//     for (int i = 0; i < 7; i++) {
//         pinMode(grayscalePins[i], INPUT);
//     }
//     for (int i = 0; i < 3; i++) {
//         pinMode(buttonPins[i], INPUT);
//     }
// }

// void loop() {
//     // 遍历数组，读取每个引脚的数字值
//     for (int i = 0; i < 7; i++) {
//         grayscaleValues[i] = digitalRead(grayscalePins[i]);
//     }

//     // 遍历数组，打印每个引脚读取到的值
//     for (int i = 0; i < 7; i++) {
//         Serial.print(grayscaleValues[i]);
//     }
//     for (int i = 0; i < 3; i++) {
//         Serial.print(digitalRead(buttonPins[i]));
//     }
//     Serial.println();

//     // 延迟一段时间，避免数据读取过于频繁
//     delay(100);
// }  
// #include <Servo.h>
// #include<Arduino.h>
// // 创建舵机对象
// Servo myServo;

// // 定义舵机控制引脚
// const int servoPin = 6;

// void setup() {
//   // 初始化串口通信，波特率为 9600
//   Serial.begin(9600);
//   // 将舵机连接到指定引脚
//   myServo.attach(servoPin);
// }

// //以上代码让电机一下子转90度，太快了，要写一个让它转的慢一点的代码
// int degreeNow = 90;//当前角度
// int targetdegree = 90;//目标角度
// void loop() {
//   // 检查串口是否有可用的数据
//   if (Serial.available() > 0) {
//     // 读取串口接收到的字符
//     char nowStatus = Serial.read();
//     if (nowStatus == '0') {
//       // 舵机转动到 0 度
//       targetdegree = 0;
//     }
//     else if (nowStatus == '9') {
//       // 舵机转动到 90 度
//       targetdegree = 90;
//     }
//     else if (nowStatus == '1') {
//       // 舵机转动到 180 度，这里是翻下来的位置
//       targetdegree = 180;
//     }
//   }
//     while (degreeNow < targetdegree) {
//       degreeNow++;
//       myServo.write(degreeNow);
//       delay(10);
//     }
//     while (degreeNow > targetdegree) {
//       degreeNow--;
//       myServo.write(degreeNow);
//       delay(10);
//     }
// }