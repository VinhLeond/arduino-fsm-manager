#include "Soil_Moisture.h"
Soil_Moisture* Soil_Moisture::instance;

Soil_Moisture::Soil_Moisture(int addr,int port) :I2C(addr){
    connection=port;
    pinMode(port,INPUT);
}

Soil_Moisture::~Soil_Moisture(){}

void Soil_Moisture::initialize()
{
    busy=true;
    instance = this;
    Wire.begin(I2C::getAddress());
    Wire.onReceive(Soil_Moisture::receiveEvent);
    Wire.onRequest(Soil_Moisture::requestEvent);
}
float Soil_Moisture::readHumidity()
{
    humidity=analogRead(connection)*(5.0/1024);
    return humidity;
}

void Soil_Moisture::bufData(int howMany)
{
    readHumidity();
    I2C::setData(humidity);
}

void Soil_Moisture::send()
{
    // byte* ptr;
    // ptr=I2C::getData();
    // byte ptr[4]={0x00,0x12,0x22,0xFF};
    // Serial.println("\n Start Sending");
    // for (int i=0; i<=3; i++){
    //     Serial.print(ptr[i]);
    // }
    I2C::setData(humidity);
    I2C_writeAnything(I2C::bytes);
    busy=false;
}

/* STATIC METHOD */


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void Soil_Moisture::receiveEvent(int howMany)
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
void Soil_Moisture::requestEvent()
{
    if (instance)
    {
        instance -> send();
    }
    
}
