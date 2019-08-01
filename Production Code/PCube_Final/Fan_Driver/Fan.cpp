#include "Fan.h"

Fan::Fan(int addr,int port) :I2C(addr), connection(port){}

Fan::~Fan(){}

void Fan::config(){
    pinMode(connection, OUTPUT);
    digitalWrite(connection,LOW);
}

void Fan::initialize()
{
    busy=true;
    processing=true;
    Wire.begin(I2C::getAddress());
}

void Fan::setSpeed(int pwm){
    analogWrite(connection, (pwm*1.0/100)*255);
}

void Fan::turnOff(){
    analogWrite(connection, 0);
}

void Fan::bufData(int howMany)
{
    // I2C::setData();
    processing=false;
}

void Fan::send()
{
    I2C_writeAnything(I2C::bytes);
    busy=false;
}

/* STATIC METHOD */

