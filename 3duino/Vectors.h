#ifndef VECTORS_H
#define VECTORS_H

class Vector2 {
public:
  float x;
  float y;

  Vector2();
  Vector2(float x, float y);
};

class Vector2I {
public:
  int x;
  int y;

  Vector2I();
  Vector2I(int x, int y);
};

class Vector3 {
public:
  float x;
  float y;
  float z;

  Vector3();
  Vector3(float x, float y, float z);
};

class Vector3I {
public:
  int x;
  int y;
  int z;

  Vector3I();
  Vector3I(int x, int y, int z);
};

class Vector4 {
public:
  float x;
  float y;
  float z;
  float w;

  Vector4();
  Vector4(float x, float y, float z, float w);
};

class Vector4I {
public:
  int x;
  int y;
  int z;
  int w;

  Vector4I();
  Vector4I(int x, int y, int z, int w);
};

#endif
