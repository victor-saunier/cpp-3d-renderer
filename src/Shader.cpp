#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier shader : " + path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::compile(unsigned int type, const std::string& source, const std::string& path) {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // Pas d'exception ici : l'édition de liens échouera forcément ensuite,
        // et le constructeur gère alors le nettoyage en un seul endroit.
        char infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Erreur compilation shader (" << path << ") :\n" << infoLog << std::endl;
    }
    return shader;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    // Lecture des deux fichiers AVANT toute allocation GL : si l'une échoue, rien à libérer
    std::string vCode = readFile(vertexPath);
    std::string fCode = readFile(fragmentPath);

    unsigned int vertex = compile(GL_VERTEX_SHADER, vCode, vertexPath);
    unsigned int fragment = compile(GL_FRAGMENT_SHADER, fCode, fragmentPath);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // Marqués pour suppression : libérés quand le programme qui les référence le sera
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    int success = 0;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(ID, sizeof(infoLog), nullptr, infoLog);
        // Un constructeur qui lève une exception n'appelle jamais le destructeur : on libère ici
        glDeleteProgram(ID);
        throw std::runtime_error(std::string("Echec de l'edition de liens du programme shader :\n") + infoLog);
    }
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