#pragma once

#include <string>
#include <glad/glad.h>

class Shader {
public:
    unsigned int ID{0};

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    // Empêche la copie pour respecter le cycle de vie RAII
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void use() const;

private:
    std::string readFile(const std::string& path);
    unsigned int compile(unsigned int type, const std::string& source);
};