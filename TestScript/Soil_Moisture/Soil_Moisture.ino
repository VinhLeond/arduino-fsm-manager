#include <Arduino.h>
#include "Water_Flow.h"
#include "Soil_Moisture.h"
#include "Air_CO2.h"
#define SLAVE_ADD 0x08
#define POT_PIN A0

Soil_Moisture soil_moisture(POT_PIN,SLAVE_ADD);
void setup()
{
  Serial.begin(9600);
}

void loop()
{
}
