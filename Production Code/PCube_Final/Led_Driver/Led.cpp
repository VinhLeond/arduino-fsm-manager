#include "Led.h"



static CRGBW leds[ledCount];
static CRGB *ledsRGB = (CRGB *) &leds[0];

Led::Led(int addr) :I2C(addr){}

Led::~Led(){}

void Led::config(){
    FastLED.addLeds<WS2812B, startPort>(ledsRGB, getRGBWsize(ledCount));
    FastLED.addLeds<WS2812B, startPort + 1>(ledsRGB, getRGBWsize(ledCount));
    FastLED.addLeds<WS2812B, startPort + 2>(ledsRGB, getRGBWsize(ledCount));
    FastLED.addLeds<WS2812B, startPort + 3>(ledsRGB, getRGBWsize(ledCount));
}

void Led::initialize()
{
    busy=true;
    processing=true;
    Wire.begin(I2C::getAddress());
}

void Led::setColourR(int ID, uint8_t red){
    leds[ID].r = red;
}
void Led::setColourG(int ID,uint8_t green){
    leds[ID].g = green;
}
void Led::setColourB(int ID,uint8_t blue ){
    leds[ID].b = blue;
}

void Led::setColour(int ID, uint8_t red  ,uint8_t green ,uint8_t blue ){
    setColourR(ID,red);
    setColourG(ID,green);
    setColourB(ID,blue);
}

void Led::setColourStrip(uint8_t red,uint8_t green,uint8_t blue)
{
    for (int i = 0; i < ledCount; i++) {
        setColour(i, red, green ,blue);
    }
}

void Led::setBrightness(uint8_t brightness){
    FastLED.setBrightness(brightness);
    // Serial.print("Done setBrightness");
}

uint8_t Led::getBrightness(){
    return FastLED.getBrightness();
}

void Led::show(){
    FastLED.show();
    busy=false;
}

void Led::bufData(int howMany)
{
    // readHumidity();
    // I2C::setData(humidity);
    processing=false;
}

void Led::send()
{
    I2C_writeAnything(I2C::bytes);
    busy=false;
}

/* STATIC METHOD */

