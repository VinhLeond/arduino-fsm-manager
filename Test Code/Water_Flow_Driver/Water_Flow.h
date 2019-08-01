#include "Arduino.h"
#include "I2C.h"
#include "I2C_Anything.h"
class Water_Flow : public I2C
{
private:    
    static Water_Flow* instance;
    void computeFlow();
    int connection;
    static void rising();
    static void falling();
    void setRiseTime();
    void setFallTime();
    int rise_time = 0;
    int fall_time = 0;
    long pwm_value;
    uint8_t latest_interrupted_pin;
    long frequency;
    static void requestEvent();
    static void receiveEvent(int howMany);
public:
    Water_Flow(int addr);
    ~Water_Flow();
    void initialize(int port);
    // uint8_t getData();
    float measurePWM();
    float flowrate;
    void bufData(int howMany=0);
    void send();
};

