#pragma once

#include <string>
#include <vector>
#include "Vertex.hpp"

namespace ModelLoader {
bool loadOBJ(const std::string& filepath, std::vector<Vertex>& outVertices, std::vector<unsigned int>& outIndices);
}