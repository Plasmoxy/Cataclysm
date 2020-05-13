#pragma once

#include <string>

class Texture {
public:
	unsigned int rendererId = 0;
	unsigned char* localBuffer = nullptr;
	int width = 0, height = 0, bpp = 0; // bpp = bits per pixel
	std::string filePath;

	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;
};