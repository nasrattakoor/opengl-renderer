#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.Use();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr /* nullptr because index buffer is bound to GL_ELEMENT_ARRAY_BUFFER */));
	}

	// clears color buffer bit and depth buffer bit
	void Clear(float r = 0.3f, float g = 0.3f, float b = 1.0f) const
	{
		GLCall(glClearColor(r, g, b, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
};