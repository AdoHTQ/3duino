import sys ,os

path = " "

if len(sys.argv) < 2:
    print("Please pass a pathname as an argument!")
    quit()


path = sys.argv[1]

if not os.path.exists(path):
    print("That path doesn't exist...")
    quit()

if not path.endswith(".obj"):
    print("That's not an obj file!\nI can't parse that!")
    quit()

print("Interpreting obj file...")

output = ""

with open(path, "r") as file:

    name = ""
    vectors = []
    faces = []

    while (file):
        line = file.readline()
        if line == "":
            break 

        minivectors = []
        minifaces = []

        match line[0]:
            case "o":
                name = line[2:-1]
            case "v" | "f":
                tmp = line[0]
                while (line.find(" ") != -1):
                    line = line[line.find(" ") + 1:]
                    # python ternary operator :)
                    (minivectors if tmp == "v" else minifaces).append(line[:line.find(" ")])
        if len(minivectors) > 0:
            vectors.append(minivectors)

        if len(minifaces) > 0:
            faces.append(minifaces)


    output += "// vertex array\n"
    output += "Vector3* vectors[] = {"
    for vector in vectors:
        output += f"new Vector3({float(vector[0])}, {float(vector[1])}, {float(vector[2])}),"
    output += "};\n"

    output += "// face array\n"
    output += "Vector3I* faces[] = {"
    for face in faces:
        output += f"new Vector3I({int(face[0])}, {int(face[1])}, {int(face[2])}),"
    output += "};\n"

    output += "// final mesh object\n"
    output += f"Mesh {name.lower()}(vectors, faces);"



    with open(f"{name.capitalize()}Mesh.h", "w") as out:
        out.write(output);

print("Complete!")

