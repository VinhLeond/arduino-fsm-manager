#include "Arduino.h"
#include "Fan.h"
#define FanOPin 9
#define FanRPin 10
#define FanLPin 11

#define FanOAddr 0x31
#define FanRAddr 0x32
#define FanLAddr 0x33

Fan FanO(FanOAddr,FanOPin);
Fan FanR(FanRAddr,FanRPin);
Fan FanL(FanLAddr,FanLPin);

void setup() {
  Serial.begin(9600);
  FanO.config();
  FanR.config();
  FanL.config();
  
  // put your setup code here, to run once:

}


void OnOffTest(){
  FanO.setSpeed(255);
  delay(5000);
//  FanL.setSpeed(255);
//  delay(5000);
//  FanR.setSpeed(255);
digitalWrite(FanLPin,HIGH);
  delay(20000);
  FanO.turnOff();
  FanL.turnOff();
  FanR.turnOff();
  delay(5000);
}
void loop() {
  Serial.println("Start Test");
  delay(3000);
  // put your main code here, to run repeatedly:
  OnOffTest();
}
