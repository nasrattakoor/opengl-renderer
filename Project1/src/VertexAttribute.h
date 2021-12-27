#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

//class VertexAttribute
//{
//public:
//	VertexAttribute(GLuint index_, GLint nComponents_, unsigned int sizeInBytes_, unsigned int offsetInsideAttribute)
//		:
//		index(index_), nComponents(nComponents_), sizeInBytes(sizeInBytes_), offset(offsetInsideAttribute)
//	{
//		GLCall(glVertexAttribPointer(index, nComponents, GL_FLOAT, GL_FALSE, sizeInBytes, reinterpret_cast<const void*>//(offset)));
//		GLCall(glEnableVertexAttribArray(index));
//	}
//
//	~VertexAttribute()
//	{
//		GLCall(glDisableVertexAttribArray(index));
//	}
//
//private:
//	GLuint index;
//	GLint nComponents;
//	unsigned int sizeInBytes;
//	unsigned int offset;
//};

struct VertexBufferElement
{
	GLuint type;
	GLuint count;
	bool normalized;

	static unsigned int GetSizeOfType(GLenum type)
	{
		switch (type)
		{
			case GL_FLOAT: return sizeof GLfloat;
			case GL_UNSIGNED_INT: return sizeof GLuint;
			case GL_UNSIGNED_BYTE: return sizeof GLubyte;
		}
		ASSERT(false);
		return 0;
	}
};

class BufferLayout
{
public:
	template <typename T>
	void Push(unsigned int count)
	{
		static_assert(false); // all other types should cause error
	}

	template<>
	void Push<float>(unsigned int count)
	{
		attributes.push_back({ GL_FLOAT, count, false });
		stride += count * sizeof GLfloat;
	}
	 
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		attributes.push_back({ GL_UNSIGNED_INT, count, false });
		stride += count * sizeof GLuint;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		attributes.push_back({ GL_UNSIGNED_BYTE, count, false });
		stride += count * sizeof GLubyte;
	}

	inline const std::vector< VertexBufferElement>& GetAttributes() const { return attributes; }
	inline GLuint GetStride() const { return stride; }

private:
	std::vector<VertexBufferElement> attributes;
	GLuint stride = 0;
};