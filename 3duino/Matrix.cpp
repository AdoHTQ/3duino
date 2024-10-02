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

float Matrix44::getElement(int x, int y) {
  return elements[x][y];
}
void Matrix44::setElement(int x, int y, float value) {
  elements[x][y] = value;
}


Vector4 Matrix44::operator*(const Vector4& vector) {
  float x = elements[0][0] * vector.x + elements[0][1] * vector.y + elements[0][2] * vector.z + elements[0][3] * vector.w;
  float y = elements[1][0] * vector.x + elements[1][1] * vector.y + elements[1][2] * vector.z + elements[1][3] * vector.w;
  float z = elements[2][0] * vector.x + elements[2][1] * vector.y + elements[2][2] * vector.z + elements[2][3] * vector.w;
  float w = elements[3][0] * vector.x + elements[3][1] * vector.y + elements[3][2] * vector.z + elements[3][3] * vector.w;
  return Vector4(x, y, z, w);

}