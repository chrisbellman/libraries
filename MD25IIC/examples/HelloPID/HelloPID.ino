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

/***************************************************************
// MD25Add (default)
//**************************************************************/
MD25IIC MyBoard;
/***************************************************************
// Variables
//**************************************************************/
int setpoint=0;              // Set-point (reference angle)
float Kp = 0.1;              // Proportional gain (tune it!!)
float Ki = 0;                // Integral gain (tune it!!)
float Kd = 0;                // Derivative gain (tune it!!)
float  integral = 0;         // Integral component
float  derivativo = 0;       // Derivative component
float erro_k = 0;            // Set-point error at time k
float erro_k_1 = 0;          // Set-point error at time k-1
float comando = 0;           // Command signal
float deltaT = 0.02;         // Sampling period
int angulo = 0;              // Measured angle

byte motor = 128;            // Actuator signal
unsigned long time;

/***************************************************************
// Return angle (between 0 and 359º)
//**************************************************************/
int returnAngle(){
  return((int)(abs(MyBoard.getMotor1Encoder()%360)));
}
/***************************************************************
// Setup function
//**************************************************************/
void setup()
{
  Serial.begin(115200);          // Initialize serial comunication with 
                                 // the computer's terminal
  MyBoard.resetEncoders();       // Initialize to zero the encoder register
  MyBoard.enableTimeOut(false);  // Disable automatic 2s timeout
  MyBoard.enableController(true);// Enable on-board feedback speed control
  MyBoard.setAcceleration(10);   // Increase acceleration (default = 5)
  MyBoard.setMotor1Speed(128);   // The motor is initially stoped
}

/***************************************************************
// Loop function
//**************************************************************/
void loop()
{
  // Get the new set-point from the serial monitor window...
  while (Serial.available() > 0) {
    setpoint= Serial.parseInt();
  }
  // Get current time
  time = millis();
  //**********************************************PID Controller
  angulo = returnAngle();
  erro_k = setpoint-angulo;
  integral = integral + erro_k * deltaT;
  derivativo = (erro_k - erro_k_1)/deltaT;
  comando = Kp * erro_k + Ki * integral + Kd * derivativo;
  erro_k_1 = erro_k;
  //************************************************************
  
  //**************************************************Saturation 
  if (comando + 128 > 255) motor = 255;
  else if (comando + 128 < 0) motor = 0;
  else motor=(byte)(comando + 128);
  //************************************************************

  //*************************************************Update Speed  
  MyBoard.setMotor1Speed(motor); 
  //*************************************************************  

  delay(20-(millis()-time)); // Try to force sampling time to 20 ms
  
}
