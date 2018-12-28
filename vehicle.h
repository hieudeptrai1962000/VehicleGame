#ifndef VEHICLE_H
#define VEHICLE_H

#include <gl/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Store the vertex array and buffer objects
GLuint cVBO;
GLuint cVAO;

float carVertices[] = {

    // BOTTOM OF CAR

    // TOP SIDE
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
     0.5f, -1.0f,  0.3f,  1.0f, 0.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 1.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 1.0f,
    -0.5f,  1.0f,  0.3f,  0.0f, 1.0f,
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,

    // LEFT SIDE
    -0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
    -0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
    -0.5f,  1.0f,  0.3f,  1.0f, 0.0f,

    // RIGHT SIDE
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
     0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,

    // BACK SIDE
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  1.0f, 1.0f,
     0.5f, -1.0f,  0.3f,  1.0f, 0.0f,
     0.5f, -1.0f,  0.3f,  1.0f, 0.0f,
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,

    // FRONT SIDE
    -0.5f,  1.0f, -0.5f,  0.0f, 1.0f,
     0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
    -0.5f,  1.0f,  0.3f,  0.0f, 0.0f,
    -0.5f,  1.0f, -0.5f,  0.0f, 1.0f,
    
    // TOP OF CAR

    -0.3f, -0.6f,  0.8f,  0.0f, 0.0f,
     0.3f, -0.6f,  0.8f,  1.0f, 0.0f,
     0.3f,  0.2f,  0.8f,  1.0f, 1.0f,
     0.3f,  0.2f,  0.8f,  1.0f, 1.0f,
    -0.3f,  0.2f,  0.8f,  0.0f, 1.0f,
    -0.3f, -0.6f,  0.8f,  0.0f, 0.0f,

    -0.3f,  0.2f,  0.8f,  1.0f, 0.0f,
    -0.3f,  0.6f,  0.3f,  1.0f, 1.0f,
    -0.3f, -0.6f,  0.3f,  0.0f, 1.0f,
    -0.3f, -0.6f,  0.3f,  0.0f, 1.0f,
    -0.3f, -0.6f,  0.8f,  0.0f, 0.0f,
    -0.3f,  0.2f,  0.8f,  1.0f, 0.0f,

     0.3f,  0.2f,  0.8f,  1.0f, 0.0f,
     0.3f,  0.6f,  0.3f,  1.0f, 1.0f,
     0.3f, -0.6f,  0.3f,  0.0f, 1.0f,
     0.3f, -0.6f,  0.3f,  0.0f, 1.0f,
     0.3f, -0.6f,  0.8f,  0.0f, 0.0f,
     0.3f,  0.2f,  0.8f,  1.0f, 0.0f,

    -0.3f, -0.6f,  0.3f,  0.0f, 1.0f,
     0.3f, -0.6f,  0.3f,  1.0f, 1.0f,
     0.3f, -0.6f,  0.8f,  1.0f, 0.0f,
     0.3f, -0.6f,  0.8f,  1.0f, 0.0f,
    -0.3f, -0.6f,  0.8f,  0.0f, 0.0f,
    -0.3f, -0.6f,  0.3f,  0.0f, 1.0f,

    -0.3f,  0.6f,  0.3f,  0.0f, 1.0f,
     0.3f,  0.6f,  0.3f,  1.0f, 1.0f,
     0.3f,  0.2f,  0.8f,  1.0f, 0.0f,
     0.3f,  0.2f,  0.8f,  1.0f, 0.0f,
    -0.3f,  0.2f,  0.8f,  0.0f, 0.0f,
    -0.3f,  0.6f,  0.3f,  0.0f, 1.0f
};

