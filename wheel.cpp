#include<Arduino.h>
#include "pins.h"
void wheelSetup(){
    pinMode(L298N_IN1, OUTPUT);
    pinMode(L298N_IN2, OUTPUT);
    pinMode(L298N_IN3, OUTPUT);
    pinMode(L298N_IN4, OUTPUT);
    pinMode(L298N_ENA, OUTPUT);
    pinMode(L298N_ENB, OUTPUT);
}
void setWheel(int left,int right){
    if(left<0){
        digitalWrite(L298N_IN1, HIGH);
        digitalWrite(L298N_IN2, LOW);
    }else{
        digitalWrite(L298N_IN1, LOW);
        digitalWrite(L298N_IN2, HIGH);
    }
    if(right<0){
        digitalWrite(L298N_IN3, HIGH);
        digitalWrite(L298N_IN4, LOW);
    }else{
        digitalWrite(L298N_IN3, LOW);
        digitalWrite(L298N_IN4, HIGH);
    }
    analogWrite(L298N_ENA, left>0?left:-left);
    analogWrite(L298N_ENB, right>0?right:-right);
}
void stopWheel(){
    digitalWrite(L298N_IN1, LOW);
    digitalWrite(L298N_IN2, LOW);
    digitalWrite(L298N_IN3, LOW);
    digitalWrite(L298N_IN4, LOW);
}