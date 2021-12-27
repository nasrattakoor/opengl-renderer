#include "Model_2.h"
#include <iostream>

void Model::RenderModel(Renderer& renderer, const Shader& shader)
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		unsigned int materialIndex = meshToTex[i];

		if (materialIndex < textures.size() && textures[materialIndex])
		{
			textures[materialIndex]->UseTexture();
		}

		meshes[i]->RenderMesh(renderer, shader);
	}
}

bool Model::LoadModel(const std::string & fileName)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		std::cerr << "Model " << fileName << " failed to load: " << importer.GetErrorString();
		return false;
	}

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);

	return true;
}

void Model::LoadNode(aiNode * node, const aiScene * scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

void Model::LoadMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		// assuming the vertex layout is {pos.x, pos.y, pos.z, tex.u, tex.v, norm.x, norm.y, norm.z}
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		
		// TODO: I'm not sure what the parameter for this method means. Does the function only return
		// whether texcoords exist for a single vertex, or whether they exist in the whole model?
		//if (mesh->HasTextureCoords(0))
		//{
		//	if (mesh->mTextureCoords[0])
		//	{
		//		vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		//	}
		//	else {
		//		vertices.insert(vertices.end(), { 0.0f, 0.0f });
		//	}
		//}
		//vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.emplace_back(face.mIndices[j]);
		}
	}

	Mesh* newMesh = new Mesh(&vertices[0],GL_FLOAT, vertices.size(), &indices[0], indices.size());
	//newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshes.emplace_back(newMesh);
	meshToTex.emplace_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene * scene)
{
	textures.resize(scene->mNumMaterials);
	
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		textures[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Textures/") + filename;

				textures[i] = std::make_unique<Texture>(texPath.c_str());

				if (!textures[i]->LoadTexture())
				{
					std::cerr << "Failed to load texture at: " << texPath.c_str() << std::endl;
					textures[i].reset();
				}
			}
		}

		if (!textures[i])
		{
			textures[i] = std::make_unique<Texture>("Textures/plain.png");
			textures[i]->LoadTextureA();
		}
	}
}