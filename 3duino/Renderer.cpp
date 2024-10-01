#include "Renderer.h" 

Mesh::Mesh (int numVertices, int numFaces)
{
  vertices = new Vector3[numVertices];
  faces = new Vector3I[numFaces];
  this -> numVertices = numVertices;
  this -> numFaces = numFaces;
}

Mesh::Mesh (Vector3* vertices, Vector3I* faces, int numVertices, int numFaces) {
  this -> vertices = vertices;
  this -> faces = faces;
  this -> numVertices = numVertices;
  this -> numFaces = numFaces;

}

Mesh::~Mesh() {
  delete[] vertices;
  delete[] faces;
}



Renderer::Renderer(DisplayDriver* dis)
{
  this->dis = dis;
}

int sign(int value)
{
  if (value > 0) return 1;
  if (value == 0) return 0;
  if (value < 0) return -1;
}

void Renderer::drawLine(int x1, int y1, int x2, int y2)
{
  int y = y1;
  int x = x1;
  int dx = abs(x2-x1);
  int dy = abs(y2-y1);
  int s1 = sign(x2-x1);
  int s2 = sign(y2-y1);

  bool interchange;

  if (dy > dx)
  {
    int t = dx;
    dx = dy;
    dy = t;
    interchange = true;
  } 
  else {interchange = false;}
  
  int e = 2*dy - dx;
  int a = 2*dy;
  int b = 2*dy - 2*dx;
  dis->setPixel(x, y, true);

  for (int i = 1; i <= dx; i++)
  {
    if (e < 0) 
    {
      if (interchange) {y += s2;}
      else {x += s1;}
      e += a;
    }
    else
    {
      y += s2;
      x += s1;
      e += b;
    }
    dis -> setPixel(x, y, true);
  }
}

void Renderer::drawLine(Vector2I* p1, Vector2I* p2)
{
  drawLine(p1->x, p1->y, p2->x, p2->y);
}

void Renderer::drawTriangle(Vector2I* p1, Vector2I* p2, Vector2I* p3)
{
  drawLine(p1, p2);
  drawLine(p2, p3);
  drawLine(p3, p1);
}

Vector2I Renderer::transformVertex(Vector3* vertex)
{
  // Orthographic projection
  return Vector2I(round(vertex->x), round(vertex->y));
}

void Renderer::renderMesh(Mesh *mesh)
{
  //Loop over each face
  for (int i = 0; i <= sizeof(&mesh->faces)/sizeof(&mesh->faces[0]); i++)
  {
    Vector2I p1 = transformVertex(&mesh->vertices[mesh->faces[i].x]);
    Vector2I p2 = transformVertex(&mesh->vertices[mesh->faces[i].y]);
    Vector2I p3 = transformVertex(&mesh->vertices[mesh->faces[i].z]);
    drawTriangle(&p1, &p2, &p3);
  }
}

