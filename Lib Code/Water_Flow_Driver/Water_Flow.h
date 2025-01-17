#pragma once
#ifndef Water_flow_H_
#define Water_flow_H_

#define timeOut 200000 //200ms

#include "Arduino.h"
#include "I2C.h"
#include "I2C_Anything.h"
#include "PinChangeInterrupt.h"
class  Water_flow : public I2C
{
private:    
    static Water_flow* instance;
    void computeFlow();
    int connection;
    static void rising();
    static void falling();
    void setRiseTime();
    void setFallTime();
    volatile int rise_time = 0;
    volatile int fall_time = 0;
    long pwm_value;
    uint8_t latest_interrupted_pin;
    long frequency;
    volatile int counter;
public:
    Water_flow(int addr,int port);
    ~Water_flow();
    void config();
    void initialize();
    float measurePWM();
    float flowrate;
    void bufData();
    void send();
    volatile bool busy=false;
    volatile bool processing=false;
};
#endif

