#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

#include <Arduino.h>

class DisplayDriver {
private:
  const uint8_t clock = 44;
  const uint8_t cs = 46;
  const uint8_t data = 48;

  uint8_t resX;
  uint8_t resY;

  bool** buffer;

  void sendData(uint8_t, uint8_t);

  void drawColumn(uint8_t, uint8_t);

public:
  DisplayDriver(uint8_t, uint8_t);

  void clearScreen();

  void setPixel(uint8_t, uint8_t, bool);
};

#endif