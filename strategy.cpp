#include<Arduino.h>
#include "communication.h"
#include "arms.h"
#include "wheel.h"

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
        stopWheel();
        return 0;
    }
    sums/=times;
    if(sums < 3){
        setWheel(basicSpeed*0.9, basicSpeed *1.2);
    }else if(sums > 3){
        setWheel(basicSpeed*1.2, basicSpeed*0.9);
    }else{
        setWheel(basicSpeed, basicSpeed);
    }
    return 1;
}