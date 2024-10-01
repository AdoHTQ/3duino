#include "DisplayDriver.h" 
#include "Renderer.h"
#include "Vectors.h"

DisplayDriver* dis;
Renderer* renderer;

bool isSetup = false;

void setup()
{
  Serial.begin(9600);

  dis = new DisplayDriver(0x10, 0x10);
  renderer = new Renderer(dis);

  dis->clearScreen();

  isSetup = true;
}

void loop()
{
  if (!isSetup) return;

  dis -> clearBuffer();
  renderer->drawTriangle(new Vector2I(random(8, 15), random(8, 15)), new Vector2I(random(8, 15), random(8, 15)), new Vector2I(random(8, 15), random(8, 15)));
  dis -> renderDisplay();
  delay(100);
}
