#include "Mesh.h"
#include "Renderer.h"

// TODO: make the vertex attributes configurable from interface.
//       Maybe add parameters like int positions, int normals, int texCoords = {0,1,2...}
Mesh::Mesh(const void * vb_data, GLenum vb_type, unsigned int vb_nVertices, const void * ib_data, unsigned int ib_nIndices)
	: vbo(vb_data, vb_type, vb_nVertices), ibo(ib_data, ib_nIndices)
{
	BufferLayout layout;
	assert(vb_type == GL_FLOAT);
	layout.Push<float>(3); // position xyz
	vao.AddBuffer(vbo, layout);
}

//void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)
//{
//	ibo.count = numOfIndices;
//
//	glGenVertexArrays(1, &vao.handle);
//	glBindVertexArray(vao.handle);
//
//	glGenBuffers(1, &ibo.handle);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.handle);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);
//
//	glGenBuffers(1, &vbo.handle);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo.handle);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
//	glEnableVertexAttribArray(2);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//	glBindVertexArray(0);
//}

// TODO: Get rid of this method and replace it with a GetVertexArray or GetVertexBuffer method.
//       Then you can call 
//                       renderer.Draw(mesh.GetVertexArray(), mesh.GetIndexBuffer(), shader)  
//       in your main function.
void Mesh::RenderMesh(Renderer& renderer, const Shader& shader)
{
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	renderer.Draw(vao, ibo, shader);
}