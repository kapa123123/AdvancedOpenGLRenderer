#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);

}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset); //Way to communicate with the shader from external
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}