#include "Vectors.h"

bool VectorABC::checkType(int type) {
  return type == axisCount;
}

Vector::Vector() {
  axisCount = 4;
  axes = new float[axisCount];
  axes[0] = 0;
  axes[1] = 0;
  axes[2] = 0;
  axes[3] = 0;
}

Vector::Vector(float x, float y) {
  axisCount = 2;
  axes = new float[axisCount];
  axes[0] = x;
  axes[1] = y;
}

Vector::Vector(float x, float y, float z) {
  axisCount = 3;
  axes = new float[axisCount];
  axes[0] = x;
  axes[1] = y;
  axes[2] = z;
}

Vector::Vector(float x, float y, float z, float w) {
  axisCount = 4;
  axes = new float[axisCount];
  axes[0] = x;
  axes[1] = y;
  axes[2] = z;
  axes[3] = w;
}

float Vector::operator[](int index) {
  return axes[index];
}

Vector::~Vector() {
  delete[] axes;
}


VectorI::VectorI() {
  axisCount = 4;
  axes = new int[axisCount];
  axes[0] = 0;
  axes[1] = 0;
  axes[2] = 0;
  axes[3] = 0;
}

VectorI::VectorI(int x, int y) {
  axisCount = 2;
  axes = new int[axisCount];
  axes[0] = x;
  axes[1] = y;
}

VectorI::VectorI(int x, int y, int z) {
  axisCount = 3;
  axes = new int[axisCount];
  axes[0] = x;
  axes[1] = y;
  axes[2] = z;
}

VectorI::VectorI(int x, int y, int z, int w) {
  axisCount = 4;
  axes = new int[axisCount];
  axes[0] = x;
  axes[1] = y;
  axes[2] = z;
  axes[3] = w;
}

int VectorI::operator[](int index) {
  return axes[index];
}

VectorI::~VectorI() {
  delete[] axes;
}
