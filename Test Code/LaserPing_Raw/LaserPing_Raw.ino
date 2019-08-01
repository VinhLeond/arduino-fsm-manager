//#include "NeoSWSerial.h"
//#include "SoftwareUart.h"

//SoftwareUart<> laserPing( 7, 7 );
//String data="000";
//String data;
char data;
unsigned long  pref;
unsigned long  interval;
const int numReadings = 10;
long distance;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
unsigned long lastreceived = 0;

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
//  String data = Serial1.readStringUntil(char(13));
//  while(!Serial1.available());
//  distance = data.toInt();
//  total = total - readings[readIndex];
//  readings[readIndex]=distance;
//  total = total + readings[readIndex];
//  // advance to the next position in the array:
//  readIndex = readIndex + 1;
//  // calculate the average:
//  average = total / numReadings;
}

void loop() {
if (millis() - lastreceived > 50){
     while (Serial1.available()){
//     char data = Serial1.readStringUntil(char(13));
       data = Serial1.read();
//     while(Serial1.available()){
//     Serial1.read();
     }
//     distance = data.toInt();

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // send it to the computer as ASCII digits
//  Serial.println("Average");
  Serial.println(data);
  lastreceived=millis();
}
}
