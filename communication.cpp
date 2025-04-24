#include<Arduino.h>
#include "pins.h"
int PIN_buttons[3] = {PIN_button1, PIN_button2, PIN_button3};
int PIN_sensors[7] = {PIN_gray1, PIN_gray2, PIN_gray3, PIN_gray4, PIN_gray5, PIN_gray6, PIN_gray7};
int button_Status[3] = {0, 0, 0};//0没按下，1按下但还没被函数调用，2按下且已经有调用
int sensor_Status[7] = {0, 0, 0, 0, 0, 0, 0};//0是白色，1是黑色
void communicationSetup(){
    //按钮
    pinMode(PIN_buttons[0], INPUT_PULLUP);
    pinMode(PIN_buttons[1], INPUT_PULLUP);
    pinMode(PIN_buttons[2], INPUT_PULLUP);
    //超声波
    pinMode(PIN_waveTrig, OUTPUT);
    pinMode(PIN_waveEcho, INPUT);
    //灰度传感器
    for(int i=0;i<7;i++){
        pinMode(PIN_sensors[i], INPUT);
    }
}
void communicationLoop(){
    for(int i = 0; i < 3; i++){
        int Statusi = digitalRead(PIN_buttons[i]) == LOW;
        if(Statusi&&button_Status[i] == 0){
            button_Status[i] = 1;
        } else if(Statusi == 0){
            button_Status[i] = 0;
        }
    }
}
// 只在每次按下时第一次调用返回一次true
int getButtonOnce(int id){
    if(button_Status[id] == 1){
        button_Status[id] = 2;
        return 1;
    }
    return 0;
}
int getButton(int id){
    return  button_Status[id] > 0;
}
int* getSensor(){
    for(int i = 0; i < 7; i++){
        sensor_Status[i] = (digitalRead(PIN_sensors[i]) == HIGH);
        //如果在室内测试，要反过来，因为是黑线
        //sensor_Status[i] = 1-sensor_Status[i];
    }
    return sensor_Status;
}
double getWaveDistance(){
    long duration;
    float distance;

    // 发送超声波信号
    digitalWrite(PIN_waveTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_waveTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_waveTrig, LOW);

    // 读取返回信号时间（单位微秒）
    duration = pulseIn(PIN_waveEcho, HIGH);

    // 计算距离 (声音传播速度为 0.034 cm/us, 往返时间除以2)
    distance = duration * 0.034 / 2;

    return distance;
}