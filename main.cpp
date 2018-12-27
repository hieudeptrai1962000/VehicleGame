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

// Variables to hold the buffer and array objects for the vertices
GLuint pVBO;
GLuint pVAO;
GLuint pEBO;
GLuint cVBO;
GLuint cVAO;

// Setup keys
const int K_UP = 0;
const int K_DOWN = 1;
const int K_LEFT = 2;
const int K_RIGHT = 3;
const int K_A = 4;
const int K_D = 5;
const int K_SPACE = 6;

float planeVertices[] = {
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

float cubeVertices[] = {
    -0.5f, -1.0f, -0.5f,  0.0f, 0.0f,
     0.5f, -1.0f, -0.5f,  1.0f, 0.0f,
     0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
     0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
    -0.5f,  1.0f, -0.5f,  0.0f, 1.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 0.0f,

    -0.5f, -1.0f,  0.5f,  0.0f, 0.0f,
     0.5f, -1.0f,  0.5f,  1.0f, 0.0f,
     0.5f,  1.0f,  0.5f,  1.0f, 1.0f,
     0.5f,  1.0f,  0.5f,  1.0f, 1.0f,
    -0.5f,  1.0f,  0.5f,  0.0f, 1.0f,
    -0.5f, -1.0f,  0.5f,  0.0f, 0.0f,

    -0.5f,  1.0f,  0.5f,  1.0f, 0.0f,
    -0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
    -0.5f, -1.0f,  0.5f,  0.0f, 0.0f,
    -0.5f,  1.0f,  0.5f,  1.0f, 0.0f,

     0.5f,  1.0f,  0.5f,  1.0f, 0.0f,
     0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f,  0.5f,  0.0f, 0.0f,
     0.5f,  1.0f,  0.5f,  1.0f, 0.0f,

    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  1.0f, 1.0f,
     0.5f, -1.0f,  0.5f,  1.0f, 0.0f,
     0.5f, -1.0f,  0.5f,  1.0f, 0.0f,
    -0.5f, -1.0f,  0.5f,  0.0f, 0.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,

    -0.5f,  1.0f, -0.5f,  0.0f, 1.0f,
     0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
     0.5f,  1.0f,  0.5f,  1.0f, 0.0f,
     0.5f,  1.0f,  0.5f,  1.0f, 0.0f,
    -0.5f,  1.0f,  0.5f,  0.0f, 0.0f,
    -0.5f,  1.0f, -0.5f,  0.0f, 1.0f
};

// Create an array of booleans to store key presses
bool keys[] = {
    false,
    false,
    false,
    false,
    false,
    false,
    false
};

// Set the camera speed
float vehicleSpeed = 0.0f;
float maxSpeed = 0.01f;
float acceleration = 0.00005f;

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

    // Check for arrow key press
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        keys[K_UP] = true;
    }
    if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
        keys[K_UP] = false;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        keys[K_DOWN] = true;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
        keys[K_DOWN] = false;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        keys[K_LEFT] = true;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
        keys[K_LEFT] = false;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        keys[K_RIGHT] = true;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
        keys[K_RIGHT] = false;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        keys[K_A] = true;
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
        keys[K_A] = false;
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        keys[K_D] = true;
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
        keys[K_D] = false;
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        keys[K_SPACE] = true;
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        keys[K_SPACE] = false;
    }

}

