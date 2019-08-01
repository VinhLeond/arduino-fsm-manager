#include "Water_Level.h"
#define levelAddr 0x13

unsigned long lastreceived = 0;
long data;
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

Water_Level sensor_level(levelAddr);
void setup() {
  sensor_level.config();
  sensor_level.initialize();
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  if (millis() - lastreceived > 1000) {
//    long start = millis();
    data = sensor_level.readDistance();
//    sensor_level.bufData(); 
//    Serial.println("Time taken");
//    Serial.println(millis() - start);
    //    Serial.println(data);
    total = total - readings[readIndex];
    readings[readIndex] = data;
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;
    // calculate the average:
    average = total / numReadings;
    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }
    Serial.println(average);
    lastreceived = millis();
  }
}
