#include <iostream>
#include "texture.h"
#include "image.h"
#include <GL/glew.h>

Texture::Texture(const std::string& varname, const std::string& filename): m_varname(varname)
{
	ImagePtr img = Image::Make(filename);
	glGenTextures(1, &m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, img-> GetNChannels() == 3 ? GL_RGB:GL_RGBA,
		img-> GetWidth(), img-> GetHeight(), 0,
		img-> GetNChannels() == 3 ? GL_RGB : GL_RGBA,
		GL_UNSIGNED_BYTE, img -> GetData());
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	std::cout << varname << ": " << filename << std::endl;
}

TexturePtr Texture::PtrMake(const std::string& varname, const std::string& filename)
{
	return TexturePtr(new Texture(varname, filename));
}

Texture::~Texture()
{
}

void Texture::Load(StatePtr st)
{
	ShaderPtr shd = st -> GetShader();
	shd -> ActiveTexture(m_varname.c_str());
	glBindTexture(GL_TEXTURE_2D, m_tex);
}

void Texture::Unload(StatePtr st)
{
	ShaderPtr shd = st -> GetShader();
	shd -> DeactiveTexture();
}
