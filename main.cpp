#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders/shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

// Variable to hold the program
GLuint program;

// Variable to hold the buffer and array objects for the vertices
GLuint VBO;
GLuint VAO;
GLuint EBO;

float vertices[] = {
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
};
unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

float texCoords[] = {
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.5f, 1.0f
};

// Set the background colour
static const GLfloat bg[] = {0.2f, 0.3f, 0.3f, 1.0f};

// Function to handle GLFW error callbacks
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
        fprintf(stderr, "Error loading GLFW...\n");
        return 1;
    }

    // Set the error callback handler
    glfwSetErrorCallback(error_callback);

    // Use open GL 3.3 core min
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Set forward compatability
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Set the core profile to use newest version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Disable resizing
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create a window and a GL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vehicle Game", NULL, NULL);

    // Check if the window failed to instantiate
    if(!window) {
        fprintf(stderr, "Failed to create GLFW window...\n");
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

    // Load the shaders
    Shader s("shaders/vertex.glsl", "shaders/fragment.glsl");

    // Load the container texture data
    int width, height, nrChannels;
    unsigned char* texData = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);

    // Check that the image data loaded successfully
    if (texData) {

        // Create the texture object
        GLuint containerTex;
        glGenTextures(1, &containerTex);

        // Use the shader
        s.use();

        // Bind container tex as the currently active texture
        glBindTexture(GL_TEXTURE_2D, containerTex);

        // Generate the texture and mipmap
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Free the image data
        stbi_image_free(texData);

    }
    else {
        fprintf(stderr, "Failed to load texture...");
    }

    // Create a VAO to hold information about the render object for the VBO data
    glGenVertexArrays(1, &VAO);

    // Create an element buffer
    glGenBuffers(1, &EBO);

    // Bind to the vertex array
    glBindVertexArray(VAO);

    // Create the vertex buffer object and bind this as the active GL buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Buffer the vertex information in the vertex buffer object
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create the Element Buffer object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Setup the step data for the VBO to access x,y,z of each vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup the step data for the VBO to access tex coords of each vertex
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Create the model matrix
    glm::mat4 modelMatrix;
    modelMatrix = glm::rotate(modelMatrix, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // Create the view matrix
    glm::mat4 viewMatrix;
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

    // Create the projection matrix to use a perspective camera
    glm::mat4 projectionMatrix;
    projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800/600, 0.1f, 100.0f);

    // Create the pointers to the uniform floats in the vertex shader
    GLuint modelLoc = glGetUniformLocation(s.program, "model");
    GLuint viewLoc = glGetUniformLocation(s.program, "view");
    GLuint projectionLoc = glGetUniformLocation(s.program, "projection");

    // Create the game loop to run until the window close button or esc is clicked
    while(!glfwWindowShouldClose(window)) {

        // Pass the data for the model, view and projection matrix to the shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        // Clear to background colour
        glClearBufferfv(GL_COLOR, 0, bg);

        // Draw the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap the buffer to render
        glfwSwapBuffers(window);

        // Use vSync to limit the number of times the buffers are swapped
        glfwSwapInterval(1);

        // Poll key press events
        glfwPollEvents();

    }

    // Destroy vertex objects
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Destroy the program
    glDeleteProgram(program);

    // Terminate GLFW window
    glfwDestroyWindow(window);

    // Terminate GLFW
    glfwTerminate();

    fprintf(stdout, "Program terminated successfully...\n");
    return 0;

}