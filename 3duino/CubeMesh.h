#include <BasicLinearAlgebra.h>
// vertex array
Matrix<3> vertices[] = {Matrix<3>(-1.0, -1.0, 1.0),Matrix<3>(-1.0, 1.0, 1.0),Matrix<3>(-1.0, -1.0, -1.0),Matrix<3>(-1.0, 1.0, -1.0),Matrix<3>(1.0, -1.0, 1.0),Matrix<3>(1.0, 1.0, 1.0),Matrix<3>(1.0, -1.0, -1.0),Matrix<3>(1.0, 1.0, -1.0),};
// face array
Matrix<3,1,int> faces[] = {Matrix<3,1,int>(2, 3, 1),Matrix<3,1,int>(4, 7, 3),Matrix<3,1,int>(8, 5, 7),Matrix<3,1,int>(6, 1, 5),Matrix<3,1,int>(7, 1, 3),Matrix<3,1,int>(4, 6, 8),Matrix<3,1,int>(2, 4, 3),Matrix<3,1,int>(4, 8, 7),Matrix<3,1,int>(8, 6, 5),Matrix<3,1,int>(6, 2, 1),Matrix<3,1,int>(7, 5, 1),Matrix<3,1,int>(4, 2, 6),};
// final mesh object
Mesh cube(vertices, faces, 8, 12);