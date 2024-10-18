#include "Renderer.h"

#include "TriMesh.h"

Renderer* renderer;

bool isSetup = false;

void setup()
{
  Serial.begin(2000000);

  renderer = new Renderer();

  //delay(1000);

  isSetup = true;
}

void loop()
{
  if (!isSetup) return;
  // dis -> clearBuffer();
  // Serial.println("a");
  renderer -> renderMesh(&tri);
  // Serial.println("b");
  // dis -> renderDisplay();
  delay(1000000);
}
