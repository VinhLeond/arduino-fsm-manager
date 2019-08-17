
# Arduino Finite State Machine 
 SUTD-Panasonic Capstone 2019 
# Description
This repo is the Arduino code of the PCube system. In the PCube system, the Arduino is the slave device that receive command from beaglebone and control the peripheral device accordingly.
The code is engineered for object oriented programming. The main script is a finite state machine and each device is treated as an object. 

Working principle:
Arduino connects to Beaglebone through I2C interface. While Arduino connect to actuators and sensors using any interface such as Uart, analog...etc.      
Each peripheral connects to Arduino is identified by a unique ID, which can be served as a I2C address.  
The Beaglebone controls actuators, sensors through Arduino as following steps:
   
1. Firstly, Beaglebone send out ID of the device.   
2. The Arduino FSM goes to corresponding device state, upon receiving the peripheral's address. Then, it starts waiting for the command.
3. BeagleBone starts sending action command, such as reading sensor or activating actuator. 
4. The command is decoded and the corresponding device function is activated.
5. The Arduino goes back to the default state and wait for new device ID.

   
# Structure

The code contains two parts: the object library and the script.    

* Library: 
    * Device object
    * Utility function
* Scripts:
    * Device test
    * Production    
   

Device Object: All device object inhered from I2C object as base parent. Depend on the device, the device contains different driver methods to perform required action.   

Utility function: It is device-independent function such as moving average filter techniques. 
  
Device test: This is test script for device driver testing. These scripts could be either for individual device or group of device.   

Production: This production code is the FSM code for the Arduino. Act as a main script for Arduino program.


# Note
I2C sensor developed on Arduino can be developed on the Beaglebone and vice versa.
