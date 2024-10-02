// vertex array
Vector3 vectors[] = {Vector3(0.0, 0.707107, -0.707107),Vector3(0.0, -0.0, -1.0),Vector3(0.0, -0.707107, -0.707107),Vector3(0.707107, 0.707107, 0.0),Vector3(1.0, -0.0, 0.0),Vector3(0.707107, -0.707107, 0.0),Vector3(0.0, -1.0, 0.0),Vector3(0.0, 1.0, 0.0),Vector3(-0.0, 0.707106, 0.707107),Vector3(-0.0, -0.0, 1.0),Vector3(-0.0, -0.707107, 0.707107),};
// face array
Vector3I faces[] = {Vector3I(3, 2, 5),Vector3I(1, 8, 4),Vector3I(7, 3, 6),Vector3I(2, 1, 4),Vector3I(6, 5, 10),Vector3I(4, 8, 9),Vector3I(7, 6, 11),Vector3I(5, 4, 9),};
// final mesh object
Mesh sphere(vectors, faces, 11, 8);