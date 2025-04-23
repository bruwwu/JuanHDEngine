#pragma once
#include "Prerequisites.h"
#include "MeshComponent.h"
#include "fbxsdk.h"

class
	ModelLoader {
public:
	ModelLoader() = default;
	~ModelLoader() = default;

	bool
		InitializeFBXManager();

	bool
		LoadFBXModel(const std::string& filePath);

	void
		ProcessFBXNode(FbxNode* node);

	void
		ProcessFBXMesh(FbxNode* node);

	void
		ProcessFBXMaterials(FbxSurfaceMaterial* material);

	// Carga modelo OBJ en m_meshes directamente
	bool 
		LoadOBJ_model(const std::string& filePath);

	std::vector<std::string>
		GetTextureFileNames() const { return textureFileNames; }

private:
	FbxManager* lSdkManager;
	FbxScene* lScene;
	std::vector<std::string> textureFileNames;
public:
	std::string modelName;
	std::vector<MeshComponent> meshes;
};