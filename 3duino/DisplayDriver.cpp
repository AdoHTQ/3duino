#include "DisplayDriver.h"
#include <Arduino.h>

DisplayDriver::DisplayDriver(const uint8_t resolutionX, const uint8_t resolutionY) 
{
  if (resX != resY || resX % 0x08 != 0x00 || resY % 0x08 != 0x00) {Serial.println("invalid arguments");}
  this -> resX = resolutionX;
  this -> resY = resolutionY;

  buffer = new bool*[resolutionX];
  for (int i = 0; i < resolutionX; i++) {
    buffer[i] = new bool[resolutionY];
  }

  //Set all pins to output mode
  pinMode(data, OUTPUT);
  pinMode(cs, OUTPUT);
  pinMode(clock, OUTPUT);
  
  digitalWrite(cs, LOW);

  //Shut down
  sendData(0x0C, 0x00);
  //Decode mode
  sendData(0x09, 0x00);
  //Set brightness to 1/16
  sendData(0x0A, 0x00);
  //Disable test mode
  sendData(0x0F, 0x00);
  //Scan limit 7
  sendData(0x0B, 0x07);
  //Power on display
  sendData(0x0C, 0x01);

  //Clear screen
  clearScreen();
}

void DisplayDriver::sendData(uint8_t address, uint8_t din) {
  digitalWrite(clock, LOW);
  digitalWrite(cs, LOW);
  shiftOut(data, clock, MSBFIRST, address);
  shiftOut(data, clock, MSBFIRST, din);
  digitalWrite(cs, HIGH);
}

void DisplayDriver::clearScreen()
{
  for (uint8_t i = 0; i < 8; i++) 
  {
    drawColumn(i, 0);
  }
}

void DisplayDriver::drawColumn(uint8_t column, uint8_t value)
{
  //Don't draw the column if it isn't a display register
  if (column < 0b0000 || column > 0b0111) return;
  //MAX7219 display registers start at 0x01 instead of 0
  sendData(column + 1, value);
}