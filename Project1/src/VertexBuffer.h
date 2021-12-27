#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "VertexAttribute.h"


// TODO: assert that a vao was created and bound
class VertexBuffer
{
	friend class Mesh;
public:
	VertexBuffer(const void* data, GLenum type, unsigned int vertices_count)
	{
		GLCall(glGenBuffers(1, &handle));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
		GLCall(glBufferData(GL_ARRAY_BUFFER, vertices_count * VertexBufferElement::GetSizeOfType(type), data, GL_STATIC_DRAW));
	}

	~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &handle));
	}

	void Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, handle));
	}

	void Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

private:
	std::vector<BufferLayout> attributes;
	GLuint handle;
	GLuint index;
	GLuint nComponents;
};