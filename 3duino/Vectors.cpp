#include "Vectors.h"

bool VectorABC::checkType(int type) {
    return type == numVerteces;
}

Vector::Vector() {
  numVerteces = 4;
  verteces = new float[numVerteces];
  verteces[0] = 0;
  verteces[1] = 0;
  verteces[2] = 0;
  verteces[3] = 0;
}

Vector::Vector(float x, float y) {
    numVerteces = 2;
    verteces = new float[numVerteces];
    verteces[0] = x;
    verteces[1] = y;
}

Vector::Vector(float x, float y, float z) {
    numVerteces = 3;
    verteces = new float[numVerteces];
    verteces[0] = x;
    verteces[1] = y;
    verteces[2] = z;
}

Vector::Vector(float x, float y, float z, float w) {
    numVerteces = 4;
    verteces = new float[numVerteces];
    verteces[0] = x;
    verteces[1] = y;
    verteces[2] = z;
    verteces[3] = w;
}

Vector::~Vector() {
    delete[] verteces;
}


VectorI::VectorI() {
  numVerteces = 4;
  verteces = new int[numVerteces];
  verteces[0] = 0;
  verteces[1] = 0;
  verteces[2] = 0;
  verteces[3] = 0;

}

VectorI::VectorI(int x, int y) {
    numVerteces = 2;
    verteces = new int[numVerteces];
    verteces[0] = x;
    verteces[1] = y;
}

VectorI::VectorI(int x, int y, int z) {
    numVerteces = 3;
    verteces = new int[numVerteces];
    verteces[0] = x;
    verteces[1] = y;
    verteces[2] = z;
}

VectorI::VectorI(int x, int y, int z, int w) {
    numVerteces = 4;
    verteces = new int[numVerteces];
    verteces[0] = x;
    verteces[1] = y;
    verteces[2] = z;
    verteces[3] = w;
}

VectorI::~VectorI() {
    delete[] verteces;
}
