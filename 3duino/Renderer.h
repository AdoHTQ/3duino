#ifndef RENDERER_H
#define RENDERER_H

#include <Arduino.h>
#include <BasicLinearAlgebra.h>

using namespace BLA;

struct Mesh {
  BLA::Matrix<3>* vertices;
  BLA::Matrix<3,1,int>* faces;

  int numVertices;
  int numFaces;

  //uint8_t* color;

  Mesh (int, int);

  Mesh (BLA::Matrix<3>*, BLA::Matrix<3,1,int>*, int, int);

  ~Mesh();

};

class Renderer {
private:
  BLA::Matrix<4,4> projection;

  float fov = 30 / 57.2957795;
  const float aspect = 1.;
  const float far = 10.;
  const float near = 0.1;

  void drawTriangle(BLA::Matrix<2,1,int> p1, BLA::Matrix<2,1,int> p2, BLA::Matrix<2,1,int> p3);

  void createProjectionMatrix();
  BLA::Matrix<3,1,int> Renderer::transformVertex(BLA::Matrix<3> ver);

public:
  Renderer();
  ~Renderer();

  void renderMesh(Mesh* mesh);
};



#endif
