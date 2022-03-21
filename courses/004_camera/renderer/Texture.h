#include <gl/glew.h>

class Texture {
public:
	Texture(bool isFlip, bool isRGBA);
	Texture(GLenum _texType, GLenum _filteringMode, bool isFlip, bool isRGBA);
	void Initialize(const char* path);
	unsigned int getTexture() { 
		return buffer;
	}
private:
	GLenum texType{ GL_TEXTURE_2D };
	GLenum filteringMode{ GL_LINEAR };
	unsigned int buffer{0};
	bool _isFlip{ false };
	bool _isRGBA{false};
};
