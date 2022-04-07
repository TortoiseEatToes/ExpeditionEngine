#include "ModelManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../SpriteModel.h"
#include "../FlatPlane.h"
#include "../SkyBox.h"

#include "../ModelTools.h"


ModelManager* ModelManager::pInstance = nullptr;

void ModelManager::Initialize(ID3D12GraphicsCommandList4* cmdList) {
	
	pInstance = new ModelManager;
	pInstance->loadCmdList = cmdList;
}

ModelManager::ModelManager()
{
}


ModelManager::~ModelManager()
{

	for (int i = 0; i < NumberOfModels; i++) {
		if(modelArray[i])
			delete modelArray[i];
	}

}

void ModelManager::Terminate() {
	delete pInstance;
	pInstance = nullptr;
}

Model* ModelManager::privGet(const ModelName& key) {
	return modelArray[key];
}


void ModelManager::Load(const ModelName& key, Model::PreMadeModels model) {
	Instance().privLoad(key, model);
};

void ModelManager::Load(const ModelName& key, Model* model) {
	Instance().privLoad(key, model);
}
void ModelManager::LoadSprite(const ModelName& key, float x, float y)
{
	Load(key, new SpriteModel(x, y, Instance().loadCmdList));
}

void ModelManager::LoadFlatPlane(const ModelName& key, float x, float y)
{
	Load(key, new FlatPlane(x, y, Instance().loadCmdList));
}

void ModelManager::LoadSkyBox(const ModelName& key, float x, float y, float z)
{
	Load(key, new SkyBox(x, z, y, Instance().loadCmdList));
}

void ModelManager::LoadBox(const ModelName& key, float width, float height, float depth)
{
	StandardVertex* pStdVerts = nullptr;
	TriangleByIndex* pTriList = nullptr;
	int numVerts = 0;
	int numTris = 0;
	
	
	ModelTools::CreateBox(pStdVerts, numVerts, pTriList, numTris, width, height, depth);

	Load(key, new Model(pStdVerts, numVerts, pTriList, numTris, Instance().loadCmdList));
}


void ModelManager::privLoad(const ModelName& key, const char* path) {

	modelArray[key] = new Model(path, Instance().loadCmdList);
}

void ModelManager::privLoad(const ModelName& key, Model::PreMadeModels model) {

	modelArray[key] = new Model(model, Instance().loadCmdList);
}

void ModelManager::privLoad(const ModelName& key, Model* model) {

	modelArray[key] = model;
}


char * ModelManager::addDefaultPath(const char* path) {

	const int BUFFER_SIZE = 100;

	assert(strlen(path) + strlen(defaultPath) < BUFFER_SIZE - 1);

	char* tmp = new char[BUFFER_SIZE];

	strncpy_s(tmp, BUFFER_SIZE, defaultPath, strlen(defaultPath));

	strncat_s(tmp, BUFFER_SIZE, path, strlen(path));

	return tmp;
}
