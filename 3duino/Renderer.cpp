#include "Renderer.h" 


Mesh::Mesh (int numVertices, int numFaces)
{
  vertices = new BLA::Matrix<3>[numVertices];
  faces = new BLA::Matrix<3,1,int>[numFaces];
  this -> numVertices = numVertices;
  this -> numFaces = numFaces;
}

Mesh::Mesh (BLA::Matrix<3>* vertices, BLA::Matrix<3,1,int>* faces, int numVertices, int numFaces) {
  this -> vertices = new BLA::Matrix<3>[numVertices];
  for (int i = 0; i < numVertices; i++) {
    this -> vertices[i] = vertices[i];  
  }

  this -> faces = new BLA::Matrix<3,1,int>[numFaces];
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



Renderer::Renderer()
{
  createProjectionMatrix();

  oled.begin();
  oled.fillScreen(0x0000);
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

void Renderer::drawTriangle(BLA::Matrix<2,1,int> p1, BLA::Matrix<2,1,int> p2, BLA::Matrix<2,1,int> p3, uint16_t color)
{
  //drawLine(p1, p2, color);
  oled.drawTriangle(p1(0), p1(1), p2(0), p2(1), p3(0), p3(1), color);
}

void Renderer::drawLine(BLA::Matrix<2,1,int> p1, BLA::Matrix<2,1,int> p2, uint16_t color)
{
  sendCommand(0x21);
  sendCommand(p1(0));
  sendCommand(p1(1));
  sendCommand(p2(0));
  sendCommand(p2(1));
  sendCommand(0xFF);
  sendCommand(0xFF);
  sendCommand(0xFF);
}

void Renderer::sendCommand(uint8_t command)
{
  digitalWrite(command, LOW);
  digitalWrite(cs, LOW);
  digitalWrite(clock, LOW);

  shiftOut(data, clock, MSBFIRST, command);

  digitalWrite(cs, HIGH);
}

BLA::Matrix<2,1,int> Renderer::transformVertex(BLA::Matrix<3> vertex)
{ 
  BLA::Matrix<4,4> transformation = BLA::Matrix<4,4>(1, 0, 0, position(0), 0, 1, 0, position(1), 0, 0, 1, position(2), 0, 0, 0, 1);

  BLA::Matrix<4,1> homogenous = {vertex(0), vertex(1), vertex(2), 1.0}; 
  
  //Perspective projection
  homogenous = transformation * homogenous;
  homogenous = projection * homogenous;
  
  //Orthographic projection
  return Matrix<2,1,int>(round((homogenous(0) / homogenous(3) + 1.0) * res(0) / 2.0), round((homogenous(1) / homogenous(3) + 1.0) * res(1) / 2.0));
}

void Renderer::renderMesh(Mesh *mesh, uint16_t color)
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
    BLA::Matrix<2,1,int> p1 = transformVertex(mesh->vertices[mesh->faces[i](0)-1]);
    BLA::Matrix<2,1,int> p2 = transformVertex(mesh->vertices[mesh->faces[i](1)-1]);
    BLA::Matrix<2,1,int> p3 = transformVertex(mesh->vertices[mesh->faces[i](2)-1]);

    drawTriangle(p1, p2, p3, color);
  }
}

void Renderer::clearScreen()
{
  oled.fillScreen(0x0000);
  // digitalWrite(reset, HIGH);
  // delay(20);
  // digitalWrite(reset, LOW);
}

