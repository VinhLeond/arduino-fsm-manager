#include "Arduino.h"
#include "I2C.h"
#include "I2C_Anything.h"
class Soil_Moisture : public I2C
{
private:
    static Soil_Moisture* instance;
    void Computing();
    int connection;
    // I2C I2CInstance;
public:
    Soil_Moisture(int addr);
    ~Soil_Moisture();
    void initialize(int port);
    // uint8_t getData();
    float readHumidity();
    float humidity;
    void bufData(int howMany=0);
    void send();
    static void requestEvent();
    static void receiveEvent(int howMany);
};

