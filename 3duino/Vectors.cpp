#include "Vectors.h"

Vector2::Vector2()
{
  x = 0;
  y = 0;
}

Vector2::Vector2(float x, float y)
{
  this->x = x;
  this->y = y;
}


Vector2I::Vector2I()
{
  x = 0;
  y = 0;
}

Vector2I::Vector2I(int x, int y)
{
  this->x = x;
  this->y = y;
}


Vector3::Vector3()
{
  x = 0;
  y = 0;
  z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}


Vector3I::Vector3I()
{
  x = 0;
  y = 0;
  z = 0;
}

Vector3I::Vector3I(int x, int y, int z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}