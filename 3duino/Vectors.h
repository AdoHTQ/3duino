#ifndef VECTORS_H
#define VECTORS_H

class VectorABC {
public:
    int axisCount;

    bool checkType(int);
};

class Vector: public VectorABC {
public:

  float* axes;
  
  Vector();
  Vector(float, float);
  Vector(float, float, float);
  Vector(float, float, float, float);

  float operator[](int index);

  ~Vector();
};

class VectorI: public VectorABC {
public:

  int* axes;

  VectorI();
  VectorI(int, int);
  VectorI(int, int, int);
  VectorI(int, int, int, int);

  int operator[](int index);

  ~VectorI();
};

#endif
