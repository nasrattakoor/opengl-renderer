#pragma once
#include <GL\glew.h>
#include "Error.h"
#include "VertexBuffer.h"
#include "VertexAttribute.h"

class VertexArray
{
	friend class Mesh;
public:
	VertexArray()
	{
		GLCall(glGenVertexArrays(1, &handle));
		Bind();
	}
	explicit VertexArray(GLuint VAO)
	{
		// TODO: assert parameter is valid vertex array object
		handle = VAO;
	}
	~VertexArray()
	{
		Unbind();
		GLCall(glDeleteVertexArrays(1, &handle));
	}

	void AddBuffer(const VertexBuffer& vb, const BufferLayout& layout)
	{
		Bind();
		vb.Bind();
		const auto& elements = layout.GetAttributes();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, (element.normalized ? GL_TRUE : GL_FALSE), layout.GetStride(), reinterpret_cast<const void*>(offset)));
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
	}

	void Bind() const
	{
		GLCall(glBindVertexArray(handle));
	}

	void Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

private:
	GLuint handle;
};

