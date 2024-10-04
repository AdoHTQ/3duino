// vertex array
Vector vectors[] = {Vector(-1.0, -1.0, -0.0),Vector(1.0, -1.0, -0.0),Vector(-1.0, 1.0, 0.0),Vector(1.0, 1.0, 0.0),};
// face array
VectorI faces[] = {VectorI(2, 3, 1),VectorI(2, 4, 3),};
// final mesh object
Mesh plane(vectors, faces, 4, 2);