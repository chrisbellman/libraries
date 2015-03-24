/*
  MD25IIC.h   - MD25IIC library
  Copyright (c) 2013-2014 J. P. Coelho.  All rights reserved.
  Rev 1.0 - September, 2013
  
  
  This library is distributed WITHOUT ANY WARRANTY.
  Please refer to the GNU Public License for more details.
*/

#ifndef MD25IIC_h
#define MD25IIC_h

#if(ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Wire.h>

/***************************************************************
// GENERAL REG.s
//**************************************************************/
//#define SWver        0x0D
/***************************************************************
// COMMAND REG.s
//**************************************************************/
//#define Change_i2c_address_1 0xA0
//#define Change_i2c_address_2 0xAA
//#define Change_i2c_address_3 0xA5

class MD25IIC
{
  public:
    MD25IIC();
    MD25IIC(byte);
    void setAcceleration(byte);
    void enableTimeOut(boolean);
    void enableController(boolean);
    void resetEncoders();
    void setMotor1Speed(byte);
    void setMotor2Speed(byte);
    long getMotor1Encoder();
    long getMotor2Encoder();
    byte getAddress();
    void setMode(byte);
    byte getMotor1Current();
    byte getMotor2Current();
    byte getBattery();
   private:
    long receiveFromEncoder(byte);
    void sendData2Reg(byte, byte);
    byte getDataFromReg(byte);
    byte address;
    TwoWire MyWire;
// Constants:
    //***************************************************************
    // GENERAL REG.s
    //***************************************************************
    static byte const Motor1_Speed  = 0x00;
    static byte const Motor2_Speed  = 0x01;
    static byte const Motor1_Encoder = 0x02;
    static byte const Motor2_Encoder = 0x06;
    static byte const Command = 0x10;
    static byte const Acceleration = 0x0E;
    static byte const Motor_Mode = 0X0F;
    static byte const Battery = 0x0A;
    static byte const M1Current = 0x0B;
    static byte const M2Current = 0x0C;
    //***************************************************************
    // COMMAND REG.s
    //***************************************************************
    static byte const Reset_encoder = 0x20;
    static byte const Disable_controller = 0x30;
    static byte const Enable_controller = 0x31;
    static byte const Disable_timeout = 0x32;
    static byte const Enable_timeout = 0x33;
};

#endif
