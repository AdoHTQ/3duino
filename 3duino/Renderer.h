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

  void drawLine(int, int, int, int);

public:
  Renderer(DisplayDriver*);

  

  //void renderMesh(Mesh mesh);
};



#endif