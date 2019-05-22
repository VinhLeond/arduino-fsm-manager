//#undef  lendCount
//#define ledCount   77
//#undef stripCount
//#define stripCount 4
#include "Led.h"


#define BRIGHT_STEP_COUNT 8
#define STARTING_BRIGHTNESS 4
volatile uint8_t brightnesSteps[BRIGHT_STEP_COUNT] = {5,15,40,70,93, 70, 40, 15};

uint8_t brightness = 4;
uint8_t lastBrightness = 4;

// For fading in a new sketch
long lastTime;

float fadeIndex;
#define FADE_STEPS 50

Led ledStrip (0x14);
void lightOff(){
  ledStrip.setBrightness(0);
  ledStrip.show();
  while(1);
}

void setup()
{  
  Serial.begin(9600);
//  
//  LEDS.addLeds<WS2812B, LED_OUT, RGB>(ledsRGB, getRGBWsize(LED_COUNT));  //use both the CRGB pointer and the size function "getRGBWsize" in the FastLED_RGBW helper file
//  brightness = STARTING_BRIGHTNESS;
//  ledStrip.setBrightness(brightnesSteps[brightness]);
//  LEDS.show();
  ledStrip.config();
  lightOff();

}

void powerTest(){
  //Red test
  for (int i =0 ; i<255; i=i+10){
    ledStrip.setColourStrip(i,0,0);
    ledStrip.show();
    delay(100);
  }
  delay(1000);
  //Green Test
  for (int i =0 ; i<255; i=i+10){
    ledStrip.setColourStrip(0,i,0);
    ledStrip.show();
    delay(100);
  }

  delay(1000);

  //Blue Test
    for (int i =0 ; i<255; i=i+10){
    ledStrip.setColourStrip(0,0,i);
    ledStrip.show();
    delay(100);
  }

  delay(1000);

  //All LED test
    for (int i =0 ; i<255; i=i+10){
    ledStrip.setColourStrip(i,i,i);
    ledStrip.show();
    delay(100);
  }
  while(1);
}

void loop()
{
  powerTest();
  ledStrip.setBrightness(0);
  ledStrip.show();
  while(1);
  // Initial fade-in effect for pattern
}
