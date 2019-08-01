//
//      IMPLEMENTING PWM Speed control (PENDING)
//
#pragma once
#ifndef Pump_H_
#define Pump_H_
#include "Arduino.h"
#include "I2C.h"
#include "I2C_Anything.h"
class Pump : public I2C
{
private:
    void Computing();
    int connection;
public:
    Pump(int addr,int port);
    ~Pump();
    void config();
    void initialize();
    void setSpeed(int pwm);
    void turnOff();
    volatile bool busy = false;
    volatile bool processing=false; 
    void bufData(int howMany=0);
    void send();
};
#endif

