#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.hpp"

int main() {
    if (!glfwInit()) {
        std::cerr << "Erreur : initialisation GLFW impossible" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Renderer - C++20", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur : creation fenetre impossible" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Erreur : initialisation GLAD impossible" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);

    // Initialisation du Shader via les fichiers externes
    Shader basicShader("shaders/basic.vert", "shaders/basic.frag");

    // Données des sommets du triangle (coordonnées normalisées X, Y, Z)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bas gauche
         0.5f, -0.5f, 0.0f, // Bas droite
         0.0f,  0.5f, 0.0f  // Haut centre
    };

    // Configuration VBO (mémoire GPU) et VAO (description des attributs)
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Fond sombre
        glClearColor(0.1f, 0.12f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Dessin du triangle
        basicShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    // Nettoyage des buffers géométriques
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}