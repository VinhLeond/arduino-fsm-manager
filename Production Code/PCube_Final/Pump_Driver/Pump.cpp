#include "Pump.h"

Pump::Pump(int addr,int port) :I2C(addr), connection(port){}

Pump::~Pump(){}

void Pump::config(){
    pinMode(connection, OUTPUT);
    digitalWrite(connection,LOW);
}

void Pump::initialize()
{
    busy=true;
    processing=true;
    Wire.begin(I2C::getAddress());
}

void Pump::setSpeed(int pwm){
    analogWrite(connection, (pwm*1.0/100)*255);
}

void Pump::turnOff(){
    analogWrite(connection, 0);
}

void Pump::bufData(int howMany)
{
    // I2C::setData();
    processing=false;
}

void Pump::send()
{
    I2C_writeAnything(I2C::bytes);
    busy=false;
}

/* STATIC METHOD */

