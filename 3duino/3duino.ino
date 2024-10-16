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

  dis = new SSDDisplayDriver(0, 0, 96, 64);
  renderer = new Renderer(dis);

  //delay(1000);

  isSetup = true;
}

void loop()
{
  if (!isSetup) return;
  // dis -> sendData(0x00);
  // dis -> sendData(0xFF);

  

  // dis -> clearBuffer();
  // renderer -> renderMesh(&plane);
  // dis -> renderDisplay();
  //delay(1);
}
