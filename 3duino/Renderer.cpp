#include "Renderer.h" 

Mesh::Mesh (int numVertices, int numFaces)
{
  vertices = new Vector[numVertices];
  faces = new VectorI[numFaces];
  this -> numVertices = numVertices;
  this -> numFaces = numFaces;
}

Mesh::Mesh (Vector* vertices, VectorI* faces, int numVertices, int numFaces) {
  this -> vertices = new Vector[numVertices];
  for (int i = 0; i < numVertices; i++) {
    this -> vertices[i] = vertices[i];  
  }

  this -> faces = new VectorI[numFaces];
  for (int i = 0; i < numFaces; i++) {
    this -> faces[i] = faces[i];  
  }
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

VectorI* Renderer::transformVertex(Vector* ver)
{
  Vector vertex = *ver;
  if (vertex.axisCount < 3) {return VectorI();}
  
  Vector homogenous = Vector(vertex[0], vertex[1], vertex[2], 1.0); 
  
  // Perspective projection
  homogenous = projection * homogenous;
  
  // Orthographic projection
  Serial.println("fesnuoifsdj");
  return new VectorI(round((homogenous[0] / homogenous[3] + 1.0) * dis->resX / 2.0), round((homogenous[1] / homogenous[3] + 1.0) * dis->resX / 2.0));
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
    // Serial.print("Count: ");
    // Serial.println(i);
    //Serial.println(sizeof(mesh->vertices));
    //Serial.println(mesh->vertices[mesh->faces[0][0]-1][0]);
    //Vector3 transform = Vector3(0.0, 0.0, 0.0);
    VectorI p1 = transformVertex(&mesh->vertices[mesh->faces[i][0]-1]);
    //VectorI p2 = transformVertex(mesh->vertices[mesh->faces[i][1]-1]);
    //VectorI p3 = transformVertex(mesh->vertices[mesh->faces[i][2]-1]);
    Serial.println(p1[0]);
    Serial.println(p1[1]);
    // Serial.println(p2[0]);
    // Serial.println(p2[1]);
    // Serial.println(p3[0]);
    // Serial.println(p3[1]);
    //dis->drawTriangle(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], 0xFFFF);
    //dis->drawTriangle(20, 20, 96, 64, 10, 40, 0xFFFF);
  }
}

