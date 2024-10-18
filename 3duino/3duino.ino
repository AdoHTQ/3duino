#include "Renderer.h"
#include "Stick.h"

#include "CubeMesh.h"
//#include "IcosphereMesh.h"
//#include "SuzanneMesh.h"

const unsigned long targetFrameLength = 100;

Renderer* renderer;

bool isSetup = false;

Stick stick = Stick(A1, A0);

void setup()
{
  Serial.begin(2000000);

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

  Matrix<2> stickPos = stick.getPosition();
  renderer -> position += Matrix<3>(stickPos(0), 0, -stickPos(1));

  renderer -> renderMesh(&cube, 0xFFFF);

  delay(constrain(targetFrameLength - (millis() - frameStart), 0, targetFrameLength));
}
