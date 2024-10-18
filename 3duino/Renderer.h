#ifndef RENDERER_H
#define RENDERER_H

#include <Arduino.h>
#include <BasicLinearAlgebra.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

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
  const uint8_t clock = 13;
  const uint8_t data = 11;
  const uint8_t reset = 9;
  const uint8_t command = 8;
  const uint8_t cs = 10;

  BLA::Matrix<2,1,int> res = {96, 64};

  float fov = 30 / 57.2957795;
  const float aspect = (float)res(0) / res(1);
  const float far = 10.;
  const float near = 0.1;


  Adafruit_SSD1331 oled =
    Adafruit_SSD1331(
      cs,
      command,
      data,
      clock,
      reset
    );

  BLA::Matrix<4,4> projection;

  void sendCommand(uint8_t command);

  void drawTriangle(BLA::Matrix<2,1,int> p1, BLA::Matrix<2,1,int> p2, BLA::Matrix<2,1,int> p3, uint16_t color);
  void drawLine(BLA::Matrix<2,1,int> p1, BLA::Matrix<2,1,int> p2, uint16_t color);

  void createProjectionMatrix();
  BLA::Matrix<2,1,int> Renderer::transformVertex(BLA::Matrix<3> ver);

public:
  Matrix<3> position = Matrix<3>(0,0,-5);
  Matrix<3> scale = Matrix<3>(0,0,0);
  Matrix<3> rotation = Matrix<3>(0,0,0);

  Renderer();
  ~Renderer();

  void renderMesh(Mesh* mesh, uint16_t color);
  void clearScreen();
};



#endif
