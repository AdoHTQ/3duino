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

public:
  virtual void clearScreen();

  virtual void clearBuffer();

  virtual void setPixel(int x, int y, bool state);

  virtual void testDisplay();

  virtual void renderDisplay();
};

class MAXDisplayDriver : public DisplayDriver {
private:
  bool** buffer;
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
  const uint8_t clock = 13;
  const uint8_t data = 11;
  const uint8_t reset = 9;
  const uint8_t command = 8;
  const uint8_t cs = 10;

  

  //Yes, I tried to use an array. It's annoying
  void sendCommand(uint8_t command);

  struct Pixel {
    int red;
    int green;
    int blue;

    uint8_t bit1;
    uint8_t bit2;

    Pixel();
    Pixel(int r, int g, int b);

    void calcBytes();
  };

  Pixel** buffer;

public:
void sendData(uint8_t din);
  SSDDisplayDriver(uint8_t x, uint8_t y, uint8_t resolutionX, uint8_t resolutionY);

  void clearScreen();

  void clearBuffer();

  void setPixel(int x, int y, bool state);

  void testDisplay();

  void renderDisplay();
};

#endif
