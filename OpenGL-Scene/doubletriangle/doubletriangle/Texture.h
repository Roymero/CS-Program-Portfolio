#pragma once
#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void bind();
	// Unbinds a texture
	void unbind();
	// Deletes a texture
	void del();
};
#endif