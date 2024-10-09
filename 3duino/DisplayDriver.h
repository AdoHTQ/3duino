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
  virtual void clearScreen();

  virtual void clearBuffer();

  virtual void setPixel(int x, int y, bool state);

  virtual void testDisplay();

  virtual void renderDisplay();
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
private:
  const uint8_t clock = 52;
  const uint8_t data = 50;
  const uint8_t reset = 48;
  const uint8_t command = 46;
  const uint8_t cs = 44;

  

  //Yes, I tried to use an array. It's annoying
  void sendCommand(uint8_t command);
  void sendCommand(uint8_t command, uint8_t param1);
  void sendCommand(uint8_t command, uint8_t param1, uint8_t param2);
  void sendCommand(uint8_t command, uint8_t param1, uint8_t param2, uint8_t param3);
  void sendCommand(uint8_t command, uint8_t param1, uint8_t param2, uint8_t param3, uint8_t param4);

public:
void sendData(uint8_t din);
  SSDDisplayDriver(uint8_t resolutionX, uint8_t resolutionY);

  void clearScreen();

  void clearBuffer();

  void setPixel(int x, int y, bool state);

  void testDisplay();

  void renderDisplay();
};

#endif
