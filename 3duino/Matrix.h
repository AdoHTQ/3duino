#ifndef MATRIX_H
#define MATRIX_H

#include "Vectors.h"

class Matrix44 {
private:
  float elements[4][4];

public:
  Matrix44();

  Matrix44(float elements[4][4]);

  void setMatrix(float elements[4][4]);

  float getElement(int x, int y);
  void setElement(int x, int y, float value);

  Vector4 operator*(const Vector4& vector);
};

#endif