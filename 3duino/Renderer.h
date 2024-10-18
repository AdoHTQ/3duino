#ifndef RENDERER_H
#define RENDERER_H

#include <Arduino.h>
#include <BasicLinearAlgebra.h>

struct Mesh {
  Matrix<3,1>* vertices;
  Matrix<3,1,int>* faces;

  int numVertices;
  int numFaces;

  //uint8_t* color;

  Mesh (int, int);

  Mesh (Matrix<3,1>*, Matrix<3,1,int>*, int, int);

  ~Mesh();

};

class Renderer {
private:
  DisplayDriver* dis;
  Matrix<4,4> projection;

  float fov = 30 / 57.2957795;
  const float aspect = 1.;
  const float far = 10.;
  const float near = 0.1;

  void drawTriangle(Matrix<2,1,int> p1, Matrix<2,1,int> p2, Matrix<2,1,int> p3);

  void createProjectionMatrix();
  Matrix<3,1,int>* transformVertex(Vector* vertex);

public:
  Renderer(Matrix<2,1,int> resolution);
  ~Renderer();

  void renderMesh(Mesh* mesh);
};



#endif
