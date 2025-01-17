// Written by Nick Gammon
// May 2012
#ifndef I2C_ANYTHING_H_
#define I2C_ANYTHING_H_
#include <Arduino.h>
#include <Wire.h>

template <typename T> int I2C_writeAnything (const T& value)
 {
   const byte * p = (const byte*) &value;
   unsigned int i;
   for (i = 0; i < sizeof value; i++)
         Wire.write(*p++);
   return i;
 }  // end of I2C_writeAnything

template <typename T> int I2C_readAnything(T& value)
 {
   byte * p = (byte*) &value;
   unsigned int i;
   for (i = 0; i < sizeof value; i++)
         *p++ = Wire.read();
   return i;
 }  // end of I2C_readAnything
 #endif
