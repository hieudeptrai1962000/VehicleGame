#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Variable to hold the program and vertex array object
GLuint program;

// Set the background colour
static const GLfloat bg[] = {0.3f, 0.1f, 0.0f, 1.0f};

// Method to handle GLFW error callbacks
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

// Create a key callback to handle key press events
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    // Check for escape key press
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

}

int main(int argc, const char * argv[]) {
    
    // Check whether GLFW initialises successfully
    if(!glfwInit()) {
        fprintf(stderr, "Error loading GLFW...");
        return 1;
    }

    // Set the error callback handler
    glfwSetErrorCallback(error_callback);

    // Use open GL 4.1 core min
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    // Set forward compatability
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Set the core profile to use newest version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Disable resizing
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create a window and a GL context
    GLFWwindow* window = glfwCreateWindow(800, 6000, "Vehicle Game", NULL, NULL);

    // Check if the window failed to instantiate
    if(!window) {
        fprintf(stderr, "Failed to create GLFW window...");
        glfwTerminate();
        return 1;
    }

    // Set the GL context to handle the window
    glfwMakeContextCurrent(window);

    // Set the key press callback function
    glfwSetKeyCallback(window, key_callback);

    // Initialise GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Create the game loop to run until the window close button is clicked
    while(!glfwWindowShouldClose(window)) {

        // Clear to background colour
        glClearBufferfv(GL_COLOR, 0, bg);

        // Swap the buffer to render
        glfwSwapBuffers(window);

        // Use vSync to limit the number of times the buffers are swapped
        glfwSwapInterval(1);

        // Poll key press events
        glfwPollEvents();

    }

    // Destroy the program
    glDeleteProgram(program);

    // Terminate GLFW window
    glfwDestroyWindow(window);

    // Terminate GLFW
    glfwTerminate();

    fprintf(stdout, "Successfully loaded GLFW...");
    return 0;

}