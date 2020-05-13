
#include <GL/glew.h>
#include "Texture.h"
#include "vendor/stb_image.h"

Texture::Texture(const std::string& path): filePath(path) {

	// flip because, opengl (0, 0) is bottom left not top left (PNG)
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	glGenTextures(1, &rendererId);
	glBindTexture(GL_TEXTURE_2D, rendererId);

	// must specify these 4 parameters (they're not default)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

	glBindTexture(GL_TEXTURE_2D, rendererId);
	if (localBuffer) stbi_image_free(localBuffer);
}

Texture::~Texture() {
	glDeleteTextures(1, &rendererId);
}

void Texture::bind(unsigned int slot) const {
	glActiveTexture(GL_TEXTURE0 + slot); // select texture slot
	glBindTexture(GL_TEXTURE_2D, rendererId);
}

void Texture::unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}
