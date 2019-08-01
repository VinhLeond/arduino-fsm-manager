#include"Water_Flow.h"
#define MY_PIN 7 // we could choose any pin
#define S_Addr 0x08
Water_Flow sensor_Flow(S_Addr,MY_PIN);

void setup() {
  Serial.begin(9600);
  sensor_Flow.initialize();
}
 
void loop(){
  Serial.println("Measure");
  sensor_Flow.initialize();
  Serial.println(sensor_Flow.busy);
  sensor_Flow.bufData();
  Serial.println(sensor_Flow.busy);
  Serial.println(sensor_Flow.flowrate);
  delay(1000);
 }
