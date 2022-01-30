#include<glad/glad.h>
#include "utils/Macros.h"
class Texture {
public:
	Texture();
	Texture(GLenum _texType, GLenum _filteringMode);
	void Initialize(unsigned char* img);
	unsigned int getTexture() { 
		return buffer;
	}
private:
	GLenum texType{ GL_TEXTURE_2D };
	GLenum filteringMode{ GL_LINEAR };
	unsigned int buffer{0};

};