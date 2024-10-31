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

  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(reset, OUTPUT);
  pinMode(command, OUTPUT);
  pinMode(cs, OUTPUT);

  digitalWrite(reset, LOW);
  delay(50);
  digitalWrite(reset, HIGH);
  delay(100);

  sendCommand(0xAE); //Display off

  sendCommand(0xA0); //Set remap

  sendCommand(0x72); //RGB Color

  sendCommand(0xA1); //Start line
  sendCommand(0x00);

  sendCommand(0xA2); //Display offset
  sendCommand(0x00);

  sendCommand(0xA4); //Normal display
  sendCommand(0xA8); //Set multiplex
  sendCommand(0x3F);

  sendCommand(0xAD); //Set master
  sendCommand(0x8E);

  sendCommand(0xB0); //Power mode
  sendCommand(0x0B);

  sendCommand(0xB1); //Precharge
  sendCommand(0x31);

  sendCommand(0xB3); //Clock div
  sendCommand(0xF0);

  sendCommand(0x8A); //Precharge A
  sendCommand(0x64);

  sendCommand(0x8B); //Precharge B
  sendCommand(0x78);

  sendCommand(0x8C); //Precharge C
  sendCommand(0x64);

  sendCommand(0xBB); //Precharge Level
  sendCommand(0x3A);

  sendCommand(0xBE); //VCOMH
  sendCommand(0x3E);

  // sendCommand(0x87); //Mastercurrent
  // sendCommand(0x06);

  sendCommand(0x81); //Contrast A
  sendCommand(0x91);

  sendCommand(0x82); //Contrast B
  sendCommand(0x50);

  sendCommand(0x83); //Contrast C
  sendCommand(0x7D);

  sendCommand(0xAF); //Display on

  clearScreen();
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
  drawLine(p1, p2, color);
  drawLine(p2, p3, color);
  drawLine(p3, p1, color);
  //oled.drawTriangle(p1(0), p1(1), p2(0), p2(1), p3(0), p3(1), color);
}

void Renderer::drawLine(BLA::Matrix<2,1,int> p1, BLA::Matrix<2,1,int> p2, uint16_t color)
{
  sendCommand(0x21);
  sendCommand(constrain(p1(0), 10, 80));
  sendCommand(constrain(p1(1), 10, 50));
  sendCommand(constrain(p2(0), 10, 80));
  sendCommand(constrain(p2(1), 10, 50));
  
  sendCommand(0xFF);
  sendCommand(0xFF);
  sendCommand(0xFF);
  //delay(100);
}

void Renderer::fillScreen(uint16_t color)
{
  //Enable fill
  sendCommand(0x26);
  sendCommand(0x01);

  //Draw full screen rect
  sendCommand(0x22);
  sendCommand(1);
  sendCommand(1);
  sendCommand(94);
  sendCommand(62);
  sendCommand(0x00);
  sendCommand(0x00);
  sendCommand(0x00);
  sendCommand(0x00);
  sendCommand(0x00);
  sendCommand(0x00);
  //delay(100);
}

void Renderer::sendCommand(uint8_t command)
{
  digitalWrite(command, LOW);
  digitalWrite(cs, LOW);
  digitalWrite(clock, LOW);

  shiftOut(data, clock, MSBFIRST, command);

  digitalWrite(cs, HIGH);
}

void Renderer::sendData(uint8_t din)
{
  digitalWrite(command, HIGH);
  digitalWrite(cs, LOW);
  digitalWrite(clock, LOW);

  shiftOut(data, clock, MSBFIRST, din);

  digitalWrite(cs, HIGH);
}

BLA::Matrix<2,1,int> Renderer::transformVertex(BLA::Matrix<3> vertex)
{ 
  BLA::Matrix<4,4> transformation = BLA::Matrix<4,4>(
    cos(rotation(1)) * cos(rotation(2)) * scale(0), -sin(rotation(2)), sin(rotation(1)), position(0), 
    sin(rotation(2)), cos(rotation(0)) * cos(rotation(2)) * scale(1), -sin(rotation(0)), position(1), 
    -sin(rotation(1)), sin(rotation(0)), cos(rotation(1)) * cos(rotation(0)) * scale(2), position(2), 
    0, 0, 0, 1);

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
  fillScreen(0x0000);
}

