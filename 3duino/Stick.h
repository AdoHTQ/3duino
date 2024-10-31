#ifndef STICK_H
#define STICK_H

#include <Arduino.h>
#include <BasicLinearAlgebra.h>

class Stick
{
private:
  uint8_t stickXPort;
  uint8_t stickYPort;
  uint8_t stickButtonPort;

  bool button;

public:
  Stick(uint8_t stickXPort, uint8_t stickYPort, uint8_t stickButtonPort);

  BLA::Matrix<2> getPosition();
  bool getButton();
  
};

#endif