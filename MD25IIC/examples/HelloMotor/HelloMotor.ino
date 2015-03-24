/***************************************************************
// MOTOR CONTROL WITH MD-25 DRIVER BOARD
//**************************************************************/
#include <Wire.h>
#include <MD25IIC.h>
// MD25IIC METHODS:
//    -----------------------   ------------------------
//   |       MOTOR          |  | BOARD                 |
// --------------------------  |-----------------------|
// 1 | setMotor1Speed(byte) |  | getAddress()          |
//   | getMotor1Encoder()   |  | setMode(byte)         |
//   | getMotor1Current()   |  | getBattery()          |
// -------------------------|  | enableTimeOut(T/F)    |
// 2 | setMotor2Speed(byte) |  | enableController(T/F) |
//   | getMotor2Encoder()   |  | resetEncoders()       |
//   | getMotor2Current()   |  | setAcceleration(byte) |
// -------------------------|  |-----------------------|

MD25IIC MyBoard;
/***************************************************************
// Setup function
//**************************************************************/
void setup()
{
  MyBoard.enableTimeOut(true);   // Stop motor if no command sent
                                  // within a 2s window
  for(int k = 0; k<256; k++)
  {
    MyBoard.setMotor1Speed(k);    // Set motor 1 to k speed
    delay(100);
  }
}
/***************************************************************
// Loop function
//**************************************************************/
void loop()
{
 // Nothing to do ;-)
}
