#pragma once

#include <vector>
#include <string>
#include <memory>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "../Texture _2.h"
#include "Renderer.h"

class Model
{
public:
	bool LoadModel(const std::string& fileName);
	void RenderModel(Renderer& renderer, const Shader& shader);
	//void ClearModel();

private:
	// loading using assimp
	void LoadNode(aiNode *node, const aiScene *scene);
	void LoadMesh(aiMesh *mesh, const aiScene *scene);
	void LoadMaterials(const aiScene *scene);

	std::vector<std::unique_ptr<Mesh>> meshes;
	std::vector<std::unique_ptr<Texture>> textures;
	std::vector<unsigned int> meshToTex;
};

