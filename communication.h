#ifndef COMMUNICATION_H
#define COMMUNICATION_H
void communicationSetup();
void communicationLoop();
int getButton(int id);
int getButtonOnce(int id);
int* getSensor();
double getWaveDistance();
#endif // COMMUNICATION_H