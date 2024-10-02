// vertex array
Vector3 vectors[] = {Vector3(0.0, -1.0, 0.0),Vector3(0.7236, -0.447215, 0.52572),Vector3(-0.276385, -0.447215, 0.85064),Vector3(-0.894425, -0.447215, 0.0),Vector3(-0.276385, -0.447215, -0.85064),Vector3(0.7236, -0.447215, -0.52572),Vector3(0.276385, 0.447215, 0.85064),Vector3(-0.7236, 0.447215, 0.52572),Vector3(-0.7236, 0.447215, -0.52572),Vector3(0.276385, 0.447215, -0.85064),Vector3(0.894425, 0.447215, 0.0),Vector3(0.0, 1.0, 0.0),};
// face array
Vector3I faces[] = {Vector3I(1, 2, 3),Vector3I(2, 1, 6),Vector3I(1, 3, 4),Vector3I(1, 4, 5),Vector3I(1, 5, 6),Vector3I(2, 6, 11),Vector3I(3, 2, 7),Vector3I(4, 3, 8),Vector3I(5, 4, 9),Vector3I(6, 5, 10),Vector3I(2, 11, 7),Vector3I(3, 7, 8),Vector3I(4, 8, 9),Vector3I(5, 9, 10),Vector3I(6, 10, 11),Vector3I(7, 11, 12),Vector3I(8, 7, 12),Vector3I(9, 8, 12),Vector3I(10, 9, 12),Vector3I(11, 10, 12),};
// final mesh object
Mesh icosphere(vectors, faces, 12, 20);