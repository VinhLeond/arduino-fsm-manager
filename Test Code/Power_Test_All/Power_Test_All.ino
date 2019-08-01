#include "Led.h"
#include "Fan.h"
#include <Arduino.h>
// ACTUATOR PIN
#define pumpPin 8
#define fanOPin 9
#define fanRPin 10
#define fanLPin 11
// LED PIN (2->5)

// Actuator address
#define ledAddr 0x30
#define fanOAddr 0x31
#define fanRAddr 0x32
#define fanLAddr 0x33
#define pumpAddr 0x34

//
Fan fanO(fanOAddr,fanOPin);
Fan fanR(fanRAddr,fanRPin);
Fan fanL(fanLAddr,fanLPin);
Led ledStrip (ledAddr);
Pump pump(pumpAddr,pumpPin);

void lightOff(){
  ledStrip.setBrightness(0);
  ledStrip.show();
  while(1);
}

void setup() {
  Serial.begin(9600);
  fanO.config();
  fanR.config();
  fanL.config();
  pump.config();
  ledStrip.config();
  //lightOff();
}

void FanTest(){
//  digitalWrite(10,HIGH);
//  digitalWrite(11,HIGH);
//  digitalWrite(12,HIGH);
//  FanO.turnOn();
  analogWrite(fanOPin,122);
  delay(100);
//  FanR.turnOn();
analogWrite(fanLPin,122);
  delay(100);
analogWrite(fanRPin,122);
  delay(100);
analogWrite(pumpPin,122);
//  FanL.turnOn();
  delay(5000);
  fanO.turnOff();
  fanR.turnOff();
  fanL.turnOff();
  pump.turnOff();
  delay(5000);
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
  FanTest();
//  LedTest();
//  while(1);
}
