
# arduino-fsm-manager    
 SUTD-Panasonic Capstone 2019 
----
##Discription
The code is engineered for object oriented programming. The main script is a finite state machine and each device is treated as an object.

Working principle:   
Arduino conect to Beaglebone through I2C interface. While Arduino connect to actuators and sensors using any interface.      
Each device connected to Arduino is identified by a unique ID, which can be served as a I2C address as well.  
The Beaglebone control actuator, sensor through arduino as following step:
   
1. Firstly, beagle bone send out ID of the device.   
2. The Arduino SFM goes to corresponding device state, upong receiving the address. It then, star waiting for the command.
3. BeagleBone starts sending action command  
4. The command is decoded and the corresponding device function is activated.
5. The Arduino goes back to the default state and wait for new device ID.

   

----
## Structure

The code contain two parts: the object library and the script.    

* Library: 
    * Device object
    * Utility function
* Scripts:
    * Device test
    * Production    
   

Device Object: All device object inhered from I2C object as base parent. Depend on the device, the device contain different driver method to perform required action.   

Utility function: It is device independent function such as moving average filter....  
  
Device test: This is test script for device driver testing. These script could be either for individual device or group of device.   

Production: This production code is the FSM code for the Arduino. Act as a main script for arduino program


----
## Note
I2C sensor developed on Arduino can be developed on the beaglebone side and vice versa.
