#include "Stick.h"

Stick::Stick(uint8_t stickXPort, uint8_t stickYPort) {
  this->stickXPort = stickXPort;
  this->stickYPort = stickYPort;
}

BLA::Matrix<2> Stick::getPosition() {
  return BLA::Matrix<2>(analogRead(stickXPort) / 512. - 1., analogRead(stickYPort) / 512. - 1.);
}