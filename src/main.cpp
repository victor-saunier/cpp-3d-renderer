#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) {
        std::cerr << "Erreur : initialisation GLFW impossible" << std::endl;
        return -1;
    }

    // Configuration OpenGL 3.3 Core
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

    std::cout << "Pilote OpenGL actif : " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version OpenGL : " << glGetString(GL_VERSION) << std::endl;

    // Définir la zone d'affichage aux dimensions de la fenêtre
    glViewport(0, 0, 800, 600);

    // Boucle de rendu
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Couleur test : Rouge vif (R=1.0, G=0.2, B=0.2)
        glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}