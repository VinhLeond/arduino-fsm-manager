#define MEGA2560
#define DEBUG

#include "ArduinoSTL.h" 
#include "Arduino.h"
#include "I2C_Anything.h"
#include "Water_Flow.h"
#include "Soil_Moisture.h"
#include "Air_CO2.h"
#include "Air_Moisture.h"
#include "Air_Temp.h"
#include "Water_Level.h"
#include "Led.h"
#include "Fan.h"
using namespace std;

//SENSOR PIN
#define soilPin A0
#define aMoisPin A1
#define aTempPin A2
#define flowPin 6
#define CO2Rx 18     //Hardware Serial1
#define CO2Tx 19
#define levelPin A3

//ACTUATOR PIN
#define FanOPin 9
#define FanRPin 10
#define FanLPin 11
//LED PIN (2->5)

//Sensor address
#define soilAddr 0x08
#define aMoisAddr 0x09
#define aTempAddr 0x10
#define CO2Addr  0x11
#define flowAddr 0x12
#define defAddr 0x07
#define levelAddr 0x13


//Actuator address
#define ledAddr 0x30
#define FanOAddr 0x31
#define FanRAddr 0x32
#define FanLAddr 0x33

#define timeout 300


// SENSOR
//Soil_Moisture sensor_Soil(soilAddr,soilPin);
//Air_Moisture sensor_aMois(aMoisAddr,aMoisPin);
//Air_Temp sensor_aTemp(aTempAddr,aTempPin);
//Air_CO2 sensor_CO2(CO2Addr,true);
//Water_flow sensor_flow(flowAddr,flowPin);
//Water_Level sensor_level(levelAddr,levelPin);

//ACTUATOR
//Fan FanO(FanOAddr,FanOPin);
//Fan FanR(FanRAddr,FanRPin);
//Fan FanL(FanLAddr,FanLPin);
Led ledStrip (ledAddr);


volatile int machineAddr = defAddr;
volatile unsigned int iMess;
volatile float fMess;
volatile vector <int> command(4);
volatile bool busy = true;
int counter;



//MANAGER FUNCTION
void listening(){
    Wire.begin(defAddr);
    busy=true;
}


void receiveEvent(int byteAmount){
  if ((byteAmount >0 ) && (byteAmount <= 1)){
    machineAddr=Wire.read();
    #ifdef DEBUG
    Serial.println("Receive Address");
    Serial.println(machineAddr);
    #endif
  }
  if ((byteAmount >= 2) &&(byteAmount <= 16)) {
    while(Wire.available()<16){
        #ifdef DEBUG
        Serial.println("Bytes arrived");
        Serial.println(Wire.available());
        #endif;
    }
    #ifdef DEBUG
    Serial.println(Wire.available());
    Serial.println("Bytes amount");
    Serial.println(byteAmount);
    #endif
    I2C_readAnything(command);
    #ifdef DEBUG
    Serial.println("Receive Command");
    Serial.println(iMess);
    #endif
  }

    busy=false;
}

void requestEvent(){
      switch (machineAddr)
    {
        
        default:
            break;
    }
  }

void setup() {
  Serial.begin(9600);

  //Config Actuator
//  FanO.config();
//  FanR.config();
//  FanL.config();
  ledStrip.config();
//  
//  //Config Sensor
//  sensor_Soil.config();
//  sensor_aMois.config();
//  sensor_aTemp.config();
//  sensor_flow.config();
//  sensor_level.config();
  #ifndef DEBUG
  sensor_CO2.config();
  #endif



  //Initialize test
  #ifdef DEBUG
  Serial.println("Start Test");
  #endif
  delay(3000);
  #ifdef DEBUG
  Serial.println("Test Fan");
  #endif
//  FanTest();
  #ifdef DEBUG
  Serial.println("Test LED");
  #endif
//  LedTest();
//  lightOff();
  //Config Manager
  listening();
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop(){
   switch (machineAddr)
    {
         case ledAddr:
            #ifdef DEBUG
            Serial.println("LED");
            Serial.println(iMess);
            #endif
            machineAddr=defAddr;
            break;
                       
        default:
            break;
    }
}
