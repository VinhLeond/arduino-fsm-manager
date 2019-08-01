#define MEGA2560
//#define DEBUG
//#define CO2

#include "ArduinoSTL.h" 
#include "Arduino.h"
#include "I2C_Anything.h"
#include "Water_Flow.h"
#include "Soil_Moisture.h"
#include "Air_CO2.h"
#include "Air_Moisture.h"
#include "Air_Temp.h"
#include "Water_Level.h"
#include "Led.h"
#include "Fan.h"
#include "Pump.h"
using namespace std;

// SENSOR PIN
#define soilPin A0
#define aMoisPin A1
#define aTempPin A2
#define flowPin 7
#define CO2Rx 18     //Hardware Serial1
#define CO2Tx 19
#define levelPin A3

// ACTUATOR PIN
#define pumpPin 8
#define fanOPin 9
#define fanRPin 10
#define fanLPin 11
// LED PIN (2->5)

// Sensor address
#define soilAddr 0x08
#define aMoisAddr 0x09
#define aTempAddr 0x10
#define CO2Addr  0x11
#define flowAddr 0x12
#define defAddr 0x07
#define levelAddr 0x13


// Actuator address
#define ledAddr 0x30
#define fanOAddr 0x31
#define fanRAddr 0x32
#define fanLAddr 0x33
#define pumpAddr 0x34

// Parameter
#define timeout 300
