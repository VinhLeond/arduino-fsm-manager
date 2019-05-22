#define MEGA2560

//#include "ArduinoSTL.h"
#include "Air_CO2.h"  
#include "Fan.h"
#include "MHZ19.h"        
#define RX_PIN 18                                          
#define TX_PIN 18                                                                         
#define S_ADDR 0x08

#define FanOPin 9
#define FanRPin 10
#define FanLPin 11

#define FanOAddr 0x31
#define FanRAddr 0x32
#define FanLAddr 0x33
// MHZ19 myMHZ19;                                             // Constructor for MH-Z19 class
// SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // Constructor for Stream class *change for HardwareSerial, i.e. ESP32 **
//HardwareSerial mySerial(1);                              // ESP32 Example 
Fan FanO(FanOAddr,FanOPin);
Fan FanR(FanRAddr,FanRPin);
Fan FanL(FanLAddr,FanLPin);
unsigned long getDataTimer = 0;                             // Variable to store timer interval
Air_CO2 sensor_CO2(S_ADDR,true);  
void setup()
{
    Serial.begin(9600);
    FanO.config();
    FanR.config();
    FanL.config();
    sensor_CO2.config();
//    sensor_CO2.setDataType(0);
//    sensor_CO2.initialize();
//    Wire.begin(S_ADDR);
    // mySerial.begin(BAUDRATE);                               // Begin Stream with MHZ19 baudrate
    // //mySerial.begin(BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN); // ESP32 Example 
//    Serial1.begin(BAUDRATE);

//     myMHZ19.begin(Serial1);                                // *Important, Pass your Stream reference 

//     myMHZ19.autoCalibration();                              // Turn ABC ON. Disable with autoCalibration(false)
}

void loop()
{
    
    delay(200);
    sensor_CO2.bufData();
//     if (millis() - getDataTimer >= 2000)                    // Check if interval has elapsed (non-blocking delay() equivilant)
//     {
//         int CO2;                                            // Buffer for CO2
//         CO2 = myMHZ19.getCO2();                             // Request CO2 (as ppm)
////
//         Serial.print("CO2 (ppm): ");                      
//         Serial.println(CO2);                                
//
//         int8_t Temp;                                         // Buffer for temperature
//         Temp = myMHZ19.getTemperature();                     // Request Temperature (as Celsius)
//         Serial.print("Temperature (C): ");                  
//         Serial.println(Temp);                               
//
//         getDataTimer = millis();                            // Update interval
//     }
}
