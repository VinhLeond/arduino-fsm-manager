//
//      IMPLEMENTING PWM Speed control (PENDING)
//
#pragma once
#ifndef Fan_H_
#define Fan_H_
#include "Arduino.h"
#include "I2C.h"
#include "I2C_Anything.h"
class Fan : public I2C
{
private:
    void Computing();
    int connection;
public:
    Fan(int addr,int port);
    ~Fan();
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

