#include "Device_Manager.h"


/* Air humidity, Co2 , temperature and soil moisture are I2C devices.
  These device are implemented on Beaglebone. It can be migrate to Arduino easily.
  However, Finite State Machine cant handle multithread protocol very well.
  Upgrade arduino to a Real Time Operation Sytem using schedule based routine is a solution. 
*/

// SENSOR
Water_Level sensor_level(levelAddr);
  
//ACTUATOR
Fan fanO(fanOAddr,fanOPin);
Fan fanR(fanRAddr,fanRPin);
Fan fanL(fanLAddr,fanLPin);
Led ledStrip (ledAddr);
Pump pump(pumpAddr,pumpPin);


volatile int machineAddr = defAddr;
volatile unsigned int iMess;
float fMess;
#define commandSize 4
volatile vector <uint32_t> command(commandSize);
volatile bool busy = true;
int counter;



void setup() {
  //Config Manager
  Serial.begin(9600);
  listening();
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  //Config Actuator
  fanO.config();
  fanR.config();
  fanL.config();
  ledStrip.config();
  pump.config();
  
  //Config Sensor
  sensor_level.config();


////////////////////////////////////////////////////////////////////////////////
////////////              MESSAGE DECODER                       ////////////////
///////////////////////////////////////////////////////////////////////////////


void receiveEvent(int byteAmount){
    #ifdef DEBUG
    Serial.println("Bytes amount");
    Serial.println(byteAmount);
    #endif
  if ((byteAmount >0 ) && (byteAmount <= 2)){
    machineAddr=Wire.read();
    #ifdef DEBUG
    Serial.println("Receive Address");
    Serial.println(machineAddr);
    #endif
    Wire.begin(machineAddr);
    busy=false;
  }
  else if ((byteAmount >=2) && (byteAmount <=4)){
    I2C_readAnything(iMess);
    #ifdef DEBUG
    Serial.println("Receive command");
    Serial.println(iMess);
    #endif
    listening();    
  }
  else if ((byteAmount >= 4) &&(byteAmount <= commandSize*4)) {
    for (int i =0; i<commandSize; i++){
    #ifdef DEBUG
    Serial.println("Bytes left");
    Serial.println(Wire.available());
    #endif
    I2C_readAnything(command[i]); 
    }
    #ifdef DEBUG
    Serial.println("Receive Command");
    for (int i =0; i<commandSize; i++){
       Serial.println(command[i]);
    }
    #endif
    listening();
  }
}



////////////////////////////////////////////////////////////////////////////////
////////////              SENSOR STATEMACHINE                   ////////////////
////////////////////////////////////////////////////////////////////////////////


void requestEvent(){
      switch (machineAddr)
    {

        case levelAddr:
//            sensor_level.initialize();
            sensor_level.bufData();
            sensor_level.send();
            #ifdef DEBUG
            Serial.println("level");
            Serial.println("Sent waterLevel");
            Serial.println("Done");
            #endif
            machineAddr=defAddr;
            break;

        default:
            break;
    }
  }


////////////////////////////////////////////////////////////////////////////////
////////////              ACTUATOR STATEMACHINE                  ///////////////
////////////////////////////////////////////////////////////////////////////////

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
            
            
        case fanLAddr:
            #ifdef DEBUG
            Serial.println("fanL");
            Serial.println(iMess);
            #endif
            fanL.setSpeed(iMess);
            fanR.setSpeed(iMess);
            iMess=0;
            machineAddr=defAddr;
            break;

        case ledAddr:
            #ifdef DEBUG
            Serial.println("LED");
            #endif
            ledStrip.setColourStrip(command[1],command[2],command[3]);
            ledStrip.show();
            machineAddr=defAddr;
            break;

        case pumpAddr:
            #ifdef DEBUG
            Serial.println("Pump");
            Serial.println(iMess);
            #endif
            pump.setSpeed(iMess);
            iMess=0;
            machineAddr=defAddr;           
            break;

        default:
            break;
    }
}
