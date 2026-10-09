#include "ModelLoader.hpp"
#include <iostream>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace ModelLoader {

bool loadOBJ(const std::string& filepath, std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str());

    if (!warn.empty()) {
        std::cout << "[TinyObjLoader Warning] : " << warn << std::endl;
    }
    if (!err.empty()) {
        std::cerr << "[TinyObjLoader Error] : " << err << std::endl;
    }
    if (!ret) {
        std::cerr << "Erreur: impossible de charger le fichier " << filepath << std::endl;
        return false;
    }

    outVertices.clear();
    outIndices.clear();

    const bool hasFileNormals = !attrib.normals.empty();
    std::vector<glm::vec3> generatedNormals;

    // Si le fichier .obj ne fournit aucune normale, on les calcule mathématiquement
    if (!hasFileNormals) {
        generatedNormals.assign(attrib.vertices.size() / 3, glm::vec3(0.0f));

        for (const auto& shape : shapes) {
            size_t indexOffset = 0;
            for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f) {
                const auto fv = shape.mesh.num_face_vertices[f];
                if (fv == 3) {
                    int i0 = shape.mesh.indices[indexOffset + 0].vertex_index;
                    int i1 = shape.mesh.indices[indexOffset + 1].vertex_index;
                    int i2 = shape.mesh.indices[indexOffset + 2].vertex_index;

                    glm::vec3 v0(attrib.vertices[3 * i0 + 0], attrib.vertices[3 * i0 + 1], attrib.vertices[3 * i0 + 2]);
                    glm::vec3 v1(attrib.vertices[3 * i1 + 0], attrib.vertices[3 * i1 + 1], attrib.vertices[3 * i1 + 2]);
                    glm::vec3 v2(attrib.vertices[3 * i2 + 0], attrib.vertices[3 * i2 + 1], attrib.vertices[3 * i2 + 2]);

                    glm::vec3 faceNormal = glm::cross(v1 - v0, v2 - v0);

                    generatedNormals[i0] += faceNormal;
                    generatedNormals[i1] += faceNormal;
                    generatedNormals[i2] += faceNormal;
                }
                indexOffset += fv;
            }
        }

        // Normalisation des vecteurs accumulés
        for (auto& n : generatedNormals) {
            if (glm::length(n) > 1e-6f) {
                n = glm::normalize(n);
            } else {
                n = glm::vec3(0.0f, 1.0f, 0.0f);
            }
        }
    }

    // Construction du buffer de sommets indexé
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.Position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            if (hasFileNormals && index.normal_index >= 0) {
                vertex.Normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
            } else {
                vertex.Normal = generatedNormals[index.vertex_index];
            }

            outIndices.push_back(static_cast<unsigned int>(outVertices.size()));
            outVertices.push_back(vertex);
        }
    }

    std::cout << "Modele " << filepath << " charge : " 
              << outVertices.size() << " sommets traites." << std::endl;
    return true;
}

} // namespace ModelLoader