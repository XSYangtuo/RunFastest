#include<Arduino.h>
#include "pins.h"
void communicationSetup(){
    pinMode(PIN_buttons[0], INPUT_PULLUP);
    pinMode(PIN_buttons[1], INPUT_PULLUP);
    pinMode(PIN_buttons[2], INPUT_PULLUP);
}
int getButton(int id){
    return  digitalRead(PIN_buttons[id]) == LOW;
}