#include "Air_CO2.h"
#define BAUDRATE 9600
#define AIRCO2 0
#define TEMP 1
Air_CO2* Air_CO2::instance;
static MHZ19 sensorMHZ19;
static SoftwareSerial dataStream (11,10);
// Stream* test = dataStream;
unsigned long getTimer = 0 ;

Air_CO2::Air_CO2(int addr) :I2C(addr)
{
    
    paraType = AIRCO2;

}

void Air_CO2::initialize(bool calib) 
{
    instance = this;
    AC = calib;
    Wire.begin(I2C::getAddress());
    Wire.onReceive(Air_CO2::receiveEvent);
    Wire.onRequest(Air_CO2::requestEvent);
    dataStream.begin(BAUDRATE);
    sensorMHZ19.begin(dataStream);
    if (AC==true)
    {
        sensorMHZ19.autoCalibration();
    }
    sensorMHZ19.autoCalibration();
    Serial.println(sensorMHZ19.getCO2());
}

Air_CO2::~Air_CO2(){}

float Air_CO2::readCO2()
{   
    // Serial.println("get CO2");
    //Can't be called through static instance pointer
    CO2 = sensorMHZ19.getCO2();
    Serial.println(CO2);
    // Serial.println("DONE");
    return CO2;
}

float Air_CO2::readTemp()
{     
    Temp = sensorMHZ19.getTemperature();
    Serial.println(Temp);
    return Temp;
}

void Air_CO2::setDataType(int dataType)
{
    paraType = dataType;
}

void Air_CO2::bufData(int howMany)
{
    
    if (paraType == AIRCO2)
    {
        readCO2();
        Serial.println("Updating CO2");
        I2C::setData(CO2);
    }
    else if (paraType == TEMP)
    {
        readTemp();
        Serial.println("Updating TEMP");
        I2C::setData(Temp);
    }
}

void Air_CO2::send()
{
    I2C_writeAnything(I2C::bytes);
}

bool Air_CO2::checkStatus()
{
    return done;
}
/* STATIC METHOD */
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void Air_CO2::receiveEvent(int howMany)
{
    if (instance){
        Serial.println("Received Command");
        int inData = Wire.read();
        // Serial.println(inData);
        instance -> bufData(howMany);
    }
}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void Air_CO2::requestEvent()
{
    if (instance){
        instance -> send();
    }
}
