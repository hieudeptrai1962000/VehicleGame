#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// Variable to hold the program
GLuint program;

// Variable to hold the buffer and array objects for the vertices
GLuint VBO;
GLuint VAO;

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
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

// Load shader and return string
string loadFile(string fName) {

    // Create an input file stream to load shaders
    std::ifstream inFile;

    // Open the file
    inFile.open(fName, ios::in);

    // Check if the file failed to load
    if(!inFile) {
        fprintf(stderr, "%s not found...\n", fName.c_str());
        exit(1);
    }

    // Buffer the string as a string stream
    std::stringstream buffer;
    buffer << inFile.rdbuf();

    // Return the string
    return buffer.str()+"\0";

}

int main(int argc, const char * argv[]) {
    
    // Check whether GLFW initialises successfully
    if(!glfwInit()) {
        fprintf(stderr, "Error loading GLFW...\n");
        return 1;
    }

    // Set the error callback handler
    glfwSetErrorCallback(error_callback);

    // Use open GL 4.1 core min
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

    // Set the viewport width and height
    glViewport(0, 0, 800, 600);

    // Load the vertex shader from file
    const char *vertexData = loadFile("shaders/vertex.glsl").c_str();

    // Create the shaders
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    // Set the source and destination of object for the shader then compile
    glShaderSource(vs, 1, &vertexData, NULL);
    glCompileShader(vs);

    // Check for compile errors
    int success;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

    // If there is an error, log
    if(!success) {
        char error[512];
        glGetShaderInfoLog(vs, 512, NULL, error);
        fprintf(stderr, "Error compiling vertex shader: \n%s\nUsing default shader...\n", error);
    }

    // Load the frag shader from file
    const char *fragData = loadFile("shaders/fragment.glsl").c_str();

    // Set the source and destination of object for the shader then compile
    glShaderSource(fs, 1, &fragData, NULL);
    glCompileShader(fs);

    // Check for compile errors
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

    // If there is an error, log
    if(!success) {
        char error[512];
        glGetShaderInfoLog(fs, 512, NULL, error);
        fprintf(stderr, "Error compiling fragment shader: \n%s\nUsing default shader...\n", error);
    }

    // Create the program to handle the shaders
    GLuint program;
    program = glCreateProgram();

    // Attach the shaders
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    // Link the program
    glLinkProgram(program);

    // Check for success of linking
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    // If there is an error, log
    if(!success) {
        char error[512];
        glGetProgramInfoLog(program, 512, NULL, error);
        fprintf(stderr, "Error linking shader program: \n%s", error);
    }

    // Set open GL to use the shaders
    glUseProgram(program);

    // Create a VAO to hold information about the render object for the VBO data
    glGenVertexArrays(1, &VAO);

    // Bind to the vertex array
    glBindVertexArray(VAO);

    // Create the vertex buffer object and bind this as the active GL buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Buffer the vertex information in the vertex buffer object
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Setup the step data for the VBO to access x,y,z of each vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Create the game loop to run until the window close button or esc is clicked
    while(!glfwWindowShouldClose(window)) {

        // Clear to background colour
        glClearBufferfv(GL_COLOR, 0, bg);

        // Select the shader configuration
        glUseProgram(program);

        // Bind to the VAO
        glBindVertexArray(VAO);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the buffer to render
        glfwSwapBuffers(window);

        // Use vSync to limit the number of times the buffers are swapped
        glfwSwapInterval(1);

        // Poll key press events
        glfwPollEvents();

    }

    // Destroy the shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

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