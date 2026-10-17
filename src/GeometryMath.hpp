#pragma once

#include <glm/glm.hpp>

namespace GeometryMath {

// Calcule la normale d'un triangle défini par 3 sommets (ordre direct / CCW)
inline glm::vec3 computeTriangleNormal(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) {
    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;
    glm::vec3 normal = glm::cross(edge1, edge2);
    
    float len = glm::length(normal);
    if (len < 1e-6f) {
        return glm::vec3(0.0f, 1.0f, 0.0f); // Normale par défaut
    }
    return normal / len;
}

}