#ifndef VEHICLE_H
#define VEHICLE_H

#include <gl/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders/shader.h"
#include "shaders/textures.h"

// Store the vertex array and buffer objects
GLuint cVBO[4];
GLuint cVAO[4];

// Store the shaders
Shader shaders[4];

float carVerticesTop[] = {

    // BOTTOM TOP SIDE
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
     0.5f, -1.0f,  0.3f,  1.0f, 0.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 1.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 1.0f,
    -0.5f,  1.0f,  0.3f,  0.0f, 1.0f,
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,

    // TOP TOP SIDE
    -0.3f, -0.6f,  0.8f,  0.0f, 0.0f,
     0.3f, -0.6f,  0.8f,  1.0f, 0.0f,
     0.3f,  0.2f,  0.8f,  1.0f, 1.0f,
     0.3f,  0.2f,  0.8f,  1.0f, 1.0f,
    -0.3f,  0.2f,  0.8f,  0.0f, 1.0f,
    -0.3f, -0.6f,  0.8f,  0.0f, 0.0f,

};

float carVerticesDoors[] = {

    // BOTTOM LEFT SIDE
    -0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
    -0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
    -0.5f,  1.0f,  0.3f,  1.0f, 0.0f,

    // BOTTOM RIGHT SIDE
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
     0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f

};

float carVerticesNumPlates[] = {

    // BOTTOM BACK SIDE
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,
     0.5f, -1.0f, -0.5f,  1.0f, 1.0f,
     0.5f, -1.0f,  0.3f,  1.0f, 0.0f,
     0.5f, -1.0f,  0.3f,  1.0f, 0.0f,
    -0.5f, -1.0f,  0.3f,  0.0f, 0.0f,
    -0.5f, -1.0f, -0.5f,  0.0f, 1.0f,

    // BOTTOM FRONT SIDE
    -0.5f,  1.0f, -0.5f,  0.0f, 1.0f,
     0.5f,  1.0f, -0.5f,  1.0f, 1.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
     0.5f,  1.0f,  0.3f,  1.0f, 0.0f,
    -0.5f,  1.0f,  0.3f,  0.0f, 0.0f,
    -0.5f,  1.0f, -0.5f,  0.0f, 1.0f
};

float carVerticesWindows[] = {

    // LEFT SIDE
    -0.3f,  0.2f,  0.8f,  1.0f, 0.0f,
    -0.3f,  0.6f,  0.3f,  1.0f, 1.0f,
    -0.3f, -0.6f,  0.3f,  0.0f, 1.0f,
    -0.3f, -0.6f,  0.3f,  0.0f, 1.0f,
    -0.3f, -0.6f,  0.8f,  0.0f, 0.0f,
    -0.3f,  0.2f,  0.8f,  1.0f, 0.0f,

    // RIGHT SIDE
     0.3f,  0.2f,  0.8f,  1.0f, 0.0f,
     0.3f,  0.6f,  0.3f,  1.0f, 1.0f,
     0.3f, -0.6f,  0.3f,  0.0f, 1.0f,
     0.3f, -0.6f,  0.3f,  0.0f, 1.0f,
     0.3f, -0.6f,  0.8f,  0.0f, 0.0f,
     0.3f,  0.2f,  0.8f,  1.0f, 0.0f,

    // BACK SIDE
    -0.3f, -0.6f,  0.3f,  0.0f, 1.0f,
     0.3f, -0.6f,  0.3f,  1.0f, 1.0f,
     0.3f, -0.6f,  0.8f,  1.0f, 0.0f,
     0.3f, -0.6f,  0.8f,  1.0f, 0.0f,
    -0.3f, -0.6f,  0.8f,  0.0f, 0.0f,
    -0.3f, -0.6f,  0.3f,  0.0f, 1.0f,

    // FRONT SIDE
    -0.3f,  0.6f,  0.3f,  0.0f, 1.0f,
     0.3f,  0.6f,  0.3f,  1.0f, 1.0f,
     0.3f,  0.2f,  0.8f,  1.0f, 0.0f,
     0.3f,  0.2f,  0.8f,  1.0f, 0.0f,
    -0.3f,  0.2f,  0.8f,  0.0f, 0.0f,
    -0.3f,  0.6f,  0.3f,  0.0f, 1.0f
};