// Method to generate the world plane
void planeMesh() {

    // Create a VAO to hold information about the render object for the VBO data
    glGenVertexArrays(1, &pVAO);

    // Create an element buffer
    glGenBuffers(1, &pEBO);

    // Bind to the vertex array
    glBindVertexArray(pVAO);

    // Create the vertex buffer object and bind this as the active GL buffer
    glGenBuffers(1, &pVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pVBO);

    // Buffer the vertex information in the vertex buffer object
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    // Create the Element Buffer object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Setup the step data for the VBO to access x,y,z of each vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup the step data for the VBO to access tex coords of each vertex
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Debind the buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

// Method to generate the cube
void cubeMesh() {

    // Create a VAO to hold information about the render object for the VBO data
    glGenVertexArrays(1, &cVAO);

    // Bind to the vertex array
    glBindVertexArray(cVAO);

    // Create the vertex buffer object and bind this as the active GL buffer
    glGenBuffers(1, &cVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cVBO);

    // Buffer the vertex information in the vertex buffer object
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // Setup the step data for the VBO to access x,y,z of each vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Setup the step data for the VBO to access tex coords of each vertex
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Debind the buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

// Method to generate and bind a texture
void genTexture(GLuint tex, GLenum texLoc, Shader s, const GLchar* sLocation) {

    // Load the texture data
    int width, height, nrChannels;
    unsigned char* texData = stbi_load(sLocation, &width, &height, &nrChannels, 0);

    // Check that the image data loaded successfully
    if (texData) {

        // Create the texture object
        glGenTextures(1, &tex);

        // Use the shader
        s.use();

        // Set the active texture
        glActiveTexture(texLoc);

        // Bind track tex as the currently active texture
        glBindTexture(GL_TEXTURE_2D, tex);

        // Generate the texture and mipmap
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Free the image data
        stbi_image_free(texData);

    }
    else {
        fprintf(stderr, "Failed to load texture...");
    }

}

// Method to draw the world plane
void drawPlane(Shader s, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {

        // Create the pointers to the uniform floats in the vertex shader
        const GLuint mvpLoc = glGetUniformLocation(s.program, "mvp");

        // Use the shader program
        s.use();

        // Recalculate the model matrix
        glm::mat4 modelMatrix;

        // Create the mvp matrix for the plane
        glm::mat4 mvp;
        mvp = projectionMatrix * viewMatrix * modelMatrix;

        // Pass the data for the model, view and projection matrix to the shader
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

        // Bind to the buffer to draw the plane
        glBindVertexArray(pVAO);

        // Draw the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Debind the buffer
        glBindVertexArray(0);

}

// Create a method to draw the cube
void drawVehicle(Shader s, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, float rotation, glm::vec3 position) {

        // Create the pointers to the uniform floats in the vertex shader
        const GLuint mvpLoc = glGetUniformLocation(s.program, "mvp");

        // Use the shader program
        s.use();

        // Recalculate the model matrix
        glm::mat4 modelMatrix;
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.03f, 0.03f, 0.03f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.5f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

        // Create the mvp matrix for the plane
        glm::mat4 mvp;
        mvp = projectionMatrix * viewMatrix * modelMatrix;

        // Pass the data for the model, view and projection matrix to the shader
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

        // Bind to the buffer to draw the plane
        glBindVertexArray(cVAO);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Debind the buffer
        glBindVertexArray(0);

}

int main(int argc, const char * argv[]) {
    
    // Check whether GLFW initialised successfully
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

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Load the shaders
    Shader ps("shaders/vertex.glsl", "shaders/planeFragment.glsl");
    Shader cs("shaders/vertex.glsl", "shaders/carFragment.glsl");

    // Variables to hold the textures
    GLuint trackTex;
    GLuint carTex;

    // Generate the textures
    genTexture(trackTex, GL_TEXTURE0,  ps, "assets/track.jpg");
    genTexture(trackTex, GL_TEXTURE1,  cs, "assets/car.jpg");

    // Set the textures in the shader program
    ps.setInt("trackTex", 0);
    cs.setInt("carTex", 1);

    // Generate the world plane
    planeMesh();

    // Generate the cube mesh
    cubeMesh();

    // Create the view matrix
    glm::mat4 viewMatrix;

    // Create the projection matrix to use a perspective camera
    glm::mat4 projectionMatrix;
    projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800/600, 0.1f, 100.0f);

    // Create the position of the vehicle
    glm::vec3 vehiclePos = glm::vec3(0.0f, 0.0f, 0.0f);

    // Create the position matrix of the camera
    glm::vec3 cameraDistance =  glm::vec3(0.0f, -0.4f, 0.3f);

    // Define a vector that points up
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    // Hold the rotation of the vehicle
    float vRotation = 0.0f;

    // Create the game loop to run until the window close button or esc is clicked
    while(!glfwWindowShouldClose(window)) {

        // Check pressed keys
        if (keys[K_UP]) {
            
            // Check if we are at max speed
            if (!(vehicleSpeed >= maxSpeed)) {
                vehicleSpeed += acceleration;
            }
            else {
                vehicleSpeed = maxSpeed;
            }

        }
        else {
            vehicleSpeed -= acceleration;
            if(vehicleSpeed <= 0) {
                vehicleSpeed = 0;
            }
        }
        if(keys[K_DOWN]) {
            if(vehicleSpeed <= 0) {
                vehicleSpeed = -maxSpeed / 4;
            }
            else {
                vehicleSpeed -= 5 * acceleration;
            }
        }
        if(keys[K_LEFT]) {
            if (vehicleSpeed != 0) {
                vRotation += 2.0f;
                if (keys[K_SPACE]) {
                    vRotation += 3.0f;
                }
            }
        }
        if(keys[K_RIGHT]) {
            if (vehicleSpeed != 0) {
                vRotation -= 2.0f;
                if (keys[K_SPACE]) {
                    vRotation -= 3.0f;
                }
            }
        }

        // Caculate the x and y component of the movement and move by speed
        vehiclePos.x -= sin(glm::radians(vRotation)) * vehicleSpeed;
        vehiclePos.y += cos(glm::radians(vRotation)) * vehicleSpeed;

        // Clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Clear to background colour
        glClearBufferfv(GL_COLOR, 0, bg);

        // Create the position matrix of the camera
        glm::vec3 cameraPos = vehiclePos + cameraDistance;

        // Calculate the camera direction
        glm::vec3 cameraDirection = glm::normalize(cameraPos - vehiclePos);
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

        // Create the view matrix
        viewMatrix = glm::lookAt(cameraPos, vehiclePos, cameraUp);
        
        // Draw the plane
        drawPlane(ps, projectionMatrix, viewMatrix);
        
        // Draw the cube
        drawVehicle(cs, projectionMatrix, viewMatrix, vRotation, vehiclePos);

        // Swap the buffer to render
        glfwSwapBuffers(window);

        // Use vSync to limit the number of times the buffers are swapped
        glfwSwapInterval(1);

        // Poll key press events
        glfwPollEvents();

    }

    // Destroy vertex objects
    glDeleteVertexArrays(1, &pVAO);
    glDeleteBuffers(1, &pVBO);
    glDeleteBuffers(1, &pEBO);
    glDeleteVertexArrays(1, &cVAO);
    glDeleteBuffers(1, &cVBO);

    // Destroy the program
    glDeleteProgram(program);

    // Terminate GLFW window
    glfwDestroyWindow(window);

    // Terminate GLFW
    glfwTerminate();

    fprintf(stdout, "Program terminated successfully...\n");
    return 0;

}