#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "Shader.hpp"
#include "Mesh.hpp"

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

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Erreur : initialisation GLAD impossible" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);

    // --- SCOPE DES RESSOURCES GPU ---
    {
        Shader basicShader("shaders/basic.vert", "shaders/basic.frag");

        std::vector<float> triangleVertices = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        Mesh triangleMesh(triangleVertices);

        // Boucle de rendu
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            glClearColor(0.1f, 0.12f, 0.18f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            basicShader.use();
            triangleMesh.draw();

            glfwSwapBuffers(window);
        }
    } 

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}