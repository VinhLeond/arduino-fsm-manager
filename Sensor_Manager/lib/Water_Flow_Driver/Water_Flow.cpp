#include "Water_Flow.h"
#include "PinChangeInt.h"
Water_Flow* Water_Flow::instance;

Water_Flow::Water_Flow(int addr,int port) :I2C(addr)
{
    connection=port;
    pinMode(port,INPUT);
}

Water_Flow::~Water_Flow(){}


void Water_Flow::initialize()
{
    busy=true;
    instance = this;
    Wire.begin(I2C::getAddress());
    Wire.onReceive(Water_Flow::receiveEvent);
    Wire.onRequest(Water_Flow::requestEvent);
}

float Water_Flow::measurePWM()
{
    instance = this;
    attachPinChangeInterrupt(connection, Water_Flow::rising, RISING);
    int timeout=millis();
    while(fall_time==0){
        if(millis()-timeout>=100){
            break;
        }
    }
    detachPinChangeInterrupt(connection);
    pwm_value=(fall_time-rise_time);
    if ((pwm_value < pow(10,8))&&(pwm_value>0))
    {
        computeFlow();
    }
    else
    {
        flowrate = 0;
    }
    Serial.print("FlowRate:"); Serial.println(flowrate);
    I2C::setData(flowrate); 
    rise_time=0;
    fall_time=0;
    return flowrate;
}

void Water_Flow::computeFlow()
{
        frequency =1.0/(2*(pwm_value/(pow(10,6))));
        flowrate= frequency/65.0;
}

void Water_Flow::bufData(int howMany)
{
    measurePWM();
    I2C::setData(flowrate);
}

void Water_Flow::send()
{
    // byte* ptr;
    // ptr=I2C::getData();
    // byte ptr[4]={0x00,0x12,0x22,0xFF};
    // Serial.println("\n Start Sending");
    // for (int i=0; i<=3; i++){
    //     Serial.print(ptr[i]);
    // }
    I2C::setData(flowrate);
    I2C_writeAnything(I2C::bytes);
    busy=false;
}

/* STATIC METHOD */
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void Water_Flow::receiveEvent(int howMany)
{
    if (instance)
    {
        Serial.println("Received Command");
        int inData = Wire.read();
        // Serial.println(inData);
        instance -> bufData(howMany);
    }

}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void Water_Flow::requestEvent()
{
    if (instance)
    {
        instance -> send();
    }
    
}

void Water_Flow::rising()
{
        if (instance)
    {
        instance -> setRiseTime();
    }
}
void Water_Flow::setRiseTime(){
    rise_time = micros();
    // Serial.println(rise_time);
    instance = this;
    attachPinChangeInterrupt(connection, Water_Flow::falling, FALLING);
}

void Water_Flow::falling() {
        if (instance)
    {
        // Serial.println("Fall");
        instance -> setFallTime();
    }
        
}
void Water_Flow::setFallTime(){
    fall_time = micros();
    // Serial.println(fall_time);
}