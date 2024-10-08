#include "DisplayDriver.h" 
#include "Renderer.h"
#include "Vectors.h"

#include "PlaneMesh.h"

SSDDisplayDriver* dis;
Renderer* renderer;

bool isSetup = false;

void setup()
{
  Serial.begin(2000000);

  dis = new SSDDisplayDriver(96, 64);
  renderer = new Renderer(dis);

  isSetup = true;
}

void loop()
{
  if (!isSetup) return;

  // dis -> clearBuffer();
  // renderer -> renderMesh(&plane);
  // dis -> renderDisplay();
  delay(500);
}
