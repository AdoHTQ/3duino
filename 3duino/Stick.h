#ifndef STICK_H
#define STICK_H

#include <Arduino.h>
#include <BasicLinearAlgebra.h>

class Stick
{
private:
  uint8_t stickXPort;
  uint8_t stickYPort;

  bool button;

public:
  Stick(uint8_t stickXPort, uint8_t stickYPort);

  BLA::Matrix<2> getPosition();
  bool getButton();
  
};

#endif