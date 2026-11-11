#pragma once

#include <glm/glm.hpp>

// Donnée CPU pure : aucun en-tête OpenGL ici, pour que le loader et les tests restent sans GL
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;

    bool operator==(const Vertex&) const = default;
};
