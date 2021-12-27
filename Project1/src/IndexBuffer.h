#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cassert>

#include "Error.h"

class IndexBuffer
{
	friend class Mesh;
public:
	IndexBuffer(const void* data, unsigned int nIndices)
		: count(nIndices)
	{
		GLCall(glGenBuffers(1, &handle));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof GLuint, data, GL_STATIC_DRAW));
	}

	// TODO: maybe there's a function that can automatically get the index-count (buffer size)
	explicit IndexBuffer(GLuint iboHandle, GLuint nIndices)
	{
		assert(glIsBuffer(iboHandle) == GL_TRUE);
		handle = iboHandle;
		count = nIndices;
	}

	void Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
	}

	void Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	inline GLuint GetHandle() const
	{
		return handle;
	}

	inline GLuint GetCount() const
	{
		return count;
	}

	~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &handle));
	}

public:
	GLuint count; // # of indices

private:
	GLuint handle;
};

