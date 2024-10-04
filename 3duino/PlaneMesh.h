// vertex array
Vector vectors[] = {Vector(0.0, 0.001998, -0.22573)/*Top*/,Vector(0.35355, 0.20479, -0.51534)/*Bottom RIght*/,Vector(0.0, -0.40758, -0.51252)/*Left*/,Vector(-0.35355, 0.20479, -0.51534)/*Top Right*/,Vector(0.0, 0.40758, -0.80496)/*Right*/,Vector(-0.35355, -0.20479, -0.80213)/*Top Left*/,Vector(0.35355,-0.20479,-0.80213)/*Bottom Left*/};
// face array
VectorI faces[] = {VectorI(0, 1, 2),VectorI(0, 1, 3),VectorI(0, 2, 3),VectorI(1, 3, 4),VectorI(2, 3, 5),VectorI(2, 1, 6)};
// final mesh object
Mesh plane(vectors, faces, 7, 6);
