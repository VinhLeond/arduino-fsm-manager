#include "I2C.h"

/*#####################-Initiation Functions-#####################*/



I2C::I2C(int addr =0x00):address(addr)
{
}

int I2C::getAddress(){
  return address;
}

void I2C::setData(float readData)
{
  float2Bytes(readData, &bytes[0]);
}



// byte* I2C::getData()
// {
//   static byte arr[4];
//   for (int i=0;i<=3;i++)
//   {
//     arr[i] = bytes[i];
//   }
//   return arr;
// }


void I2C::float2Bytes(float val, byte *bytes_array){
  // Create union of shared memory space
  union {
    float float_variable;
    byte temp_array[4];
  } u;
  // Overite bytes of union with float variable
  u.float_variable = val;
  // Assign bytes to input array
  memcpy(bytes_array, u.temp_array, 4);
}

