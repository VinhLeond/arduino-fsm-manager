#include "Device_Manager.h"

// SENSOR
Soil_Moisture sensor_Soil(soilAddr,soilPin);
Air_Moisture sensor_aMois(aMoisAddr,aMoisPin);
Air_Temp sensor_aTemp(aTempAddr,aTempPin);
Air_CO2 sensor_CO2(CO2Addr,true);
Water_flow sensor_flow(flowAddr,flowPin);
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
  sensor_Soil.config();
  sensor_aMois.config();
  sensor_aTemp.config();
  sensor_flow.config();
  sensor_level.config();
  #ifdef CO2
  sensor_CO2.config();
  #endif

////////////////////////////////////////////////////////////////////////////////
////////////              Initialize test                       ////////////////
///////////////////////////////////////////////////////////////////////////////


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
}

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
//    Serial.println("Bytes left");
//    Serial.println(Wire.available());
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
        case soilAddr:
//             sensor_Soil.initialize();
            sensor_Soil.bufData();
            sensor_Soil.send();
            #ifdef DEBUG
            Serial.println("SoilMoisture");
            Serial.println("Sent Moisture");
            Serial.println(sensor_Soil.humidity);
            Serial.println("Done");
            #endif
            machineAddr=defAddr;
            break;
            
        case aMoisAddr:
            // sensor_aMois.initialize();
            sensor_aMois.bufData();
            sensor_aMois.send();
            #ifdef DEBUG
            Serial.println("AirMoist");
            Serial.println("Sent Moisture");
            Serial.println(sensor_aMois.humidity);
            Serial.println("Done");
            #endif
            machineAddr=defAddr;
            break;
            
        case aTempAddr:
            // sensor_aTemp.initialize();
            sensor_aTemp.bufData();
            sensor_aTemp.send();
            #ifdef DEBUG
            Serial.println("AirTemp");
            Serial.println("Sent Temperature");
            Serial.println(sensor_aTemp.Temp);
            Serial.println("Done");
            #endif        
            machineAddr=defAddr;
            break;
            
        case CO2Addr:
            #ifdef DEBUG
            Serial.println("CO2");
            #endif
            // sensor_CO2.initialize();
            sensor_CO2.send();
            #ifdef DEBUG
            Serial.println("CO2");
            Serial.println("Sent CO2");
//            Serial.println(sensor_CO2.CO2);
            Serial.println("Done");
            #endif
            machineAddr=defAddr;
            break;
            
        case flowAddr:
            // sensor_flow.initialize();
            sensor_flow.bufData();     
            sensor_flow.send();
            #ifdef DEBUG
            Serial.println("flow");
            Serial.println("Sent flow");
            Serial.println(sensor_flow.flowrate);
            Serial.println("Done");
            #endif
            machineAddr=defAddr;
            break;
            
        case levelAddr:
//            sensor_level.initialize();
            sensor_level.bufData();
            sensor_level.send();
            #ifdef DEBUG
            Serial.println("level");
            Serial.println("Sent waterLevel");
//            Serial.println(sensor_level.level);
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
            //NEED TEST HERE
            listening();
            #ifdef DEBUG
            Serial.println("Idle");
            #endif
            while(busy==true);
            break;
            
//        case CO2Addr:
//            sensor_CO2.bufData();
//            sensor_CO2.initialize();
//            machineAddr=defAddr;
            
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
//            while(ledStrip.busy);
//            for (int i =0; i<commandSize; i++){
//              command[i]=0;
//            }
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


////////////////////////////////////////////////////////////////////////////////
////////////              DEVICE FUNCTION                       ////////////////
////////////////////////////////////////////////////////////////////////////////


//ACTUATOR FUNCTION
void lightOff(){
  ledStrip.setBrightness(0);
  ledStrip.show();
}

void FanTest(){
  fanO.setSpeed(50);
  delay(4000);
  fanL.setSpeed(50);
  delay(4000);
  fanR.setSpeed(50);
  delay(5000);
//  fanO.turnOff();
//  fanL.turnOff();
//  fanR.turnOff();
//  delay(5000);
}


void LedTest(){
  //Red test
  for (int i =0 ; i<255; i=i+10){
    ledStrip.setColourStrip(i,0,0);
    ledStrip.show();
    delay(100);
  }
  delay(1000);
  //Green Test
  for (int i =0 ; i<255; i=i+10){
    ledStrip.setColourStrip(0,i,0);
    ledStrip.show();
    delay(100);
  }

  delay(1000);

  //Blue Test
    for (int i =0 ; i<255; i=i+10){
    ledStrip.setColourStrip(0,0,i);
    ledStrip.show();
    delay(100);
  }

  delay(1000);

  //All LED test
    for (int i =0 ; i<255; i=i+10){
    ledStrip.setColourStrip(i,i,i);
    ledStrip.show();
    delay(100);
  }
//  while(1);
}
//SENSOR FUNCTION

//MANAGER FUNCTION
void listening(){
    Wire.begin(defAddr);
    busy=true;
}
