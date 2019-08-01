#pragma once
#ifndef Water_Level_H_
#define Water_Level_H_
#include "Arduino.h"
#include "I2C.h"
#include "I2C_Anything.h"
class Water_Level : public I2C
{
private:
    void computing();
    String buffer = "";
public:
    Water_Level(int addr);
    ~Water_Level();
    void initialize();
    void config();
    float readDistance();
    float waterLevel;
    volatile bool busy = false;
    volatile bool processing = false;
    void bufData(int howMany=0);
    void send();
    long distance;
};
#endif

