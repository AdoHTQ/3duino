#ifndef DISPLAYDRIVER_H
#define DISPLAYDRIVER_H

#include <Arduino.h>

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

  void sendData(uint8_t, uint8_t);
  
  void sendDataLow(uint8_t, uint8_t);

  void drawColumn(uint8_t, uint8_t);

  uint8_t boolsToByte(const bool*);

public:
  DisplayDriver(uint8_t, uint8_t);

  void clearScreen();

  void clearBuffer();

  void setPixel(uint8_t, uint8_t, bool);

  void testDisplay();

  void renderDisplay();
};

#endif
