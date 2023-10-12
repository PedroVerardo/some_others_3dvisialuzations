#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
#include <cstdlib>


Image::Image(const std::string &filename)
{
	m_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_nchannels, 0);
	if (!m_data)
	{
		std::cerr << "Could noot load the image: " << filename << std::endl;
		exit(1);
	}
}

Image::~Image()
{
}

const unsigned char* Image::GetData() const
{
	return m_data;
}

int Image::GetHeight() const
{
	return m_height;
}

int Image::GetNChannels() const
{
	return m_nchannels;
}

int Image::GetWidth() const
{
	return m_width;
}

ImagePtr Image::Make(const std::string& filename)
{
	return ImagePtr(new Image(filename));
}

void Image::ExtractSubimage(int x, int y, int w, int h, unsigned char* data)
{

}