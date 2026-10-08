#include "Mesh.hpp"

Mesh::Mesh(const std::vector<float>& vertices) {
    // 3 coordonnées (x, y, z) par sommet
    vertexCount = static_cast<GLsizei>(vertices.size() / 3);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Configuration de l'attribut 0 (position)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
    }
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
    }
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}