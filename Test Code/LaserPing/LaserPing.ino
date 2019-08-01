//#include "NeoSWSerial.h"
//#include "SoftwareUart.h"

//SoftwareUart<> laserPing( 7, 7 );
//String buffer="000";
String buffer ="";
unsigned long  pref;
unsigned long  interval;
const int numReadings = 10;
long distance;
String data;
char preData[5];
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
unsigned long lastreceived = 0;
unsigned long wait = 0;
boolean finish = false;
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
//  String buffer = Serial1.readStringUntil(char(13));
//  while(!Serial1.available());
//  distance = buffer.toInt();
//  total = total - readings[readIndex];
//  readings[0]=distance;
//  total = total + readings[readIndex];
//  // advance to the next position in the array:
//  readIndex = readIndex + 1;
//  // calculate the average:
//  average = total / numReadings;
}

void loop() {
if (millis() - lastreceived > 1000){
//     if (Serial1.available()){
//     buffer = Serial1.readStringUntil(char(13));
     while(Serial1.available()){
     Serial1.read();}
     while(finish == false){
     if (Serial1.available()){
     if (char(Serial1.peek())==char(13)){
        finish = true;
//        buffer=buffer+",";
     }
     else{
      buffer = buffer +char(Serial1.read());
     }
     }
     }
//     Serial.println(buffer);
     int i=0;
//     while(buffer[i]!=','){
//       data = data + buffer[i];
//       i++;
//     }
     data = buffer;
     
     finish = false;
//     data="";
     buffer="";
     Serial.println(data);
//    }
  // send it to the computer as ASCII digits
//  Serial.println("Average");
  lastreceived=millis();
}
}
