#include<Arduino.h>
#include "communication.h"
#include "arms.h"
#include "wheel.h"
#include "strategy.h"
#define ST 0 //直行一格
#define LF 1//左转
#define RT 2//右转
#define ARM_DOWN 3//放下
#define ARM_UP 4//抬起
#define END -1//结束
int strategyGroup[1][100]{
    {ST,ST,LF,ST,ST,LF,ST,ST,LF,ST,ST,END}
};
int nowStrategy = -1;
int nowStrategyIndex = 0;

int straight(int basicSpeed){
    int* sensorStatus = getSensor();
    double sums = 0;
    int times = 0;
    for(int i = 0; i < 7; i++){
        if(sensorStatus[i] == 0){
            sums +=i;
            times+=1;
        }
    }
    if(sums == 21){//全白
        setWheel(basicSpeed, basicSpeed);
        while(getSensor()[0] == 0 && nowStrategy != -1)
            delay(10);
        stopWheel();
        delay(1000);
        return 1;
    }
    sums/=times;
    if(sums < 3){
        setWheel(basicSpeed*0.9, basicSpeed *1.2);
    }else if(sums > 3){
        setWheel(basicSpeed*1.2, basicSpeed*0.9);
    }else{
        setWheel(basicSpeed, basicSpeed);
    }
    return 0;
}
int turn(int basicSpeed, int direction){//1向左2向右
    if(direction == 2){
        setWheel(basicSpeed, 0);
        delay(600);
        stopWheel();
    }else{
        setWheel(0, basicSpeed);
        delay(600);
        stopWheel();
    }
}

void setStrategy(int id){
    nowStrategy = id;
    nowStrategyIndex = 0;
}
void strategyLoop(){
    if(nowStrategy == -1){
        return;
    }
    switch (strategyGroup[nowStrategy][nowStrategyIndex])
    {
    case END:
        nowStrategy = -1;
        return;
        break;
    case ST:
        if(straight(70)){
            // Serial.println("!!!");
            nowStrategyIndex++;
        }
        break;
    case LF:
        turn(100, 1);
        nowStrategyIndex++;
        break;
    case RT:
        turn(100, 2);
        nowStrategyIndex++;
        break;
    case ARM_DOWN:
        armDown();
        nowStrategyIndex++;
        break;
    case ARM_UP:
        armUp();
        nowStrategyIndex++;
        break;
    default:
        break;
    }
}
void stopAllStrategy(){
    nowStrategy = -1;
    stopWheel();
}