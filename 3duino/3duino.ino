#include "DisplayDriver.h" 
#include "Renderer.h"
#include "Vectors.h"

DisplayDriver* dis;
Renderer* renderer;

bool isSetup = false;

Mesh* tri = new Mesh(3, 1);

void setup()
{
  Serial.begin(9600);

  dis = new DisplayDriver(0x10, 0x10);
  renderer = new Renderer(dis);

  //Probably a better way to do this but idc
  tri->vertices[0] = Vector3(15, 15, 0);
  tri->vertices[1] = Vector3(8, 15, 0);
  tri->vertices[2] = Vector3(15, 8, 0);
  tri->faces[0] = Vector3I(0, 1, 2);

  isSetup = true;
}

void loop()
{
  if (!isSetup) return;

  dis -> clearBuffer();
  renderer -> renderMesh(tri);
  dis -> renderDisplay();
  delay(100);
}
