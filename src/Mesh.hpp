#pragma once

#include <vector>
#include <glad/glad.h>

class Mesh {
public:
    Mesh(const std::vector<float>& vertices);
    ~Mesh();

    // RAII : copie interdite pour éviter les suppressions GPU dupliquées
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    void draw() const;

private:
    unsigned int VAO{0};
    unsigned int VBO{0};
    GLsizei vertexCount{0};
};