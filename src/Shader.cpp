#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Erreur: impossible d'ouvrir le fichier " << path << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::compile(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Erreur compilation shader:\n" << infoLog << std::endl;
    }
    return shader;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vCode = readFile(vertexPath);
    std::string fCode = readFile(fragmentPath);

    unsigned int vertex = compile(GL_VERTEX_SHADER, vCode);
    unsigned int fragment = compile(GL_FRAGMENT_SHADER, fCode);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    int success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(ID, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Erreur linkage programme shader:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    if (ID != 0) {
        glDeleteProgram(ID);
    }
}

int Shader::getUniformLocation(const std::string& name) const {
    auto it = uniformLocationCache.find(name);
    if (it != uniformLocationCache.end()) {
        return it->second;
    }
    int location = glGetUniformLocation(ID, name.c_str());
    uniformLocationCache[name] = location;
    return location;
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(getUniformLocation(name), value);
}