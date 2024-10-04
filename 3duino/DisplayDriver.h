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
protected:
  uint8_t resX;
  uint8_t resY;

  bool** buffer;
public:
  void clearScreen();

  void clearBuffer();

  void setPixel(int x, int y, bool state);

  void testDisplay();

  void renderDisplay();
};

class MAXDisplayDriver : public DisplayDriver {
private:
  const uint8_t clock = 44;
  const uint8_t cs = 46;
  const uint8_t data = 48;

  void sendData(uint8_t address, uint8_t din);

  void sendDataLow(uint8_t address, uint8_t din);

  void drawColumn(uint8_t column, uint8_t value);

  uint8_t boolsToByte(const bool* bits);

public:
  MAXDisplayDriver(uint8_t resolutionX, uint8_t resolutionY);

  void clearScreen();

  void clearBuffer();

  void setPixel(int x, int y, bool state);

  void testDisplay();

  void renderDisplay();
};

class SSDDisplayDriver : public DisplayDriver {

};

#endif
