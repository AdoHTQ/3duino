#ifndef RENDERER_H
#define RENDERER_H

#include <Arduino.h>
#include "Vectors.h"

struct Mesh {
  Vector3* vertices;
  int* faces;
  //uint8_t* color;


  Mesh (int numVertices, int numFaces)
  {
    vertices = new Vector3[numVertices];
    faces = new int[numFaces];
  }

  ~Mesh() {
    delete[] vertices;
    delete[] faces;
  }
};

class Renderer {
private:

public:
  void RenderMesh(Mesh mesh);
};

#endif