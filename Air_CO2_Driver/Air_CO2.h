#include "Arduino.h"
#include "I2C.h"
#include "I2C_Anything.h"
#include "HardwareSerial.h"
#include "MHZ19.h"
#include "SoftwareSerial.h"

class Air_CO2 : public I2C, public MHZ19
{
private:
    static Air_CO2* instance;
    void Computing();
    bool done;
    int connection;
    int uartRx;
    int uartTx;
    bool AC;
    unsigned long getDataTimer;
    bool checkStatus();
    int paraType;
public:
    Air_CO2();
    Air_CO2(int addr);
    ~Air_CO2();
    void initialize(bool calib = false);
    float readCO2();
    float readTemp();
    int CO2;
    float Temp;
    void setDataType(int dataType);
    void bufData(int howMany=0);
    void send();
    static void requestEvent();
    static void receiveEvent(int howMany);
};

