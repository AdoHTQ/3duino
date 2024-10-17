// vertex array
Vector vectors[] = {Vector(-1.0, -1.0, 1.0),Vector(-1.0, 1.0, 1.0),Vector(-1.0, -1.0, -1.0),Vector(-1.0, 1.0, -1.0),Vector(1.0, -1.0, 1.0),Vector(1.0, 1.0, 1.0),Vector(1.0, -1.0, -1.0),Vector(1.0, 1.0, -1.0),};
// face array
VectorI faces[] = {VectorI(2, 3, 1),VectorI(4, 7, 3),VectorI(8, 5, 7),VectorI(6, 1, 5),VectorI(7, 1, 3),VectorI(4, 6, 8),VectorI(2, 4, 3),VectorI(4, 8, 7),VectorI(8, 6, 5),VectorI(6, 2, 1),VectorI(7, 5, 1),VectorI(4, 2, 6),};
// final mesh object
Mesh cube(vectors, faces, 8, 12);