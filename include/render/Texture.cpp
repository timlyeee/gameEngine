#include "Texture.h"
#include <iostream>
Texture::Texture() {
	//TODO: init with sth
}
Texture::Texture(GLenum _texType, GLenum _filteringMode){
    texType = _texType;
    filteringMode = _filteringMode;
}
void Texture::Initialize(unsigned char* img){
    glGenTextures(1, &buffer);
    glBindTexture(texType, buffer);

    // set the texture wrapping parameters
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // set texture filtering parameters
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    
    if (img) {
        glTexImage2D(texType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        glGenerateMipmap(texType);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
}