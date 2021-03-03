#include "Sphere.h"

Sphere::Sphere() {}

Sphere::Sphere(glm::vec3 center, int stackCount, int sectorCount, std::string name) {
	sphere = CreateSphere(center, stackCount, sectorCount, name);
	this->stackCount = stackCount;
	this->sectorCount = sectorCount;
    this->name = name;
    //std::cout << "Planet name: " << this->name;
}

Mesh* Sphere::CreateSphere(glm::vec3 center, int stackCount, int sectorCount, std::string name) {
    float radius = 1.0f;
    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    float s, t;                                     // vertex texCoord

    float sectorStep = 2 * M_PI / sectorCount; // longitude
    float stackStep = M_PI / stackCount;       // latitude
    float sectorAngle, stackAngle;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoords;

    for (int i = 0; i <= stackCount; ++i) {
        
        stackAngle = M_PI / 2 - i * stackStep;   // starting from pi/2 to -pi/2
        xy = radius * cos(stackAngle);                  // r * cos(u)
        z = radius * sin(stackAngle);                   // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cos(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sin(sectorAngle);             // r * cos(u) * sin(v)
            vertices.push_back(glm::vec3(x, y, z));

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            normals.push_back(glm::vec3(nx, ny, nz));

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            textureCoords.push_back(glm::vec2(s, t));
        }

        /*
            Each sector in a stack requires 2 triangles.
            If the first vertex index in the current stack is k1
            and the next stack is k2, then the counterclockwise orders
            of vertex indices of 2 triangles are:
            k1 - k2 - k1+1
            k1+1 - k2 - k2+1

            // generate index list of sphere triangles
            // k1--k1+1
            // |  / |
            // | /  |
            // k2--k2+1
        */
    }

    std::vector<unsigned short> indices;

    int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if (i != (stackCount - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    /*for (int i = 0; i < vertices.size(); i++)
        std::cout << vertices[i][0] << ' ' << vertices[i][1] << ' ' << vertices[i][2] << '\n';

    std::cout << '\n\n';

    for (int i = 0; i < normals.size(); i++)
        std::cout << normals[i][0] << ' ' << normals[i][1] << ' ' << normals[i][2] << '\n';

    std::cout << '\n\n';

    for (int i = 0; i < textureCoords.size(); i++)
        std::cout << textureCoords[i][0] << ' ' << textureCoords[i][1] << '\n';

    std::cout << '\n\n';

    for (int i = 0; i < indices.size(); i = i + 3)
        std::cout << indices[i] << ' ' << indices[i + 1] << ' ' << indices[i + 2] << '\n';
        */
    Mesh* mesh = new Mesh(name);
    mesh->InitFromData(vertices, normals, textureCoords, indices);
    return mesh;


}