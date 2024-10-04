#ifndef VECTORS_H
#define VECTORS_H

class Vector {
public:

    int numVerteces;

    float* verteces;
    
    Vector();
    Vector(float, float);
    Vector(float, float, float);
  Vector(float, float, float, float);

  ~Vector();
};

class VectorI {
public:

    int numVerteces;

    int* verteces;

    VectorI();
    VectorI(int, int);
    VectorI(int, int, int);
    VectorI(int, int, int, int);

    ~VectorI();
};

#endif
