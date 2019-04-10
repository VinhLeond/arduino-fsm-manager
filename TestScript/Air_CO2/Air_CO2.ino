#include "Air_CO2.h"                                         // include main library                           // Remove if using HardwareSerial
#define RX_PIN 11                                          // Rx pin which the MHZ19 Tx pin is attached to
#define TX_PIN 10                                          // Tx pin which the MHZ19 Rx pin is attached to                                     // Native to the sensor (do not change)
#define S_ADDR 0x08
// MHZ19 myMHZ19;                                             // Constructor for MH-Z19 class
// SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // Constructor for Stream class *change for HardwareSerial, i.e. ESP32 ***

//HardwareSerial mySerial(1);                              // ESP32 Example 

unsigned long getDataTimer = 0;                             // Variable to store timer interval
Air_CO2 sensor_CO2(S_ADDR,true);  
void setup()
{
    Serial.begin(9600);
    sensor_CO2.config();
    sensor_CO2.setDataType(0);
    sensor_CO2.initialize();
//    Wire.begin(S_ADDR);
    // mySerial.begin(BAUDRATE);                               // Begin Stream with MHZ19 baudrate
    // //mySerial.begin(BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN); // ESP32 Example 

    // myMHZ19.begin(mySerial);                                // *Important, Pass your Stream reference 

    // myMHZ19.autoCalibration();                              // Turn ABC ON. Disable with autoCalibration(false)
}

void loop()
{
    
    delay(200);
    sensor_CO2.bufData();
    // if (millis() - getDataTimer >= 2000)                    // Check if interval has elapsed (non-blocking delay() equivilant)
    // {
    //     int CO2;                                            // Buffer for CO2
    //     CO2 = myMHZ19.getCO2();                             // Request CO2 (as ppm)

    //     Serial.print("CO2 (ppm): ");                      
    //     Serial.println(CO2);                                

    //     int8_t Temp;                                         // Buffer for temperature
    //     Temp = myMHZ19.getTemperature();                     // Request Temperature (as Celsius)
    //     Serial.print("Temperature (C): ");                  
    //     Serial.println(Temp);                               

    //     getDataTimer = millis();                            // Update interval
    // }
}
