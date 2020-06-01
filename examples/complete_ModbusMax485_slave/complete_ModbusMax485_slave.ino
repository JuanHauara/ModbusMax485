/*
 *  Author: Juan Hauara
 *  05/31/2020
 *  email: juan.hauara@teraflop.nl
 * 
 *  You can use the QModMaster program to simulate an Modbus RTU master, 
 *  it's free software: https://sourceforge.net/projects/qmodmaster/
 */

#include <ModbusMax485.h>

#define de_re_pin 4         // digital pin 4 as driver enable/receiver enable pin
#define modbus_slave_id 28  // Slave address

// 8 digital inputs
#define di1 6
#define di2 7
#define di3 8
#define di4 9
#define di5 10
#define di6 11
#define di7 12
#define di8 A7

// 6 digital outputs
#define do1 13
#define do2 A2
#define do3 A3
#define do4 A4
#define do5 A5
#define do6 A6

// 2 analog inputs
#define ai1 A0
#define ai2 A1

// 1 analog output
#define ao1 5

bool digitalIn[8];          // 8 digital inputs
bool digitalOut[6];         // 6 digital outputs
unsigned int analogIn[2];   // 2 analog inputs
unsigned int analogOut[1];  // 1 analog output

ModbusMax485::ModbusMax485slave<19> modbusSlave;

void setup()
{
  pinMode(di1, INPUT);
  pinMode(di2, INPUT);
  pinMode(di3, INPUT);
  pinMode(di4, INPUT);
  pinMode(di5, INPUT);
  pinMode(di6, INPUT);
  pinMode(di7, INPUT);
  pinMode(di8, INPUT);

  pinMode(do1, OUTPUT);
  pinMode(do2, OUTPUT);
  pinMode(do3, OUTPUT);
  pinMode(do4, OUTPUT);
  pinMode(do5, OUTPUT);
  pinMode(do6, OUTPUT);

  pinMode(ao1, OUTPUT);

  modbusSlave.begin(9600, &Serial, de_re_pin, modbus_slave_id);

  modbusSlave.addDiscreteInput(&digitalIn[0], 1000);
  modbusSlave.addDiscreteInput(&digitalIn[1], 1001);
  modbusSlave.addDiscreteInput(&digitalIn[2], 1002);
  modbusSlave.addDiscreteInput(&digitalIn[3], 1003);
  modbusSlave.addDiscreteInput(&digitalIn[4], 1004);
  modbusSlave.addDiscreteInput(&digitalIn[5], 1005);
  modbusSlave.addDiscreteInput(&digitalIn[6], 1006);
  modbusSlave.addDiscreteInput(&digitalIn[7], 1007);
  
  modbusSlave.addCoil(&digitalOut[0], 2000);
  modbusSlave.addCoil(&digitalOut[1], 2001);
  modbusSlave.addCoil(&digitalOut[2], 2002);
  modbusSlave.addCoil(&digitalOut[3], 2003);
  modbusSlave.addCoil(&digitalOut[4], 2004);
  modbusSlave.addCoil(&digitalOut[5], 2005);

  modbusSlave.addInputRegister(&analogIn[0], 3000);
  modbusSlave.addInputRegister(&analogIn[1], 3001);

  modbusSlave.addHoldingRegister(&analogOut[0], 4000);
}

void loop() 
{
  // reads digital and analog inputs
  digitalIn[0] = digitalRead(di1);
  digitalIn[1] = digitalRead(di2);
  digitalIn[2] = digitalRead(di3);
  digitalIn[3] = digitalRead(di4);
  digitalIn[4] = digitalRead(di5);
  digitalIn[5] = digitalRead(di6);
  digitalIn[6] = digitalRead(di7);
  digitalIn[7] = digitalRead(di8);
  
  analogIn[0] = analogRead(ai1);
  analogIn[1] = analogRead(ai2);
  
  // See if any modbus package was received from the master. 
  // This is a non blocking function since it uses the hardware serial port.
  modbusSlave.update();

  // digital and analog outputs are written
  digitalWrite(do1, digitalOut[0]);
  digitalWrite(do2, digitalOut[1]);
  digitalWrite(do3, digitalOut[2]);
  digitalWrite(do4, digitalOut[3]);
  digitalWrite(do5, digitalOut[4]);
  digitalWrite(do6, digitalOut[5]);

  analogWrite(ao1, analogOut[0]);  // use the holding register to set the duty cycle of PWM signal in pin 5
}
