# About
Adapted with minor changes from https://github.com/norgor/ModbusRTU to work with MAX485 chip.

Now you can specify the de_re_pin (driver enable/receiver enable pin) with the begin() sentence.
You have to connect DE and RE together and then to the de_re_pin of your Arduino.

Example: 
```c++ 
   #define de_re_pin 4         // digital pin 4 as driver enable/receiver enable pin
   #define modbus_slave_id 28  // Slave address
   
   modbusSlave.begin(9600, &Serial, de_re_pin, modbus_slave_id);
```

See a complete example of a Modbus RTU slave implementation in the attached example.

 *  You can use the QModMaster program to simulate a Modbus RTU master, it's an excellent free software: https://sourceforge.net/projects/qmodmaster/

The ModbusRTU library is a **simple** to use library that allows an arduino to act as a Modbus slave. It attempts to obscure all unnecessary parts of the protocol to provide a clean interface.

The library pre-allocates all necessary memory upon instantiation, which improves the performance of the library and allows for simpler diagnostics. 

# Support
Slave ID's are supported, it is therefore possible to have multiple slaves on the same bus.

### Entities
* Discrete Inputs
* Coils
* Input Registers
* Holding Registers

### Function Codes
* 1   - Read Coils
* 2   - Read Discrete Inputs
* 3   - Read Multiple Holding Registers
* 4   - Read Input Registers
* 5   - Write Single Coil
* 6   - Write Single Holding Register
* 15  - Write Multiple Coils
* 16  - Write Multiple Holding Registers

### Exception Functionality
* Exception Response Codes
  * 1 - Illegal Function
  * 2 - Illegal Data Address
  * 3 - Illegal Data Value
  
# Documentation
Whole libary is enclosed in a namespace called ModbusRTU.

## ModbusRTUSlave Class
The class is a template class with one parameter called registerCount. The parameter specifies the size of the register array or maximum register count.

### Members
```c++ 
   void begin(unsigned long baud, HardwareSerial *pHardwareSerial = &Serial, unsigned int de_re_pin, unsigned char slaveId = 1)
```
   The begin function sets up variables and configures the hardware serial class.
   * Parameters
      * baud: The baud rate the serial interface should run at.
      * pHardwareSerial: Pointer to a HardwareSerial instance. Defaults to &Serial.
      * de_re_pin: Pin to control DE (driver enable) and RE (receiver enable) pins of the MAX485 chip. You have to connect DE and RE together and then to the de_re_pin of your Arduino. Defaults to 4.
      * slaveId: Slave ID to be used by this slave. Defaults to 1.


```c++
   void update()
```
   The function checks for incoming frames from master, attempts to parse the frame upon receiving, thereafter returns the result to the master. The parsing includes reading/writing to the modbus entites. If parsing a frame fails, the slave will attempt to send an exception.


```c++
   long addCoil(bool *coil, unsigned short _register)
```
   The function adds a coil to the register array.
   * Parameters
      * coil: Pointer to a read/write boolean value.
      * _register: The register number to be assigned to the coil.
   * Return value
      * Returns the register number upon success.
      * Returns -1 upon failure.


```c++
   long addDiscreteInput(const bool *discreteInput, unsigned short _register)
```
   The function adds a discrete input to the register array.
   * Parameters
      * discreteInput: Pointer to a read-only boolean value.
      * _register: The register number to be assigned to the discrete input.
   * Return value
      * Returns the register number upon success.
      * Returns -1 upon failure.


```c++
   long addInputRegister(const short *inputRegister, unsigned short _register)
```
   The function adds an input register to the register array.
   * Parameters
      * inputRegister: Pointer to a read-only 16-bit value.
      * _register: The register number to be assigned to the input register.
   * Return value
      * Returns the register number upon success.
      * Returns -1 upon failure.


```c++
   long addHoldingRegister(short *holdingRegister, unsigned short _register)
```
   The function adds an input register to the register array.
   * Parameters
      * holdingRegister: Pointer to a read/write 16-bit value.
      * _register: The register number to be assigned to the holding register.
   * Return value
      * Returns the register number upon success.
      * Returns -1 upon failure.
