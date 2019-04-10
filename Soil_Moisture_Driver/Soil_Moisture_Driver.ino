#include "Soil_Moisture.h"
#include <Arduino.h>
#define SLAVE_ADD 0x08
#define POT_PIN A0

Soil_Moisture soil_moisture(POT_PIN,SLAVE_ADD);
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  soil_moisture.bufData();
//  Serial.println(soil_moisture.getAddress());
  uint8_t* ptr=soil_moisture.getData();
//  Serial.println(ptr[1]);
}
