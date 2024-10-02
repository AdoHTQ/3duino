// vertex array
Vector3 vectors[] = {Vector3(-1.0, -1.0, -1.0),Vector3(-1.0, 1.0, -1.5),Vector3(1.0, -1.0, -1.5),Vector3(1.0, 1.0, -1.5),};
// face array
Vector3I faces[] = {Vector3I(0, 1, 2), Vector3I(1, 2, 3)};
// final mesh object
Mesh plane(vectors, faces, 4, 2);