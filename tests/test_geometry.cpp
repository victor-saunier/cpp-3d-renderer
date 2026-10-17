#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include "../src/GeometryMath.hpp"

// Test 1 : Vérifie qu'un triangle dans le plan XY génère une normale pointant vers +Z
TEST(GeometryMathTest, NormalPointsInPositiveZForCounterClockwiseTriangle) {
    glm::vec3 v0(0.0f, 0.0f, 0.0f);
    glm::vec3 v1(1.0f, 0.0f, 0.0f);
    glm::vec3 v2(0.0f, 1.0f, 0.0f);

    glm::vec3 normal = GeometryMath::computeTriangleNormal(v0, v1, v2);

    EXPECT_NEAR(normal.x, 0.0f, 1e-5f);
    EXPECT_NEAR(normal.y, 0.0f, 1e-5f);
    EXPECT_NEAR(normal.z, 1.0f, 1e-5f);
}

// Test 2 : Vérifie qu'un triangle dégénéré (points colinéaires) retourne le fallback propre
TEST(GeometryMathTest, DegenerateTriangleReturnsDefaultNormal) {
    glm::vec3 v0(0.0f, 0.0f, 0.0f);
    glm::vec3 v1(1.0f, 1.0f, 1.0f);
    glm::vec3 v2(2.0f, 2.0f, 2.0f); // Alignés -> produit vectoriel nul

    glm::vec3 normal = GeometryMath::computeTriangleNormal(v0, v1, v2);

    EXPECT_FLOAT_EQ(normal.x, 0.0f);
    EXPECT_FLOAT_EQ(normal.y, 1.0f);
    EXPECT_FLOAT_EQ(normal.z, 0.0f);
}