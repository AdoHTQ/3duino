#include "Matrix.h" 

Matrix44::Matrix44() {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      elements[i][j] = 0.0f;
    }
  }
}

Matrix44::Matrix44(float elements[4][4]) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      this->elements[i][j] = elements[i][j];
    }
  }
}

float Matrix44::getElement(int r, int c) {
  return elements[r][c];
}
void Matrix44::setElement(int r, int c, float value) {
  elements[r][c] = value;
}


Vector Matrix44::operator*(const Vector& vector) {
  if (vector.numVerteces < 4) {return Vector();}
  float x = elements[0][0] * vector.verteces[0] + elements[0][1] * vector.verteces[1] + elements[0][2] * vector.verteces[2] + elements[0][3] * vector.verteces[3];
  float y = elements[1][0] * vector.verteces[0] + elements[1][1] * vector.verteces[1] + elements[1][2] * vector.verteces[2] + elements[1][3] * vector.verteces[3];
  float z = elements[2][0] * vector.verteces[0] + elements[2][1] * vector.verteces[1] + elements[2][2] * vector.verteces[2] + elements[2][3] * vector.verteces[3];
  float w = elements[3][0] * vector.verteces[0] + elements[3][1] * vector.verteces[1] + elements[3][2] * vector.verteces[2] + elements[3][3] * vector.verteces[3];
  return Vector(x, y, z, w);
}
