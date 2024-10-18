#include <BasicLinearAlgebra.h>// vertex array
Matrix<3> vertices[] = {Matrix<3>(0.0, 0.707107, -0.707107),Matrix<3>(0.0, -0.0, -1.0),Matrix<3>(0.0, -0.707107, -0.707107),Matrix<3>(0.707107, 0.707107, 0.0),Matrix<3>(1.0, -0.0, 0.0),Matrix<3>(0.707107, -0.707107, 0.0),Matrix<3>(0.0, -1.0, 0.0),Matrix<3>(0.0, 1.0, 0.0),Matrix<3>(-0.0, 0.707106, 0.707107),Matrix<3>(-0.0, -0.0, 1.0),Matrix<3>(-0.0, -0.707107, 0.707107),};
// face array
Matrix<3,1,int> faces[] = {Matrix<3,1,int>(3, 2, 5, 6),Matrix<3,1,int>(1, 8, 4),Matrix<3,1,int>(7, 3, 6),Matrix<3,1,int>(2, 1, 4, 5),Matrix<3,1,int>(6, 5, 10, 11),Matrix<3,1,int>(4, 8, 9),Matrix<3,1,int>(7, 6, 11),Matrix<3,1,int>(5, 4, 9, 10),};
// final mesh object
Mesh sphere(vertices, faces, 11, 8);