#include "Renderer.h"

#include "CubeMesh.h"
#include "IcosphereMesh.h"

const unsigned long targetFrameLength = 100;

Renderer* renderer;

bool isSetup = false;

void setup()
{
  //Serial.begin(2000000);

  renderer = new Renderer();

  isSetup = true;
}

unsigned long frameStart;

void loop()
{
  if (!isSetup) return;
  frameStart = millis();

  //renderer -> clearScreen();
  renderer -> renderMesh(&cube, 0x0000);
  renderer -> renderMesh(&cube, 0xFFFF);

  delay(constrain(targetFrameLength - (millis() - frameStart), 0, targetFrameLength));
}
