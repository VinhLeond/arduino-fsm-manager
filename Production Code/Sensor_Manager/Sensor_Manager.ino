//#define MEGA2560
#define DEBUG

#include <Arduino.h>
#include "Water_Flow.h"
#include "Soil_Moisture.h"
#include "Air_CO2.h"
#include "Air_Moisture.h"
#include "Air_Temp.h"
#include "Water_Level.h"

#define soilPin A0
#define aMoisPin A1
#define aTempPin A2
#define flowPin 6
#define CO2Rx 18     //Hardware Serial1
#define CO2Tx 19
#define levelPin A3


#define soilAddr 0x08
#define aMoisAddr 0x09
#define aTempAddr 0x10
#define CO2Addr  0x11
#define flowAddr 0x12
#define defAddr 0x07
#define levelAddr 0x13

#define timeout 300


volatile int machineAddr = defAddr;
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
    #ifdef DEBUG
    //
    #else
    sensor_CO2.config();
    #endif
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    Serial.begin(9600);
    sensor_flow.config();
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
    #ifdef DEBUG
    Serial.println(machineAddr);
    #endif
    busy=false;
}

void loop(){ 
    switch (machineAddr)
    {
        case defAddr:
            listening();
            #ifdef DEBUG
            Serial.println("Idle");
            #endif
            while(busy==true);
            break;
            
        case soilAddr:
            #ifdef DEBUG
            Serial.println("SoilMoisture");
            #endif
            sensor_Soil.initialize();
            sensor_Soil.bufData();
            while(sensor_Soil.busy);
            machineAddr=defAddr;
            #ifdef DEBUG
            Serial.println("Done");
            #endif
            break;
            
        case aMoisAddr:
            #ifdef DEBUG
            Serial.println("AirMoist");
            #endif
            sensor_aMois.initialize();
            sensor_aMois.bufData();
            while(sensor_aMois.busy);
            machineAddr=defAddr;
            break;
            
        case aTempAddr:
            #ifdef DEBUG
            Serial.println("AirTemp");
            #endif
            sensor_aTemp.initialize();
            sensor_aTemp.bufData();
            while(sensor_aTemp.busy);
            machineAddr=defAddr;
            break;
            
        case CO2Addr:
            #ifdef DEBUG
            Serial.println("CO2");
            #endif
            sensor_CO2.initialize();
            sensor_CO2.bufData();
            while(sensor_CO2.busy);
            machineAddr=defAddr;
            #ifdef DEBUG
            Serial.println("Done");
            #endif
            break;
            
        case flowAddr:
            #ifdef DEBUG
            Serial.println("flow");
            #endif
            sensor_flow.initialize();
            sensor_flow.bufData();
            while(sensor_flow.busy);
            machineAddr=defAddr;
            #ifdef DEBUG
            Serial.println("Done");
            #endif
            break;
            
        case levelAddr:
            #ifdef DEBUG
            Serial.println("level");
            #endif
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
            #ifdef DEBUG
            Serial.println("Sent Moisture");
            Serial.println(sensor_Soil.humidity);
            #endif
            break;
            
        case aMoisAddr:
            while(sensor_aMois.processing);
            sensor_aMois.send();
            #ifdef DEBUG
            Serial.println("Sent Moisture");
            Serial.println(sensor_aMois.humidity);
            #endif
            break;
            
        case aTempAddr:
            while(sensor_aTemp.processing);
            sensor_aTemp.send();
            #ifdef DEBUG
            Serial.println("Sent Temperature");
            Serial.println(sensor_aTemp.Temp);
            #endif        
            break;
            
        case CO2Addr:
            while(sensor_CO2.processing);
            sensor_CO2.send();
            #ifdef DEBUG
            Serial.println("Sent CO2");
            Serial.println(sensor_CO2.CO2);
            #endif
            break;
            
        case flowAddr:
            while(sensor_flow.processing);
            sensor_flow.send();
            #ifdef DEBUG
            Serial.println("Sent flow");
            Serial.println(sensor_flow.flowrate);
            #endif
            break;
            
        case levelAddr:
            while(sensor_level.processing);
            sensor_level.send();
        default:
            break;
    }
  }
