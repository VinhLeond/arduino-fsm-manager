#include "Water_flow.h"
Water_flow* Water_flow::instance;
Water_flow::Water_flow(int addr,int port) :I2C(addr),connection(port)
{
    
}

Water_flow::~Water_flow(){}

void Water_flow::config(){
    pinMode(connection,INPUT);
}
void Water_flow::initialize()
{
    busy=true;
    processing=true;
    Wire.begin(I2C::getAddress());
}

float Water_flow::measurePWM()
{
    instance = this;
    attachPCINT(digitalPinToPCINT(connection), Water_flow::rising, RISING);
    counter = millis();
    while(rise_time==0){
        if(millis()- counter >= 10){
            flowrate=0;
            fall_time=0;
            return flowrate;
        }
    }
    while(fall_time==0);
    detachPCINT(digitalPinToPCINT(connection));
    rise_time=0;
    fall_time=0;
}

void Water_flow::computeFlow()
{
        frequency =1.0/(2*(pwm_value/(pow(10,6))));
        flowrate= frequency/65.0;
}

void Water_flow::bufData()
{
    measurePWM();
    I2C::setData(flowrate);
    processing=false;
}

void Water_flow::send()
{
    I2C_writeAnything(I2C::bytes);
    busy=false;
}

/* STATIC METHOD */
void Water_flow::rising()
{
        if (instance)
    {
        instance -> setRiseTime();
    }
}
void Water_flow::setRiseTime(){
    rise_time = micros();
    instance = this;
    attachPCINT(digitalPinToPCINT(connection), Water_flow::falling, FALLING);
}

void Water_flow::falling() {
        if (instance)
    {
        instance -> setFallTime();
    }
        
}
void Water_flow::setFallTime(){
    fall_time = micros();
    pwm_value=(fall_time-rise_time);
    if ((pwm_value < pow(10,8))&&(pwm_value>0))
    {
        computeFlow();
    }
    else{
        flowrate =0;
    }
}