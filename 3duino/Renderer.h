#ifndef RENDERER_H
#define RENDERER_H

#include <Arduino.h>
#include "Vectors.h"
#include "DisplayDriver.h"
#include "Matrix.h"

struct Mesh {
  Vector3* vertices;
  Vector3I* faces;

  int numVertices;
  int numFaces;

  //uint8_t* color;

  Mesh (int, int);

  Mesh (Vector3*, Vector3I*, int, int);

  ~Mesh();

};

class Renderer {
private:
  DisplayDriver* dis;
  Matrix44* projection;

  const float fov = PI / 2;
  const float aspect = 1;
  const float far = 10;
  const float near = 0.01;

  void drawLine(int x1, int y1, int x2, int y2);
  void drawLine(Vector2I* p1, Vector2I* p2);

  void drawTriangle(Vector2I* p1, Vector2I* p2, Vector2I* p3);

  Vector2I transformVertex(Vector3* vertex);

public:
  Renderer(DisplayDriver* displayDriver);
  ~Renderer();

  void renderMesh(Mesh* mesh);
};



#endif
