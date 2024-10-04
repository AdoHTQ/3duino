#ifndef RENDERER_H
#define RENDERER_H

#include <Arduino.h>
#include "Vectors.h"
#include "DisplayDriver.h"
#include "Matrix.h"

struct Mesh {
  Vector* vertices;
  VectorI* faces;

  int numVertices;
  int numFaces;

  //uint8_t* color;

  Mesh (int, int);

  Mesh (Vector*, VectorI*, int, int);

  ~Mesh();

};

class Renderer {
private:
  DisplayDriver* dis;
  Matrix44 projection;

  float fov = 30 / 57.2957795;
  const float aspect = 1.;
  const float far = 10.;
  const float near = 0.1;

  void drawLine(int x1, int y1, int x2, int y2);
  void drawLine(VectorI p1, VectorI p2);

  void drawTriangle(VectorI p1, VectorI p2, VectorI p3);

  void createProjectionMatrix();
  VectorI transformVertex(Vector vertex);

public:
  Renderer(DisplayDriver* displayDriver);
  ~Renderer();

  void renderMesh(Mesh* mesh);
};



#endif
