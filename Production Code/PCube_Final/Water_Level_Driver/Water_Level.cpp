#include "Water_Level.h"


Water_Level::Water_Level(int addr) :I2C(addr){}

Water_Level::~Water_Level(){}

void Water_Level::config(){
    Serial1.begin(9600);
}

void Water_Level::initialize()
{
    busy=true;
    processing=true;
    Wire.begin(I2C::getAddress());
}
float Water_Level::readDistance()
{
<<<<<<< HEAD
    while (Serial1.available()) {
      Serial1.read();
    }
    while (1) {
      if (Serial1.available()) {
        if (char(Serial1.peek()) == char(13)) {
          break;
        }
        else {
          buffer = buffer + char(Serial1.read());
        }
      }
    }
    distance = buffer.toInt();
    buffer = "";
    return distance;
}

void Water_Level::computing(){
    waterLevel = max(160 - distance,0);
=======


void Water_Level::bufData(int howMany)
{
<<<<<<< HEAD
    readDistance();
    computing();
    I2C::setData(waterLevel);
=======
    readwaterLevel();
    I2C::setData(volt);
>>>>>>> 4b8bbb1822bc42de12fabe9e02d1657663fe2c9f
    processing=false;
}

void Water_Level::send()
{
    I2C_writeAnything(I2C::bytes);
    busy=false;
}

/* STATIC METHOD */