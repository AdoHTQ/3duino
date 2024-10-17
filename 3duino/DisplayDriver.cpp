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

int sign(int value)
{
  if (value > 0) return 1;
  if (value == 0) return 0;
  if (value < 0) return -1;
}

void MAXDisplayDriver::drawLine(int x1, int y1, int x2, int y2)
{
  int y = y1;
  int x = x1;
  int dx = abs(x2-x1);
  int dy = abs(y2-y1);
  int s1 = sign(x2-x1);
  int s2 = sign(y2-y1);

  bool interchange;

  if (dy > dx)
  {
    int t = dx;
    dx = dy;
    dy = t;
    interchange = true;
  } 
  else {interchange = false;}
  
  int e = 2*dy - dx;
  int a = 2*dy;
  int b = 2*dy - 2*dx;
  setPixel(x, y, true);

  for (int i = 1; i <= dx; i++)
  {
    if (e < 0) 
    {
      if (interchange) {y += s2;}
      else {x += s1;}
      e += a;
    }
    else
    {
      y += s2;
      x += s1;
      e += b;
    }
    setPixel(x, y, true);
  }
}

void MAXDisplayDriver::drawLine(VectorI p1, VectorI p2)
{
  drawLine(p1[0], p1[1], p2[0], p2[1]);
}

void MAXDisplayDriver::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint16_t color)
{
  VectorI p1 = VectorI(x1, y1);
  VectorI p2 = VectorI(x2, y2);
  VectorI p3 = VectorI(x3, y3);
  drawLine(p1, p2);
  drawLine(p2, p3);
  drawLine(p3, p1);
}




SSDDisplayDriver::SSDDisplayDriver(const uint8_t x, const uint8_t y, const uint8_t resolutionX, const uint8_t resolutionY) 
{
  resX = resolutionX - 1;
  resY = resolutionY - 1;

  oled.begin();

  //Clear screen
  clearScreen();
}

void SSDDisplayDriver::clearScreen()
{
  // sets all memory and pixels to be blank
  oled.fillScreen(0x0000);
}

void SSDDisplayDriver::clearBuffer()
{
}

void SSDDisplayDriver::setPixel(int x, int y, bool state)
{
}

void SSDDisplayDriver::drawLine(int x1, int y1, int x2, int y2)
{
  oled.drawLine(x1, y1, x2, y2, 0xFFFF);
}

void SSDDisplayDriver::drawLine(VectorI p1, VectorI p2)
{
  drawLine(p1[0], p1[1], p2[0], p2[1]);
}

void SSDDisplayDriver::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint16_t color)
{
  oled.drawTriangle(x1, y1, x2, y2, x3, y3, color);
}

void SSDDisplayDriver::testDisplay()
{
  //sendCommand(0xA5);
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
