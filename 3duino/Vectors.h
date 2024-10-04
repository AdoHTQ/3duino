#ifndef VECTORS_H
#define VECTORS_H

class VectorABC {
public:
    int numVerteces;

    bool checkType(int);
};

class Vector: public VectorABC {
public:

    float* verteces;
    
    Vector();
    Vector(float, float);
    Vector(float, float, float);
  Vector(float, float, float, float);

  ~Vector();
};

class VectorI: public VectorABC {
public:

    int* verteces;

    VectorI();
    VectorI(int, int);
    VectorI(int, int, int);
    VectorI(int, int, int, int);

    ~VectorI();
};

#endif
