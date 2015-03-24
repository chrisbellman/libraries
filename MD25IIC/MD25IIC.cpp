/*
  MD25IIC.h   - MD25IIC library
  Copyright (c) 2013-2014 J. P. Coelho.  All rights reserved.
  Rev 1.0 - September, 2013
  
  
  This library is distributed WITHOUT ANY WARRANTY.
  Please refer to the GNU Public License for more details.
*/

#if(ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Wire.h"
#include "MD25IIC.h"

/***************************************************************
// CONSTRUCTORS
//**************************************************************/
MD25IIC::MD25IIC()
{
  this->address = (0xB0 >> 1);
  MyWire.begin();            // Initialize Arduino as the IIC Master
}

MD25IIC::MD25IIC(byte address)
{
  this->address = address;
  MyWire.begin();            // Initialize Arduino as the IIC Master
}
/***************************************************************
// Enable/Disable Timeout
//**************************************************************/
void MD25IIC::enableTimeOut(boolean state){
  if (state){
	sendData2Reg(Command,Enable_timeout); // Enable Timeout
  }
  else{
    sendData2Reg(Command,Disable_timeout);      // Disable Timeout
  } 
}
/***************************************************************
// Enable/Disable on-board Controller
//**************************************************************/
void MD25IIC::enableController(boolean state){
  if (state){
	sendData2Reg(Command,Enable_controller); // Enable controller
  }
  else{
    sendData2Reg(Command,Disable_controller);      // Disable controller
  } 
}
/***************************************************************
// Reset encoder function
//**************************************************************/
void MD25IIC::resetEncoders(void){
	sendData2Reg(Command,Reset_encoder);
}
/***************************************************************
// Send order to motor 1
//**************************************************************/
void MD25IIC::setMotor1Speed(byte val)
{
	sendData2Reg(Motor1_Speed,val);
}
/***************************************************************
// Send order to motor 2
//**************************************************************/
void MD25IIC::setMotor2Speed(byte val)
{
	sendData2Reg(Motor2_Speed,val);
}
/***************************************************************
// Get Motor  1 Encoder Value
//**************************************************************/
long MD25IIC::getMotor1Encoder(void){
	return(receiveFromEncoder(Motor1_Encoder));
}
/***************************************************************
// Get Motor  2 Encoder Value
//**************************************************************/
long MD25IIC::getMotor2Encoder(void){
	return(receiveFromEncoder(Motor2_Encoder));
}
/***************************************************************
// Get Battery
//**************************************************************/
byte MD25IIC::getBattery(void)
{
	return(getDataFromReg(Battery));
}
/***************************************************************
// Get Motor 1 Current
//**************************************************************/
byte MD25IIC::getMotor1Current(void)
{
	return(getDataFromReg(M1Current));
}
/***************************************************************
// Get Motor 2 Current
//**************************************************************/
byte MD25IIC::getMotor2Current(void)
{
	return(getDataFromReg(M2Current));
}
/***************************************************************
// Get board Address
//**************************************************************/
byte MD25IIC::getAddress(void)
{
	return(address);
}
/***************************************************************
// Change Motor Mode
//**************************************************************/
void MD25IIC::setMode(byte select){
	switch(select) {
		case 0: sendData2Reg(Motor_Mode,select);break;
		case 1: sendData2Reg(Motor_Mode,select);break;
		case 2: sendData2Reg(Motor_Mode,select);break;
		case 3: sendData2Reg(Motor_Mode,select);break;
		default: sendData2Reg(Motor_Mode,0);break;
	}
}
/***************************************************************
// Set Acceleration
//**************************************************************/
void MD25IIC::setAcceleration(byte select){
	switch(select) {
		case 1: sendData2Reg(Acceleration,select);break;
		case 2: sendData2Reg(Acceleration,select);break;
		case 3: sendData2Reg(Acceleration,select);break;
		case 5: sendData2Reg(Acceleration,select);break;
		case 10: sendData2Reg(Acceleration,select);break;
		default: sendData2Reg(Acceleration,5);break;
	}
}
//#####################################################################
//# PRIVATE METHODS
//#####################################################################
/***************************************************************
// Send val to reg
//**************************************************************/
void MD25IIC::sendData2Reg(byte reg, byte val)
{
  MyWire.beginTransmission(address);       // Device select
  MyWire.write(reg);                       // Reg 2 write
  MyWire.write(val);                       // data 
  MyWire.endTransmission();                // End transmission
}
/***************************************************************
// Reset encoder function
//**************************************************************/
long MD25IIC::receiveFromEncoder(byte reg)
{ 
  long encoder = 0;         
  MyWire.beginTransmission(address); // Transmit to device MD25
  MyWire.write(reg);                 // Ask for Encx register    
  MyWire.endTransmission();          // Stop transmitting 

  MyWire.requestFrom((uint8_t) address, (uint8_t) 4);    // Request 4 bytes of data from MD-25
                                   // Scan IIC port and retrieve data
                                   // Scan IIC port and retrieve data
  while(MyWire.available())          // while available...
  { 
    encoder<<=8;                 // Shift 8 bits to left
    encoder += MyWire.read();      // Measure byte
  }

  return(encoder);
}
/***************************************************************
// Get data from register
//**************************************************************/
byte MD25IIC::getDataFromReg(byte reg)
{
	byte result = 0;
	MyWire.beginTransmission(address); // Transmit to device MD25
	MyWire.write(reg);                 // Register    
	MyWire.endTransmission();          // Stop transmitting 
	MyWire.requestFrom((uint8_t)address,(uint8_t)1);    // Query
	while(MyWire.available())          // while available...
	{
		result = MyWire.read();       // Get byte
	}
	
	return(result);
}
