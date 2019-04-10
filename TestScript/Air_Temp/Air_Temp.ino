#include <Arduino.h>
#include "Water_Flow.h"
#include "Soil_Moisture.h"
#include "Air_CO2.h"
#include "Air_Moisture.h"
#define SLAVE_ADD 0x10
#define aMoisPin A2

Air_Moisture sensor_aMoisture(aMoisPin,SLAVE_ADD);
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  delay(1000);
  Serial.println(analogRead(aMoisPin));
}
