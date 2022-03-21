#include "Texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Texture::Texture(bool isFlip, bool isRGBA) {
	//TODO: init with sth
	_isFlip = isFlip;
	_isRGBA = isRGBA;
}
Texture::Texture(GLenum _texType, GLenum _filteringMode, bool isFlip, bool isRGBA){
    texType = _texType;
    filteringMode = _filteringMode;
	_isFlip = isFlip;
	_isRGBA = isRGBA;
}
void Texture::Initialize(const char *path){
    glGenTextures(1, &buffer);
    glBindTexture(texType, buffer);

    // set the texture wrapping parameters
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // set texture filtering parameters
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	int width, height, nrChannels;
    // load image, create texture and generate mipmaps
	if (_isFlip) {
		stbi_set_flip_vertically_on_load(true);
	}
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(texType, 0, GL_RGB, width, height, 0, _isRGBA? GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(texType);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
	stbi_image_free(data);
}