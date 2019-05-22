#include "Led.h"
#include "Fan.h"
#include <Arduino.h>

//
Fan FanO(0x15,9);
Fan FanR(0x16,10);
Fan FanL(0x17,11);
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
//  pinMode(10,OUTPUT);
//  pinMode(11,OUTPUT);
//  pinMode(12,OUTPUT);
//  digitalWrite(10,LOW);
//  digitalWrite(11,LOW);
//  digitalWrite(12,LOW);
  ledStrip.config();
}

void FanTest(){
//  digitalWrite(10,HIGH);
//  digitalWrite(11,HIGH);
//  digitalWrite(12,HIGH);
//  FanO.turnOn();
  analogWrite(10,122);
  delay(100);
//  FanR.turnOn();
analogWrite(11,122);
  delay(100);
analogWrite(12,122);
//  FanL.turnOn();
  delay(5000);
  FanO.turnOff();
  FanR.turnOff();
  FanL.turnOff();
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
