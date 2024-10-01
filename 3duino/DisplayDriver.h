#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

#include <Arduino.h>
#include "Vectors.h"

/*

The 16x16 dot matrix is split into 4 8x8 matricies that are daisy chained together

This is their order

[4][2]
[3][1]

*/

class DisplayDriver {
private:  
  const uint8_t clock = 44;
  const uint8_t cs = 46;
  const uint8_t data = 48;

  uint8_t resX;
  uint8_t resY;

  bool* test;

  bool** buffer;

  void sendData(uint8_t address, uint8_t din);
  
  void sendDataLow(uint8_t address, uint8_t din);

  void drawColumn(uint8_t column, uint8_t value);

  uint8_t boolsToByte(const bool* bits);

public:
  DisplayDriver(uint8_t resolutionX, uint8_t resolutionY);
  ~DisplayDriver();

  void clearScreen();

  void clearBuffer();

  void setPixel(uint8_t x, uint8_t y, bool state);

  void testDisplay();

  void renderDisplay();
};

#endif
