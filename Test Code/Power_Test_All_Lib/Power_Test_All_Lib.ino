#include "Led.h"
#include "Fan.h"


Fan FanO(0x15,5);
Fan FanR(0x16,4);
Fan FanL(0x17,3);
Led ledStrip (0x14);

void lightOff(){
  ledStrip.setBrightness(0);
  ledStrip.show();
  while(1);
}

void setup() {
  Serial.begin(9600);
  FanO.config();
  FanR.config();
  FanL.config();
  ledStrip.config();
}

void FanTest(){
  FanO.turnOn();
  FanR.turnOn();
  FanL.turnOn();
//  delay(5000);
//  FanO.turnOff();
//  FanR.turnOff();
//  FanL.turnOff();
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
  while(1);
}


void loop(){
  Serial.println("Start Test");
  delay(3000);
  LedTest();
  FanTest();
  while(1);
}
