#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // 1. Initialiser GLFW
    if (!glfwInit()) {
        std::cerr << "Erreur : impossible d'initialiser GLFW" << std::endl;
        return -1;
    }

    // 2. Créer une fenêtre de 800x600
    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Renderer - C++20", nullptr, nullptr);
    if (!window) {
        std::cerr << "Erreur : impossible de creer la fenetre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 3. Définir le contexte graphique sur cette fenêtre
    glfwMakeContextCurrent(window);

    std::cout << "Fenetre ouverte avec succes !" << std::endl;

    // 4. Boucle principale de rendu
    while (!glfwWindowShouldClose(window)) {
        // Traiter les événements (clics, clavier, fermeture)
        glfwPollEvents();

        // Échanger les buffers d'affichage (double buffering)
        glfwSwapBuffers(window);
    }

    // 5. Nettoyer les ressources
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}