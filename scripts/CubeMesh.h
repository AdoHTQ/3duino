// vertex array
Vector3* vectors[] = {new Vector3(-1.0, -1.0, 1.0),new Vector3(-1.0, 1.0, 1.0),new Vector3(-1.0, -1.0, -1.0),new Vector3(-1.0, 1.0, -1.0),new Vector3(1.0, -1.0, 1.0),new Vector3(1.0, 1.0, 1.0),new Vector3(1.0, -1.0, -1.0),new Vector3(1.0, 1.0, -1.0),};
// face array
Vector3I* faces[] = {new Vector3I(2, 3, 1),new Vector3I(4, 7, 3),new Vector3I(8, 5, 7),new Vector3I(6, 1, 5),new Vector3I(7, 1, 3),new Vector3I(4, 6, 8),new Vector3I(2, 4, 3),new Vector3I(4, 8, 7),new Vector3I(8, 6, 5),new Vector3I(6, 2, 1),new Vector3I(7, 5, 1),new Vector3I(4, 2, 6),};
// final mesh object
Mesh cube(vectors, faces);