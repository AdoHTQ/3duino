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



SSDDisplayDriver::SSDDisplayDriver(const uint8_t resolutionX, const uint8_t resolutionY) 
{
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
  pinMode(command, OUTPUT);
  pinMode(reset, OUTPUT);
  
  //Reset display
  digitalWrite(reset, LOW);
  delay(1000);
  digitalWrite(reset, HIGH);

  digitalWrite(cs, LOW);


  sendCommand(0xAF);

  // There has to be a better way to do this

  // Setup columns
  //sendCommand(0x15, 0xA0, 0x00);
  sendCommand(0x15);
  sendCommand(0xA0);
  sendCommand(0x00);
  //sendCommand(0x15, 0xB0, resX);
  sendCommand(0x15);
  sendCommand(0xB0);
  sendCommand(resX);

  // Setup rows
  //sendCommand(0x75, 0xA0, 0x00);
  //sendCommand(0x75, 0xB0, resY);

  //Clear screen
  clearScreen();
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

  digitalWrite(cs, HIGH);
}

void SSDDisplayDriver::sendCommand(uint8_t command, uint8_t param1)
{
  digitalWrite(command, LOW);
  digitalWrite(cs, LOW);
  digitalWrite(clock, LOW);

  shiftOut(data, clock, MSBFIRST, command);
  shiftOut(data, clock, MSBFIRST, param1);

  digitalWrite(cs, HIGH);
}

void SSDDisplayDriver::sendCommand(uint8_t command, uint8_t param1, uint8_t param2)
{
  digitalWrite(command, LOW);
  digitalWrite(cs, LOW);
  digitalWrite(clock, LOW);

  shiftOut(data, clock, MSBFIRST, command);
  shiftOut(data, clock, MSBFIRST, param1);
  shiftOut(data, clock, MSBFIRST, param2);

  digitalWrite(cs, HIGH);
}

void SSDDisplayDriver::sendCommand(uint8_t command, uint8_t param1, uint8_t param2, uint8_t param3)
{
  digitalWrite(command, LOW);
  digitalWrite(cs, LOW);
  digitalWrite(clock, LOW);

  shiftOut(data, clock, MSBFIRST, command);
  shiftOut(data, clock, MSBFIRST, param1);
  shiftOut(data, clock, MSBFIRST, param2);
  shiftOut(data, clock, MSBFIRST, param3);

  digitalWrite(cs, HIGH);
}

void SSDDisplayDriver::sendCommand(uint8_t command, uint8_t param1, uint8_t param2, uint8_t param3, uint8_t param4)
{
  digitalWrite(command, LOW);
  digitalWrite(cs, LOW);
  digitalWrite(clock, LOW);

  shiftOut(data, clock, MSBFIRST, command);
  shiftOut(data, clock, MSBFIRST, param1);
  shiftOut(data, clock, MSBFIRST, param2);
  shiftOut(data, clock, MSBFIRST, param3);
  shiftOut(data, clock, MSBFIRST, param4);

  digitalWrite(cs, HIGH);
}


void SSDDisplayDriver::clearScreen()
{

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
