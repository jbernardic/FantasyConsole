#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "../../Dependencies/stb_image.h"
#include "ErrorHandler.h"
using namespace std;
Texture::Texture(const char* path)
	:m_Path(path)

{
	glGenTextures(1, &m_Texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	// texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* data = stbi_load(path, &m_Width, &m_Height, &m_NrChannels, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (data) {
		if (m_NrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Failed to load a texture"<<endl;
	}
	stbi_image_free(data);
}
const void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

const void Texture::Bind(unsigned int unit) const
{
	glBindTextureUnit(unit, m_Texture);
}

const void Texture::UnBind() const{
	glBindTexture(GL_TEXTURE_2D, 0);
}