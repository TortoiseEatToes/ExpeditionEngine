#include "TerrainObjectManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "TerrainModel.h"
#include "../Model/Managers/TextureManager.h"



TerrainObjectManager* TerrainObjectManager::TerrainInstance = nullptr;

void TerrainObjectManager::Initialize(ID3D12GraphicsCommandList4* cmdList) {
	Instance().loadCmdList = cmdList;
}

TerrainObjectManager::TerrainObjectManager()
{

}


TerrainObjectManager::~TerrainObjectManager()
{
	for (int i = 0; i < NumberOfTerrains; i++) {
		delete terrainArray[i];
	}
}

void TerrainObjectManager::Terminate() {
	delete TerrainInstance;
	TerrainInstance = nullptr;
}

TerrainModel* TerrainObjectManager::privGet(const TerrainName& key) {

	return terrainArray[key];
}



void TerrainObjectManager::privLoad(const TerrainName& key, LPCWSTR heightmapFile, const float& len, const float& maxheight,
	const float& ytrans, const int& RepeatU, const int& RepeatV) {

	terrainArray[key] = new TerrainModel(heightmapFile, len, maxheight,
		ytrans, RepeatU, RepeatV, loadCmdList);
}

wchar_t * TerrainObjectManager::addDefaultPath(const wchar_t* path) {

	const int BUFFER_SIZE = 100;

	assert(wcslen(path) + wcslen(defaultPath) < BUFFER_SIZE - 1);

	wchar_t* tmp = new wchar_t[BUFFER_SIZE];

	wcsncpy_s(tmp, BUFFER_SIZE, defaultPath, wcslen(defaultPath));

	wcsncat_s(tmp, BUFFER_SIZE, path, wcslen(path));

	return tmp;
}
