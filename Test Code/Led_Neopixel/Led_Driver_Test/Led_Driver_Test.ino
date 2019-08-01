#include "Led.h"

//#undef ledCount
//#define ledCount     77
//#undef ledPort
//#define ledPort       13


//CRGBW leds[LED_COUNT];  // FastLED with RGBW
//CRGB *ledsRGB = (CRGB *) &leds[0];
Led ledStrip (0x14);

#define BRIGHT_STEP_COUNT 8
#define STARTING_BRIGHTNESS 4
volatile uint8_t brightnesSteps[BRIGHT_STEP_COUNT] = {5,15,40,70,93, 70, 40, 15};

uint8_t brightness = 4;
uint8_t lastBrightness = 4;

// For fading in a new sketch
long lastTime;

float fadeIndex;
#define FADE_STEPS 50



void setup()
{  
  Serial.begin(9600);
//  
//  LEDS.addLeds<WS2812B, LED_OUT, RGB>(ledsRGB, getRGBWsize(LED_COUNT));  //use both the CRGB pointer and the size function "getRGBWsize" in the FastLED_RGBW helper file
  brightness = STARTING_BRIGHTNESS;
//  ledStrip.setBrightness(brightnesSteps[brightness]);
//  LEDS.show();
  ledStrip.config();
  lightOff();
}

void lightOff(){
  ledStrip.setColourStrip(255,0,85);
  ledStrip.show();
  while(1);
}
void colorLoop() {
//  static uint8_t i=0;  
  static int j = 0;
  static int f = 0;
  static int k = 0;
  static uint8_t r=0;
  static uint8_t g=0;
  static uint8_t b=0;
  for (int i = 0; i < ledCount; i++) {
    r=64*(1+sin(i/2.0 + j/4.0       ));
    g=64*(1+sin(i/1.0 + f/9.0  + 2.1));
    b=64*(1+sin(i/3.0 + k/14.0 + 4.2));
    ledStrip.setColourR(i,r);
    ledStrip.setColourG(i,g);
    ledStrip.setColourB(i,b);
 }
  ledStrip.show();
//  while(1);
  j = j + 1;
  f = f + 1;
  k = k + 2;
}

//check this out!!
//void rainbowLoop(){
//  static uint8_t hue;
//
//for (uint8_t i = 0; i < LED_COUNT; i++) {
//    leds[i] = CHSV((i * 256 / LED_COUNT) + hue, 255, 255);
//  }
//  ledStrip.show();
//  hue++;
//}

void loop()
{
  // If'n we get some data, switch to passthrough mode
  // Draw the current pattern
  colorLoop();
  //rainbowLoop();
  // Initial fade-in effect for pattern
  if((millis() - lastTime > 15) && fadeIndex < FADE_STEPS) {
    lastTime = millis();
    fadeIndex++;
    ledStrip.setBrightness(brightnesSteps[brightness]*(fadeIndex/FADE_STEPS));
  }
  ledStrip.show();
}
