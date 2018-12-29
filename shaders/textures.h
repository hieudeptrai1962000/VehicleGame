#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "shader.h"

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

#endif