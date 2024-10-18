#include "Renderer.h" 

Mesh::Mesh (int numVertices, int numFaces)
{
  vertices = new BLA::Matrix<3>[numVertices];
  faces = new BLA::Matrix<3,1,int>[numFaces];
  this -> numVertices = numVertices;
  this -> numFaces = numFaces;
}

// Mesh::Mesh (BLA::Matrix<3>* vertices, BLA::Matrix<3,1,int>* faces, int numVertices, int numFaces) {
//   this -> vertices = BLA::Matrix<3>[numVertices];
//   for (int i = 0; i < numVertices; i++) {
//     this -> vertices[i] = vertices[i];  
//   }

//   this -> faces = BLA::Matrix<3,1>[numFaces];
//   for (int i = 0; i < numFaces; i++) {
//     this -> faces[i] = faces[i];  
//   }
//   this -> numVertices = numVertices;
//   this -> numFaces = numFaces;
// }

Mesh::~Mesh() {
  delete[] vertices;
  delete[] faces;
}



Renderer::Renderer()
{
  createProjectionMatrix();

  //Serial.println(transformVertex(&Vector3(1, 1, 2)).x);
}


void Renderer::createProjectionMatrix()
{
  projection = BLA::Matrix<4,4>();
  projection(0, 0) = 1 / (aspect * tan(fov / 2));
  projection(1, 1) = 1 / tan(fov / 2);
  projection(2, 2) = (far + near) / (near - far);
  projection(2, 3) = (2 * far * near) / (near - far);
  projection(3, 2) = -1;
}

BLA::Matrix<3,1,int> Renderer::transformVertex(BLA::Matrix<3> vertex)
{ 
  BLA::Matrix<4,1> homogenous = {vertex(0), vertex(1), vertex(2), 1.0}; 
  
  //Perspective projection
  homogenous = projection * homogenous;
  
  //Orthographic projection
  //return new VectorI(round((homogenous[0] / homogenous[3] + 1.0) * dis->resX / 2.0), round((homogenous[1] / homogenous[3] + 1.0) * dis->resX / 2.0));
  
  BLA::Matrix<3,1,int> result = {homogenous(0), homogenous(1), homogenous(2)};

  return result;
  //return new VectorI(0, 0, 0);
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
    //VectorI* p1 = transformVertex(&mesh->vertices[mesh->faces[i][0]-1]);
    //VectorI tmp = *p1;
    //VectorI p2 = transformVertex(mesh->vertices[mesh->faces[i][1]-1]);
    //VectorI p3 = transformVertex(mesh->vertices[mesh->faces[i][2]-1]);
    //Serial.println(tmp[0]);
    //Serial.println(tmp[1]);
    // Serial.println(p2[0]);
    // Serial.println(p2[1]);
    // Serial.println(p3[0]);
    // Serial.println(p3[1]);
    //dis->drawTriangle(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], 0xFFFF);
    //dis->drawTriangle(20, 20, 96, 64, 10, 40, 0xFFFF);
    //delete p1;
  }
}

