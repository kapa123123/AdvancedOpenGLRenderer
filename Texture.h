#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H


#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shaderClass.h"

class Texture
{
public:
	GLuint ID; //ID Type to allow multiple Textures
	const char* type;
	GLuint unit;

	Texture(const char* image, const char* texType, GLuint slot);

	// Assign Texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	// Binds a to Object
	void Bind();

	// Unbline object to clear 
	void Unbind();

	// Delete texture
	void Delete();
};




#endif