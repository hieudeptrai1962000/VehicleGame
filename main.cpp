#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include "shaders/shader.h"
#include "shaders/textures.h"
#include "vehicle.h"

using namespace std;

// Variable to hold the program
GLuint program;

// Variables to hold the buffer and array objects for the vertices
GLuint pVBO;
GLuint pVAO;
GLuint pEBO;

// Setup keys
const int K_UP = 0;
const int K_DOWN = 1;
const int K_LEFT = 2;
const int K_RIGHT = 3;
const int K_A = 4;
const int K_D = 5;
const int K_SPACE = 6;

// Store the camera type to render with
int cameraType;

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
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        cameraType++;
        if (cameraType > 2) {
            cameraType = 0;
        }
    }
    if (key == GLFW_KEY_C&& action == GLFW_RELEASE) {
        
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

// Method to draw the world plane
void drawPlane(Shader s, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {

    // Create the pointers to the uniform floats in the vertex shader
    const GLuint mvpLoc = glGetUniformLocation(s.program, "mvp");

    // Set the texture
    glUniform1i(glGetUniformLocation(s.program, "trackTex"), 0);

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

    // Enable vertical flipping of textures
    stbi_set_flip_vertically_on_load(true);

    // Load the shaders
    Shader s("shaders/vertex.glsl", "shaders/planeFragment.glsl");

    // Variables to hold the textures
    GLuint trackTex;

    // Generate the textures
    genTexture(trackTex, GL_TEXTURE0,  s, "assets/carRedWindows.jpg");

    // Generate the world plane
    planeMesh();

    // Create the vehicle
    Vehicle v(glm::vec3(-0.23f, -0.05f, 0.0f), 0.0f, 0.0f, 0.01f, 0.00005f);

    // Create the view matrix
    glm::mat4 viewMatrix;

    // Create the projection matrix to use a perspective camera
    glm::mat4 projectionMatrix;
    projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800/600, 0.1f, 100.0f);

    // Create the position matrix of the camera
    glm::vec3 cameraDistance =  glm::vec3(0.0f, -0.4f, 0.3f);

    // Create the position matrix of the camera
    glm::vec3 cameraPos = v.position + cameraDistance;

    // Define a vector that points up
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - v.position);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    // Set to the default camera
    cameraType = 0;

    // Create the game loop to run until the window close button or esc is clicked
    while(!glfwWindowShouldClose(window)) {

        // Check pressed keys
        if (keys[K_UP]) {
            
            // Check if we are at max speed
            if (!(v.speed >= v.maxSpeed)) {
                v.speed += v.acceleration;
            }
            else {
                v.speed = v.maxSpeed;
            }

        }
        else {
            v.speed -= v.acceleration;
            if(v.speed <= 0) {
                v.speed = 0;
            }
        }
        if(keys[K_DOWN]) {
            if(v.speed <= 0) {
                v.speed = -v.maxSpeed / 4;
            }
            else {
                v.speed -= 5 * v.acceleration;
            }
        }
        if(keys[K_LEFT]) {
            if (v.speed > 0) {
                v.rotation += 2.0f;
                if (keys[K_SPACE]) {
                    v.rotation += 3.0f;
                }
            }
            else if (v.speed < 0) {
                v.rotation -= 2.0f;
            }
        }
        if(keys[K_RIGHT]) {
            if (v.speed > 0) {
                v.rotation -= 2.0f;
                if (keys[K_SPACE]) {
                    v.rotation -= 3.0f;
                }
            }
            else if (v.speed < 0) {
                v.rotation += 2.0f;
            }
        }

        // Caculate the x and y component of the movement and move by speed
        v.position.x -= sin(glm::radians(v.rotation)) * v.speed;
        v.position.y += cos(glm::radians(v.rotation)) * v.speed;

        // Clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Clear to background colour
        glClearBufferfv(GL_COLOR, 0, bg);

        // Check the camera type
        if (cameraType == 0) {

            // Create the position matrix of the camera
            glm::vec3 cameraPos = v.position + cameraDistance;

            // Calculate the camera direction
            glm::vec3 cameraDirection = glm::normalize(cameraPos - v.position);
            glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

            // Create the view matrix
            viewMatrix = glm::lookAt(cameraPos, v.position, cameraUp);
        }
        else if (cameraType == 1) {

            // Create the position matrix of the camera
            glm::vec3 cameraPos = v.position + glm::vec3(sin(glm::radians(v.rotation)) * 0.4f, -cos(glm::radians(v.rotation)) * 0.4f, 0.3f);

            // Calculate the camera direction
            glm::vec3 cameraDirection = glm::normalize(cameraPos - v.position);
            glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

            // Create the view matrix
            viewMatrix = glm::lookAt(cameraPos, v.position, cameraUp);
            //viewMatrix = glm::rotate(viewMatrix, glm::radians(vRotation), -cameraDirection);
        }
        else if (cameraType == 2) {

            // Set the camera position
            glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.3f);

            // Calculate the camera direction
            glm::vec3 cameraDirection = glm::normalize(cameraPos - v.position);
            glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

            // Create the view matrix
            viewMatrix = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), cameraUp);

        }
        
        // Draw the plane
        drawPlane(s, projectionMatrix, viewMatrix);
        
        // Draw the cube
        v.draw(projectionMatrix, viewMatrix);

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

    // Destroy the program
    glDeleteProgram(program);

    // Terminate GLFW window
    glfwDestroyWindow(window);

    // Terminate GLFW
    glfwTerminate();

    fprintf(stdout, "Program terminated successfully...\n");
    return 0;

}