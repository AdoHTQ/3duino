#include "DisplayDriver.h" 
#include "Renderer.h"
#include "Vectors.h"

#include "CubeMesh.h"

DisplayDriver* dis;
Renderer* renderer;

bool isSetup = false;

void setup()
{
  Serial.begin(9600);

  dis = new DisplayDriver(0x10, 0x10);
  renderer = new Renderer(dis);

  isSetup = true;
}

void loop()
{
  if (!isSetup) return;

  dis -> clearBuffer();
  renderer -> renderMesh(&cube);
  dis -> renderDisplay();
  delay(100);
}
