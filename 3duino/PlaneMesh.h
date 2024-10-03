// vertex array
Vector3 vectors[] = {Vector3(0.0, 0.001998, -0.22573)/*Top*/,Vector3(0.35355, 0.20479, -0.51534)/*Bottom RIght*/,Vector3(0.0, -0.40758, -0.51252)/*Left*/,Vector3(-0.35355, 0.20479, -0.51534)/*Top Right*/,Vector3(0.0, 0.40758, -0.80496)/*Right*/,Vector3(-0.35355, -0.20479, -0.80213)/*Top Left*/,Vector3(0.35355,-0.20479,-0.80213)/*Bottom Left*/};
// face array
Vector3I faces[] = {Vector3I(0, 1, 2),Vector3I(0, 1, 3),Vector3I(0, 2, 3),Vector3I(1, 3, 4),Vector3I(2, 3, 5),Vector3I(2, 1, 6)};
// final mesh object
Mesh plane(vectors, faces, 7, 6);