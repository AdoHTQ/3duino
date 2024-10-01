#ifndef RENDERER_H
#define RENDERER_H

#include <Arduino.h>
#include "Vectors.h"
#include "DisplayDriver.h"

// struct Mesh {
//   Vector3* vertices;
//   int* faces;
//   //uint8_t* color;


//   Mesh (int numVertices, int numFaces)
//   {
//     vertices = new Vector3[numVertices];
//     faces = new int[numFaces];
//   }

//   ~Mesh() {
//     delete[] vertices;
//     delete[] faces;
//   }
// };

class Renderer {
private:
  DisplayDriver* dis;

  void drawLine(int x1, int y1, int x2, int y2);
  void drawLine(Vector2I* p1, Vector2I* p2);

  void transformVertex()

public:
  Renderer(DisplayDriver* displayDriver);

  void drawTriangle(Vector2I* p1, Vector2I* p2, Vector2I* p3);

  //void renderMesh(Mesh mesh);
};



#endif