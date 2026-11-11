#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "ModelLoader.hpp"

namespace {

const std::string dataDir = PROJECT_ROOT_DIR "/tests/data/";

const Vertex* findByPosition(const std::vector<Vertex>& vertices, const glm::vec3& position) {
    for (const auto& v : vertices) {
        if (glm::length(v.Position - position) < 1e-6f) return &v;
    }
    return nullptr;
}

} // namespace

// Le cube versionné (modèle par défaut) : 8 positions x 3 normales de face = 24 sommets uniques
TEST(ModelLoaderTest, BundledCubeDeduplicatesToTwentyFourVertices) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    ASSERT_TRUE(ModelLoader::loadOBJ(PROJECT_ROOT_DIR "/assets/cube.obj", vertices, indices));

    EXPECT_EQ(indices.size(), 36u); // 12 triangles
    EXPECT_EQ(vertices.size(), 24u);
}

// Sans "vn" : le sommet partagé est dédupliqué et sa normale est pondérée par l'aire des faces
TEST(ModelLoaderTest, GeneratedNormalsAreAreaWeightedAndShared) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    ASSERT_TRUE(ModelLoader::loadOBJ(dataDir + "area_weighting.obj", vertices, indices));

    EXPECT_EQ(indices.size(), 6u);
    EXPECT_EQ(vertices.size(), 5u); // l'origine n'est stockée qu'une fois

    const Vertex* origin = findByPosition(vertices, glm::vec3(0.0f));
    ASSERT_NE(origin, nullptr);
    // Le grand triangle (+Z, aire 50) domine le petit (+Y, aire 0.5).
    // Avec une moyenne non pondérée, on obtiendrait (0, 0.707, 0.707).
    EXPECT_GT(origin->Normal.z, 0.99f);
}

// Régression : une face sans "vn" dans un fichier qui en contient lisait un vecteur vide (UB)
TEST(ModelLoaderTest, FaceWithoutNormalInMixedFileFallsBackToGeneratedNormal) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    ASSERT_TRUE(ModelLoader::loadOBJ(dataDir + "mixed_normals.obj", vertices, indices));

    EXPECT_EQ(indices.size(), 6u);
    EXPECT_EQ(vertices.size(), 6u); // normales différentes -> aucun sommet fusionné

    const Vertex* apex = findByPosition(vertices, glm::vec3(0.0f, 0.0f, 1.0f));
    ASSERT_NE(apex, nullptr);
    EXPECT_NEAR(apex->Normal.y, -1.0f, 1e-5f); // normale générée de la face (1, 2, 4)

    for (const auto& v : vertices) {
        EXPECT_NEAR(glm::length(v.Normal), 1.0f, 1e-5f);
    }
}
