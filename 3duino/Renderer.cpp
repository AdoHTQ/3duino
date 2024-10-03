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

  createProjectionMatrix();

  //Serial.println(transformVertex(&Vector3(1, 1, 2)).x);
}


void Renderer::createProjectionMatrix()
{
  projection = Matrix44();
  projection.setElement(0, 0, 1 / (aspect * tan(fov / 2)));
  projection.setElement(1, 1, 1 / tan(fov / 2));
  projection.setElement(2, 2, (far + near) / (near - far));
  projection.setElement(2, 3, (2 * far * near) / (near - far));
  projection.setElement(3, 2, -1);
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
  Vector4 homogenous = Vector4(vertex->x, vertex->y, vertex->z, 1.0);
  //homogenous.y -= 0.2;
  homogenous = projection * homogenous;
  // Orthographic projection
  //Serial.println(homogenous.x / homogenous.w);
  return Vector2I(round((homogenous.x / homogenous.w + 1.0) * (15.0/2.0)), round((homogenous.y / homogenous.w + 1.0) * (15.0/2.0)));
}

void Renderer::renderMesh(Mesh *mesh)
{ 
  if (analogRead(A1) > 900) 
  {
    fov += 0.1;
    createProjectionMatrix();
  }
  if (analogRead(A1) < 100) 
  {
    fov -= 0.1;
    createProjectionMatrix();
  }

  //Loop over each face
  for (int i = 0; i < mesh->numFaces; i++)
  {
    //Vector3 transform = Vector3(0.0, 0.0, 0.0);
    Vector2I p1 = transformVertex(&mesh->vertices[mesh->faces[i].x]);
    Vector2I p3 = transformVertex(&mesh->vertices[mesh->faces[i].z]);
    Vector2I p2 = transformVertex(&mesh->vertices[mesh->faces[i].y]);
    drawTriangle(&p1, &p2, &p3);
  }
}

