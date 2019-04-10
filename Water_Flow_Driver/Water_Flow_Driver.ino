#include <PinChangeInt.h>
 
#define MY_PIN 3 // we could choose any pin
 
volatile int rise_time = 0;
volatile int fall_time = 0;
long pwm_value;
uint8_t latest_interrupted_pin;
long frequency;
float flowrate;


void rising()
{
  rise_time = micros();
  PCintPort::attachInterrupt(MY_PIN, &falling, FALLING);
}
 
void falling() {
  fall_time = micros();
}

void measurePWM(){
    PCintPort::attachInterrupt(MY_PIN, &rising, RISING);
    while(fall_time==0){}
    PCintPort::detachInterrupt(MY_PIN);
    pwm_value=(fall_time-rise_time);
    if ((pwm_value < pow(10,8))&&(pwm_value>0))
    {
        frequency =1.0/(2*(pwm_value/(pow(10,6))));
        flowrate= frequency/65.0;
        Serial.print("FlowRate:"); Serial.println(flowrate);
    }
    fall_time=0; 
}
 
void setup() {
  pinMode(MY_PIN, INPUT);
  Serial.begin(9600);
}
 
void loop() {
    measurePWM();
    delay(2000);
}
