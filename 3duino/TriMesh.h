#include <BasicLinearAlgebra.h>
// vertex array
Matrix<3> vertices[] = {Matrix<3>(0.0, 0.0, -5.0),Matrix<3>(0.0, 1.0, -5.0),Matrix<3>(1.0, 0.0, -10.0),};
// face array
Matrix<3,1,int> faces[] = {Matrix<3,1,int>(1, 2, 3),};
// final mesh object
Mesh tri(vertices, faces, 3, 1);