float *carVertices[4] = {
    carVerticesTop,
    carVerticesDoors,
    carVerticesNumPlates,
    carVerticesWindows
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
    
        // Create the shaders
        for (int i = 0; i < 4; i++) {
            shaders[i] = Shader("shaders/vertex.glsl", "shaders/carFragment.glsl");
        }

        // Create the textures and bind
        GLuint carTex;
        GLuint carTexDoors;
        GLuint carTexNumPLates;
        GLuint carTexWindows;
        genTexture(carTex, GL_TEXTURE1,  shaders[0], "assets/track.jpg");
        genTexture(carTexDoors, GL_TEXTURE2,  shaders[1], "assets/carRed.jpg");
        genTexture(carTexNumPLates, GL_TEXTURE3,  shaders[2], "assets/carRedDoors.jpg");
        genTexture(carTexWindows, GL_TEXTURE4,  shaders[3], "assets/carRedNumPlates.jpg");

    }

    // Method to create a vehicle mesh object
    void mesh() {

        // ROOFS

        // Create a VAO to hold information about the render object for the VBO data
        glGenVertexArrays(1, &cVAO[0]);

        // Bind to the vertex array
        glBindVertexArray(cVAO[0]);

        // Create the vertex buffer object and bind this as the active GL buffer
        glGenBuffers(1, &cVBO[0]);
        glBindBuffer(GL_ARRAY_BUFFER, cVBO[0]);

        // Buffer the vertex information in the vertex buffer object
        glBufferData(GL_ARRAY_BUFFER, sizeof(carVerticesTop), carVerticesTop, GL_STATIC_DRAW);

        // Setup the step data for the VBO to access x,y,z of each vertex
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Setup the step data for the VBO to access tex coords of each vertex
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        // Debind the buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // DOORS

        // Create a VAO to hold information about the render object for the VBO data
        glGenVertexArrays(1, &cVAO[1]);

        // Bind to the vertex array
        glBindVertexArray(cVAO[1]);

        // Create the vertex buffer object and bind this as the active GL buffer
        glGenBuffers(1, &cVBO[1]);
        glBindBuffer(GL_ARRAY_BUFFER, cVBO[1]);

        // Buffer the vertex information in the vertex buffer object
        glBufferData(GL_ARRAY_BUFFER, sizeof(carVerticesDoors), carVerticesDoors, GL_STATIC_DRAW);

        // Setup the step data for the VBO to access x,y,z of each vertex
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Setup the step data for the VBO to access tex coords of each vertex
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        // Debind the buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // NUMBER PLATES

        // Create a VAO to hold information about the render object for the VBO data
        glGenVertexArrays(1, &cVAO[2]);

        // Bind to the vertex array
        glBindVertexArray(cVAO[2]);

        // Create the vertex buffer object and bind this as the active GL buffer
        glGenBuffers(1, &cVBO[2]);
        glBindBuffer(GL_ARRAY_BUFFER, cVBO[2]);

        // Buffer the vertex information in the vertex buffer object
        glBufferData(GL_ARRAY_BUFFER, sizeof(carVerticesNumPlates), carVerticesNumPlates, GL_STATIC_DRAW);

        // Setup the step data for the VBO to access x,y,z of each vertex
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Setup the step data for the VBO to access tex coords of each vertex
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        // Debind the buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // WINDOWS

        // Create a VAO to hold information about the render object for the VBO data
        glGenVertexArrays(1, &cVAO[3]);

        // Bind to the vertex array
        glBindVertexArray(cVAO[3]);

        // Create the vertex buffer object and bind this as the active GL buffer
        glGenBuffers(1, &cVBO[3]);
        glBindBuffer(GL_ARRAY_BUFFER, cVBO[3]);

        // Buffer the vertex information in the vertex buffer object
        glBufferData(GL_ARRAY_BUFFER, sizeof(carVerticesWindows), carVerticesWindows, GL_STATIC_DRAW);

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
    void draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {

        // Render each section of the car
        for (int i = 0; i < 4; i++) {

            // Create the pointers to the uniform floats in the vertex shader
            const GLuint mvpLoc = glGetUniformLocation(shaders[i].program, "mvp");
            shaders[i].setInt("carTex", i+1);

            // Use the shader program
            shaders[i].use();

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
            glBindVertexArray(cVAO[i]);

            // Draw the triangle
            glDrawArrays(GL_TRIANGLES, 0, 24);

            // Debind the buffer
            glBindVertexArray(0);

        }

    }

};

#endif