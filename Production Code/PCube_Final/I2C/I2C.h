#ifndef I2C_H_
#define I2C_H_
#include "Arduino.h"
#include "Wire.h"
class I2C
{
  public:
  I2C(int addr);
  // byte* getData();
  void setData(float readData);
  void float2Bytes(float val, byte* bytes_array);
  byte bytes[4];
  int getAddress();
  private:
  int address;
};
#endif
