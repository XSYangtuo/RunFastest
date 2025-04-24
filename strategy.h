#ifndef STRATEGY_H
#define STRATEGY_H
void setStrategy(int id);
void strategyLoop();
void stopAllStrategy();
int straight(int basicSpeed);
int turn(int basicSpeed, int direction);
double sensorDirection();
#endif