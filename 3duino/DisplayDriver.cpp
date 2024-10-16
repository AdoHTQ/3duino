#include "DisplayDriver.h"
#include "Vectors.h"

MAXDisplayDriver::MAXDisplayDriver(const uint8_t resolutionX, const uint8_t resolutionY) 
{
  if (resolutionX != resolutionY || resolutionX % 0x08 != 0x00 || resolutionY % 0x08 != 0x00) {Serial.println("invalid arguments");}
  resX = resolutionX;
  resY = resolutionY;

  buffer = new bool*[resX];

  for (int i = 0; i < resolutionX; i++) {
    buffer[i] = new bool[resY];
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

void MAXDisplayDriver::sendData(uint8_t address, uint8_t din) {
  digitalWrite(clock, LOW);
  digitalWrite(cs, LOW);
  shiftOut(data, clock, MSBFIRST, address);
  shiftOut(data, clock, MSBFIRST, din);
  digitalWrite(cs, HIGH);
}

// sends data, but doesn't interact with the CS pin
// this should be used for daisy-chaining
void MAXDisplayDriver::sendDataLow(uint8_t address, uint8_t din) {
  shiftOut(data, clock, MSBFIRST, address);
  shiftOut(data, clock, MSBFIRST, din);
}

// clears all displays
void MAXDisplayDriver::clearScreen()
{
  clearBuffer();
  renderDisplay();
}


void MAXDisplayDriver::clearBuffer()
{
  for (int i = 0; i < resX; i++) 
  {
    for (int j = 0; j < resY; j++) {
      buffer[i][j] = false;
    }
  }
}

void MAXDisplayDriver::setPixel(int x, int y, bool state)
{
  if (x >= resX || x < 0 || y >= resY || y < 0) return;
  buffer[x][y] = state;
}

void MAXDisplayDriver::testDisplay()
{
  sendData(0x0F, 0x01);
}

// we might not need this anymore
void MAXDisplayDriver::drawColumn(uint8_t column, uint8_t value)
{
  //Don't draw the column if it isn't a display register
  if (column < 0b0000 || column > 0b0111) return;
  //MAX7219 display registers start at 0x01 instead of 0
  sendData(column + 1, value);
}

// converts the first 8 boolean values in an array to a byte
uint8_t MAXDisplayDriver::boolsToByte(const bool *bits) {
  uint8_t byte = 0;
    for (int i = 0; i < 8; i++) {
      if (bits[i]) {
        byte |= 1 << (7 - i);
      }
    }
  return byte;
}

// renders whatever content is currently in the buffer
void MAXDisplayDriver::renderDisplay() {

  // loops through half of the columns in the buffer
  for (int i = 0; i < resY / 2; i++) {
    bool bytes[(resX + resY) / 8][8];
    int segSwitch = 0;
    // loops through all rows
    for (int j = 0; j < resX; j++) {
      if (j >= resX / 2) {segSwitch = 1;}
      bytes[0 + segSwitch][7-(j - (8 * segSwitch))] = buffer[j][i];
      bytes[2 + segSwitch][7-(j - (8 * segSwitch))] = buffer[j][i+8];
    }

    digitalWrite(cs, LOW);
    for (bool* byte : bytes) {
      sendDataLow(i + 1, boolsToByte(byte));
    }
    digitalWrite(cs, HIGH);

    // memory safety :)

    //Kinda cursed but I wanted an easy way to turn this on and off
    if (false)
    {
      for (int i = 0; i < resX; i++) {
        for (int j = 0; j < resY; j++) {
          if (buffer[i][j]) {
            Serial.write("O");
          } else {
            Serial.write(" ");
          }
        }
        Serial.write("\n");
      }
      Serial.println();
    }
  }  
}



SSDDisplayDriver::SSDDisplayDriver(const uint8_t x, const uint8_t y, const uint8_t resolutionX, const uint8_t resolutionY) 
{
  resX = resolutionX - 1;
  resY = resolutionY - 1;

  // buffer = new Pixel*[resX];

  // for (int i = 0; i < resolutionX; i++) {
  //   //hanging for some reason
  //   buffer[i] = new Pixel[resY];
  // }


  //Set all pins to output mode
  pinMode(data, OUTPUT);
  pinMode(cs, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(command, OUTPUT);
  pinMode(reset, OUTPUT);
  
  //Reset display
  digitalWrite(reset, LOW);
  delay(10);
  digitalWrite(reset, HIGH);

  digitalWrite(cs, LOW);


 
  // these are some more commands that I tried, it borked the display when I tried it tho.

  /*
  sendCommand(0xAE);
  sendCommand(0xA0);
  sendCommand(0x72);

  sendCommand(0xAD);
  sendCommand(0x8E);

  sendCommand(0xB3);
  sendCommand(0xF0);

  sendCommand(0xA4);
  sendCommand(0xA8);
  sendCommand(0x3F);
  */

  // Turn off display
  sendCommand(0xAE);

  // sendCommand(0xB3);
  // sendCommand(0xF0);
  
  // turn on display last
  sendCommand(0xAF);
  
  //Clear screen
  //clearScreen();
}

void SSDDisplayDriver::sendData(uint8_t din)
{
  digitalWrite(command, HIGH);
  digitalWrite(cs, LOW);
  digitalWrite(clock, LOW);

  shiftOut(data, clock, MSBFIRST, din);
  
  digitalWrite(cs, HIGH);
}

void SSDDisplayDriver::sendCommand(uint8_t command)
{
  digitalWrite(command, LOW);
  digitalWrite(cs, LOW);
  digitalWrite(clock, LOW);

  shiftOut(data, clock, MSBFIRST, command);
  Serial.println(command);
  digitalWrite(cs, HIGH);
}

void SSDDisplayDriver::clearScreen()
{
  // sets all memory and pixels to be blank
  sendCommand(0x25);
  sendCommand(0x00);
  sendCommand(0x00);
  sendCommand(resX);
  sendCommand(resY);
}

void SSDDisplayDriver::clearBuffer()
{
}

void SSDDisplayDriver::setPixel(int x, int y, bool state)
{
}

void SSDDisplayDriver::testDisplay()
{
  sendCommand(0xA5);
}

void SSDDisplayDriver::renderDisplay()
{
}

SSDDisplayDriver::Pixel::Pixel() {
  red = 0;
  blue = 0;
  green = 0;
}

SSDDisplayDriver::Pixel::Pixel(int r, int g, int b) {
  red = r > 31 ? 31 : r;
  green  = g > 63 ? 63 : g;
  blue = b > 31 ? 31 : b;
  calcBytes();
}

void SSDDisplayDriver::Pixel::calcBytes() {
  // calculates the 16 bit color value
  uint16_t tmp = ((red << 11) | (green << 5) | blue);
  
  // splits the 16 bit into two bytes
  bit1 = (uint8_t) (tmp & 0xFF00);
  bit2 = (uint8_t) ((tmp & 0xFF00) >> 8);
}
