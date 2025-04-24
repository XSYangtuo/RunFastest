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
#define WAVE 5//超声波触发
#define END -1//结束
int strategyGroup[1][100]{
    {WAVE,ARM_DOWN,ST,ST,RT,ST,ST,RT,ST,ST,RT,ST,ST,ARM_UP,END}
};
int nowStrategy = -1;
int nowStrategyIndex = 0;
// 方向，3是正中，0是左边，6是右边,-1全白,-2全黑
double sensorDirection(){
    int* sensorStatus = getSensor();
    double sums = 0;
    int times = 0;
    for(int i = 0; i < 7; i++){
        if(sensorStatus[i] == 0){
            sums +=i;
            times+=1;
        }
    }
    if(times == 0) return -2;
    if(times == 7) return -1;
    return sums/times;
}
//前进一格
int straight(int basicSpeed){
    int* sensorStatus = getSensor();
    double sums = sensorDirection();
    if(sums == -1){//全白或者全黑
        Serial.println("all white");
        //setWheel(basicSpeed*0.5, basicSpeed*0.5);
        // while(getSensor()[0] == 1 && nowStrategy != -1)
        //     delay(10);
        //delay(1000);
        stopWheel();
        delay(300);
        return 1;
    }
    if(sums == -2){
        Serial.println("all black");
        setWheel(-basicSpeed, -basicSpeed);
        return 0;
    }
    //用一个变量控制乘数，满足sums=3的时候为0，sums为0的时候为-0.3，sums为6时为+0.3
    double changeC = (sums - 3) * 0.08;
    setWheel(basicSpeed*(1+changeC), basicSpeed*(1-changeC));
    // if(sums < 3){
    //     setWheel(basicSpeed*0.9, basicSpeed *1.2);
    // }else if(sums > 3){
    //     setWheel(basicSpeed*1.2, basicSpeed*0.9);
    // }else{
    //     setWheel(basicSpeed, basicSpeed);
    // }
    return 0;
}
//转弯
int turn(int basicSpeed, int direction){//1向左2向右
    if(direction == 2){
        setWheel(basicSpeed, 0);
    }else{
        setWheel(0, basicSpeed);
    }
    delay(600);
    // while(sensorDirection() == -2)
    //     delay(10);
    stopWheel();
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
    case WAVE:
        if(getWaveDistance() < 4){
            //Serial.println(getWaveDistance());
            delay(500);//防止超声波抖动
            if(getWaveDistance() < 4)
                nowStrategyIndex++;
        }
        break;
    default:
        break;
    }
}
void stopAllStrategy(){
    nowStrategy = -1;
    stopWheel();
}