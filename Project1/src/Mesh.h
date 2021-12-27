#pragma once

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh
{
public:
	Mesh(const void* vb_data, GLenum vb_type, unsigned int vb_nVertices, const void* ib_data, unsigned int ib_nIndices);
	//void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh(Renderer& renderer, const Shader& shader);

private:
	VertexArray vao; // must be first
	VertexBuffer vbo;
	IndexBuffer ibo;
};

