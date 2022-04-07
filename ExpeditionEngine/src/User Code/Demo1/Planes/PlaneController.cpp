#include "PlaneController.h"
#include "..//..//..//Expedition Engine/Graphics/Model/Managers/ModelManager.h"
#include "..//..//..//Expedition Engine/Graphics/Terrain/TerrainObjectManager.h"
#include "..//..//..//Expedition Engine/Graphics/Model/Managers/TextureManager.h"

#include "../../../Expedition Engine/DX12App/d3dUtil_12.h"

PlaneController::PlaneController(const SceneName& sceneToExistIn)
	: GameObject(sceneToExistIn), go_Plane(sceneToExistIn, ModelManager::Get(ModelName::PlaneModel), numOfPlanes), go_Terrain(sceneToExistIn, TerrainObjectManager::Get(TerrainName::TestTerrain)),
	go_Sky(sceneToExistIn, ModelManager::Get(ModelName::SkyModel), 1)
{
	worldMatrices[0] = (Matrix4F(TRANS, Vector4F(0, -100, 0, 1)) * Matrix4F(SCALE, 200)).TransposeCopy();
	worldMatrices[1] = ((Matrix4F(TRANS, Vector4F(-100, 0,0,1)) * Matrix4F(ROT_AXISANGLE, Vector4F(0, 0, 1), -1.5708f)).TransposeCopy()
		* Matrix4F(SCALE, 200)).TransposeCopy();
	worldMatrices[2] = ((Matrix4F(TRANS, Vector4F(100, 0 ,0,1)) * Matrix4F(ROT_AXISANGLE, Vector4F(0, 0, 1), 1.5708f)).TransposeCopy()  
		* Matrix4F(SCALE, 200)).TransposeCopy();
	worldMatrices[3] = ((Matrix4F(TRANS, Vector4F(0,0,-100,1)) * Matrix4F(ROT_AXISANGLE, Vector4F(1, 0, 0), 1.5708f)).TransposeCopy()
		* Matrix4F(SCALE, 200)).TransposeCopy();
	worldMatrices[4] = ((Matrix4F(TRANS, Vector4F(0,0,100,1)) * Matrix4F(ROT_AXISANGLE, Vector4F(1,0,0), -1.5708f)).TransposeCopy()
		* Matrix4F(SCALE, 200)).TransposeCopy();
	worldMatrices[5] = ((Matrix4F(TRANS, Vector4F(0, 100, 0, 1)) * Matrix4F(ROT_AXISANGLE, Vector4F(1, 0, 0), 3.14159f)).TransposeCopy()
		* Matrix4F(SCALE, 200)).TransposeCopy();

	Vector4F color(.5f, .5f, .5f, 1);
	
	planeCollision = new PlaneCollision*[numOfPlanes];

	for (int i = 0; i < numOfPlanes; i++) 
	{
		go_Plane.SetWorld(worldMatrices[i], i);
		go_Plane.SetMaterial(color, color, color,i);

		planeCollision[i] = new PlaneCollision(sceneToExistIn);
	}

	go_Terrain.SetMaterial(Colors::ForestGreen, Colors::ForestGreen, Colors::White);
	//go_Terrain.SetTexture(TextureName::DanceFloorTexture);
	go_Plane.SetTexture(TextureName::DanceFloorTexture);
	go_Sky.SetTexture(TextureName::SkyTex);
}

PlaneController::~PlaneController() 
{
	for (int i = 0; i < numOfPlanes; i++) 
	{
		delete planeCollision[i];
	}

	delete[] planeCollision;
}

void PlaneController::OnSceneEnter() 
{
	//go_Plane.StartDrawing();
	go_Sky.StartDrawingTexture();
	go_Terrain.StartDrawingColorLight();

	for (int i = 0; i < numOfPlanes; i++) {
		planeCollision[i]->SetCollisionVolumePlane();
		planeCollision[i]->SetWorld(worldMatrices[i]);

		planeCollision[i]->StartDetectingCollision(registeredScene);
	}
}

void PlaneController::OnSceneExit() 
{
	//go_Plane.StopDrawing();
	go_Sky.StopDrawingTexture();
	go_Terrain.StopDrawingColorLight();

	for (int i = 0; i < numOfPlanes; i++) 
	{
		planeCollision[i]->StopDetectingCollision();
	}
}