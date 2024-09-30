#include "DisplayDriver.h" 
#include "Renderer.h"

DisplayDriver* display;

void setup()
{
  Serial.begin(9600);

  display = new DisplayDriver(0x10, 0x10);

}
  
void loop()
{
  display -> clearScreen();
  display -> renderDisplay();
  delay(1000);
}