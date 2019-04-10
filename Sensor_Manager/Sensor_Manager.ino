#include <Arduino.h>
#include "Water_flow.h"
#include "Soil_Moisture.h"
#include "Air_CO2.h"
#include "Air_Moisture.h"
#include "Air_Temp.h"
#include "Water_Level.h"

#define soilPin A0
#define aMoisPin A1
#define aTempPin A2
#define flowPin 7
#define CO2Rx 8
#define CO2Tx 9
#define levelPin A3


#define soilAddr 0x08
#define aMoisAddr 0x09
#define aTempAddr 0x10
#define CO2Addr  0x11
#define flowAddr 0x12
#define defAddr 0x07
#define levelAddr 0x13

volatile int machineAddr = defAddr;

#define timeout 300
volatile bool busy = true;
int counter;
Soil_Moisture sensor_Soil(soilAddr,soilPin);
Air_Moisture sensor_aMois(aMoisAddr,aMoisPin);
Air_Temp sensor_aTemp(aTempAddr,aTempPin);
Air_CO2 sensor_CO2(CO2Addr,true);
Water_flow sensor_flow(flowAddr,flowPin);
Water_Level sensor_level(levelAddr,levelPin);

void setup()
{
    Serial.begin(9600);
//    sensor_CO2.config();
    listening();
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void listening(){
    Wire.begin(defAddr);
    busy=true;
}

void receiveEvent(int howMany){
  while(Wire.available()){
    machineAddr = Wire.read();
  }
    Serial.println(machineAddr);
    busy=false;
}

void loop(){ 
    switch (machineAddr)
    {
        case defAddr:
            listening();
            Serial.println("Idle");
            while(busy==true);
            break;
        case soilAddr:
            Serial.println("SoilMoisture");
            sensor_Soil.initialize();
            sensor_Soil.bufData();
            while(sensor_Soil.busy);
            machineAddr=defAddr;
//            counter=millis();
//            while (sensor_Soil.busy);
//            Serial.println("Done");
            break;
        case aMoisAddr:
            Serial.println("AirMoist");
            sensor_aMois.initialize();
            sensor_aMois.bufData();
            while(sensor_aMois.busy);
            machineAddr=defAddr;
            break;
        case aTempAddr:
            Serial.println("AirTemp");
            sensor_aTemp.initialize();
            sensor_aTemp.bufData();
            while(sensor_aTemp.busy);
            machineAddr=defAddr;
            break;
        case CO2Addr:
            Serial.println("CO2");
            sensor_CO2.initialize();
            sensor_CO2.bufData();
            while(sensor_CO2.busy);
            machineAddr=defAddr;
//            while (sensor_CO2.busy);
//            Serial.println("Done");
            break;
        case flowAddr:
            Serial.println("flow");
            sensor_flow.initialize();
            sensor_flow.bufData();
            while(sensor_flow.busy);
            machineAddr=defAddr;
//            while (sensor_flow.busy);
//            Serial.println("Done");
            break;
        case levelAddr:
            Serial.println("level");
            sensor_level.initialize();
            sensor_level.bufData();
            while(sensor_level.busy);
            machineAddr=defAddr;
            break;
        default:
            break;
    }
}

void requestEvent(){
      switch (machineAddr)
    {
        case defAddr:
            break;
        case soilAddr:
            while(sensor_Soil.processing);
            sensor_Soil.send();
//            Serial.println("Sent Moisture");
//            Serial.println(sensor_Soil.humidity);
            break;
        case aMoisAddr:
            while(sensor_aMois.processing);
            sensor_aMois.send();
//            Serial.println("Sent Moisture");
//            Serial.println(sensor_aMois.humidity);
            break;
        case aTempAddr:
            while(sensor_aTemp.processing);
            sensor_aTemp.send();
//            Serial.println("Sent Temperature");
//            Serial.println(sensor_aTemp.Temp);        
            break;
        case CO2Addr:
            while(sensor_CO2.processing);
            sensor_CO2.send();
//            Serial.println("Sent CO2");
//            Serial.println(sensor_CO2.CO2);
            break;
        case flowAddr:
            while(sensor_flow.processing);
            sensor_flow.send();
//            Serial.println("Sent flow");
//            Serial.println(sensor_flow.flowrate);
            break;
        case levelAddr:
            while(sensor_level.processing);
            sensor_level.send();
        default:
            break;
    }
  }
