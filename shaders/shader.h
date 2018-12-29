#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Define the shader class
class Shader {

    public:

    // Store the ID of the shader program
    GLuint program;

    Shader() {
        //Do nothing
    }

    // Constructor
    Shader(const GLchar* vPath, const GLchar* fPath) {

        std::string vCode;
        std::string fCode;
        std::ifstream vFile;
        std::ifstream fFile;

        // Set the ifstreams to throw exceptions
        vFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        // Create the string streams
        std::stringstream vShaderStream, fShaderStream;

        try {

            // Open the files
            vFile.open(vPath);
            fFile.open(fPath);

            // Read the buffer as a stream
            vShaderStream << vFile.rdbuf();
            fShaderStream << fFile.rdbuf();

            // Close the files
            vFile.close();
            fFile.close();

            // Read as strings
            vCode = vShaderStream.str();
            fCode = fShaderStream.str();

        }
        catch (std::ifstream::failure e) {
            fprintf(stderr, "Error generating shaders: %s", e.what());
        }

        // Set the shaders
        const char *vertexData = vCode.c_str();
        const char *fragData = fCode.c_str();

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

        // Clean up shaders
        glDeleteShader(vs);
        glDeleteShader(fs);

    }

    // Method to set as active shader
    void use() {
        glUseProgram(program);
    }

    // Utility methods to set uniform attributes
    void setBool(const std::string &name, bool value) const {         
        glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value); 
    }
    void setInt(const std::string &name, int value) const { 
        glUniform1i(glGetUniformLocation(program, name.c_str()), value); 
    }
    void setFloat(const std::string &name, float value) const { 
        glUniform1f(glGetUniformLocation(program, name.c_str()), value); 
    } 

};
#endif