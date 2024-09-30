#include "DisplayDriver.h" 
#include "Renderer.h"

DisplayDriver* dis;
Renderer* renderer;

bool isSetup;

void setup()
{
  Serial.begin(9600);

  dis = new DisplayDriver(0x10, 0x10);
  renderer = new Renderer(dis);

  isSetup = true;
}
  
void loop()
{
  //if (!isSetup) return;
  //dis -> clearScreen();
  Serial.println("a");
  renderer->drawLine(15, 15, 14, 14);
  Serial.println("b");
  dis -> renderDisplay();
  delay(1000);
}