float truckVertices[] = {

    // BOTTOM OF TRUCK

    // TOP SIDE
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
     0.5f, -1.0f,  0.3f,  1.0f, 0.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 1.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 1.0f,
    -0.5f,  1.0f,  0.3f,  0.0f, 1.0f,
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,

    // LEFT SIDE
    -0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
    -0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
    -0.5f,  1.0f,  0.3f,  1.0f, 0.0f,

    // RIGHT SIDE
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
     0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,

    // BACK SIDE
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  1.0f, 1.0f,
     0.5f, -1.0f,  0.3f,  1.0f, 0.0f,
     0.5f, -1.0f,  0.3f,  1.0f, 0.0f,
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,

    // FRONT SIDE
    -0.5f,  1.0f, -0.5f,  0.0f, 1.0f,
     0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
    -0.5f,  1.0f,  0.3f,  0.0f, 0.0f,
    -0.5f,  1.0f, -0.5f,  0.0f, 1.0f,

    // TOP OF TRUCK

    // TOP SIDE
    -0.4f,  0.1f,  1.0f,  0.0f, 0.0f,
     0.4f,  0.1f,  1.0f,  1.0f, 0.0f,
     0.4f,  0.8f,  1.0f,  1.0f, 1.0f,
     0.4f,  0.8f,  1.0f,  1.0f, 1.0f,
    -0.4f,  0.8f,  1.0f,  0.0f, 1.0f,
    -0.4f,  0.1f,  1.0f,  0.0f, 0.0f,

    // LEFT SIDE
    -0.4f,  0.8f,  1.0f,  1.0f, 0.0f,
    -0.5f,  1.0f,  0.3f,  1.0f, 1.0f,
    -0.5f,  0.1f,  0.3f,  0.0f, 1.0f,
    -0.5f,  0.1f,  0.3f,  0.0f, 1.0f,
    -0.4f,  0.1f,  1.0f,  0.0f, 0.0f,
    -0.4f,  0.8f,  1.0f,  1.0f, 0.0f,

    // RIGHT SIDE
     0.4f,  0.8f,  1.0f,  1.0f, 0.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 1.0f,
     0.5f,  0.1f,  0.3f,  0.0f, 1.0f,
     0.5f,  0.1f,  0.3f,  0.0f, 1.0f,
     0.4f,  0.1f,  1.0f,  0.0f, 0.0f,
     0.4f,  0.8f,  1.0f,  1.0f, 0.0f,

    // BACK SIDE
    -0.5f,  0.1f,  0.3f,  0.0f, 1.0f,
     0.5f,  0.1f,  0.3f,  1.0f, 1.0f,
     0.4f,  0.1f,  1.0f,  1.0f, 0.0f,
     0.4f,  0.1f,  1.0f,  1.0f, 0.0f,
    -0.4f,  0.1f,  1.0f,  0.0f, 0.0f,
    -0.5f,  0.1f,  0.3f,  0.0f, 1.0f,

    // FRONT SIDE
    -0.5f,  1.0f,  0.3f,  0.0f, 1.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 1.0f,
     0.4f,  0.8f,  1.0f,  1.0f, 0.0f,
     0.4f,  0.8f,  1.0f,  1.0f, 0.0f,
    -0.4f,  0.8f,  1.0f,  0.0f, 0.0f,
    -0.5f,  1.0f,  0.3f,  0.0f, 1.0f
};

// Define the class to hold a vehicle
class Vehicle {

    public:

    // Store the position of the vehicle
    glm::vec3 position;

    // Store the rotation, speed, max speed and acceleration
    float rotation;
    float speed;
    float maxSpeed;
    float acceleration;

    // Constructor
    Vehicle(glm::vec3 pos, float r, float s, float ms, float a) {

        // Set the fields
        position = pos;
        rotation = r;
        speed = s;
        maxSpeed = ms;
        acceleration = a;

        // Create the vehicle mesh
        mesh();

    }

    // Method to create a vehicle mesh object
    void mesh() {

        // Create a VAO to hold information about the render object for the VBO data
        glGenVertexArrays(1, &cVAO);

        // Bind to the vertex array
        glBindVertexArray(cVAO);

        // Create the vertex buffer object and bind this as the active GL buffer
        glGenBuffers(1, &cVBO);
        glBindBuffer(GL_ARRAY_BUFFER, cVBO);

        // Buffer the vertex information in the vertex buffer object
        glBufferData(GL_ARRAY_BUFFER, sizeof(carVertices), carVertices, GL_STATIC_DRAW);

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

    // Create a method to draw the cube
    void draw(Shader s, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {

        // Create the pointers to the uniform floats in the vertex shader
        const GLuint mvpLoc = glGetUniformLocation(s.program, "mvp");

        // Use the shader program
        s.use();

        // Recalculate the model matrix
        glm::mat4 modelMatrix;
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02f, 0.02f, 0.02f));
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
        glDrawArrays(GL_TRIANGLES, 0, 60);

        // Debind the buffer
        glBindVertexArray(0);

    }

};

#endif