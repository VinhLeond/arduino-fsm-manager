#define MEGA2560 //Using Arduino Mega 2560 - Using hardware Serial instead of Software Serial
//#define DEBUG

#include "ArduinoSTL.h" 
#include "Arduino.h"
#include "I2C_Anything.h"
#include "Water_Level.h"
#include "Led.h"
#include "Fan.h"
#include "Pump.h"
using namespace std;

// SENSOR PIN
// Level sensor using RX1 (Pin19)


// ACTUATOR PIN
#define pumpPin 8
#define fanOPin 9
#define fanRPin 10
#define fanLPin 11
// LED PIN (2->5)

// Sensor address
#define defAddr 0x07
#define levelAddr 0x13


// Actuator address
#define ledAddr 0x30
#define fanOAddr 0x31
#define fanRAddr 0x32
#define fanLAddr 0x33
#define pumpAddr 0x34

// Parameter
#define timeout 300 // (Using for Flow sensor only)
