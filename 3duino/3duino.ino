#include "DisplayDriver.h" 
#include "Renderer.h"
#include "Vectors.h"

#include "CubeMesh.h"

SSDDisplayDriver* dis;
Renderer* renderer;

bool isSetup = false;

void setup()
{
  Serial.begin(2000000);

  dis = new SSDDisplayDriver(0, 0, 96, 64);
  renderer = new Renderer(dis);

  //delay(1000);

  isSetup = true;
}

void loop()
{
  if (!isSetup) return;
  // dis -> clearBuffer();
  Serial.println("a");
  renderer -> renderMesh(&cube);
  Serial.println("b");
  dis -> renderDisplay();
  delay(1000);
}
