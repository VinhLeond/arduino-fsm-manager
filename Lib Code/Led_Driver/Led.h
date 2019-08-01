//
//      IMPLEMENTING TEMPLATE AND CONSTRUCTOR (PENDING)
//
#pragma once
#ifndef Led_H_
#define Led_H_
#include "Arduino.h"
#include "I2C.h"
#include "I2C_Anything.h"
#include "FastLED.h"
#include "FastLED_RGBW.h"

#define startPort 2
#define ledPort 2

#ifndef stripCount
#define stripCount 4
#endif
// 144/m Neopixel RGBW
#define ledCount 77


class Led : public I2C
{
private:
    void Computing();
    // byte test=0;
    
public:
    Led(int addr);
    ~Led();
    void config();
    void initialize();
    void setColourR(int ID,uint8_t r = 0 );
    void setColourG(int ID,uint8_t g = 0 );
    void setColourB(int ID,uint8_t b = 0 );
    void setColour(int ID, uint8_t r = 0 ,uint8_t g = 0,uint8_t b = 0);
    void setColourStrip(uint8_t r = 0 ,uint8_t g = 0,uint8_t b = 0);
    void setBrightness(uint8_t bright);
    void show();
    uint8_t getBrightness();
    // uint8_t getColour();
    byte getColour();
    volatile bool busy = false;
    volatile bool processing=false; 
    void bufData(int howMany=0);
    void send();
    uint8_t brightness;
    byte colour;
    // static CRGBW leds;
};
#endif

