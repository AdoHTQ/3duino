#include "Renderer.h" 

Mesh::Mesh (int numVertices, int numFaces)
{
  vertices = new Vector[numVertices];
  faces = new VectorI[numFaces];
  this -> numVertices = numVertices;
  this -> numFaces = numFaces;
}

Mesh::Mesh (Vector* vertices, VectorI* faces, int numVertices, int numFaces) {
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

void Renderer::drawTriangle(VectorI p1, VectorI p2, VectorI p3)
{
  dis->drawLine(p1, p2);
  dis->drawLine(p2, p3);
  dis->drawLine(p3, p1);
}

VectorI Renderer::transformVertex(Vector vertex)
{
  if (vertex.axisCount < 3) {return VectorI();}
  Vector homogenous = Vector(vertex[0], vertex[1], vertex[2], 1.0);
  
  //homogenous.y -= 0.2;
  homogenous = projection * homogenous;
  // Orthographic projection
  
  return VectorI(round((homogenous[0] / homogenous[3] + 1.0) * ((float)dis->resX/2.0)), round((homogenous[1] / homogenous[3] + 1.0) * ((float)dis->resX/2.0)));
}

void Renderer::renderMesh(Mesh *mesh)
{ 
  // if (analogRead(A1) > 900) 
  // {
  //   fov += 0.1;
  //   createProjectionMatrix();
  // }
  // if (analogRead(A1) < 100) 
  // {
  //   fov -= 0.1;
  //   createProjectionMatrix();
  // }

  //Loop over each face
  for (int i = 0; i < mesh->numFaces; i++)
  {
    //Vector3 transform = Vector3(0.0, 0.0, 0.0);
    VectorI p1 = transformVertex(mesh->vertices[mesh->faces[i][0]]);
    VectorI p3 = transformVertex(mesh->vertices[mesh->faces[i][1]]);
    VectorI p2 = transformVertex(mesh->vertices[mesh->faces[i][2]]);
    Serial.println(p1[0]);
    Serial.println(p1[1]);
    Serial.println(p2[0]);
    Serial.println(p2[1]);
    Serial.println(p3[0]);
    Serial.println(p3[1]);
    drawTriangle(p1, p2, p3);
  }
}

