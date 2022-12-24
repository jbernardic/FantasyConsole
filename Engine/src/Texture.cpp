#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "../../Dependencies/stb_image.h"
#include "ErrorHandler.h"
using namespace std;
Texture::Texture(const char* path)
	:_path(path)

{
	glGenTextures(1, &_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path, &_width, &_height, &_nrChannels, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (data) {
		if (_nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Failed to load a texture"<<endl;
	}
	stbi_image_free(data);
}
const void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, _texture);
}

const void Texture::Bind(unsigned int unit) const
{
	glBindTextureUnit(unit, _texture);
}

const void Texture::UnBind() const{
	glBindTexture(GL_TEXTURE_2D, 0);
}