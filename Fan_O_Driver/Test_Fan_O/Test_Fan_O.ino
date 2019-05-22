#include "Arduino.h"
#define FanO 5
#define FanR 4
#define FanL 3
void setup() {
  Serial.begin(9600);
  pinMode(FanO,OUTPUT);
  pinMode (FanR, OUTPUT);
  pinMode (FanL, OUTPUT);
  digitalWrite(FanR, LOW);
  digitalWrite(FanO,LOW);
  digitalWrite(FanL, LOW);
  // put your setup code here, to run once:

}


void OnOffTest(){
  digitalWrite(FanO,HIGH);
  digitalWrite(FanR, HIGH);
  digitalWrite(FanL, HIGH); 
  delay(5000);
  digitalWrite(FanR, LOW);
  digitalWrite(FanO,LOW);
  digitalWrite(FanL, LOW);
  delay(5000);
}
void loop() {
  Serial.println("Start Test");
  delay(10000);
  // put your main code here, to run repeatedly:
  OnOffTest();
}
