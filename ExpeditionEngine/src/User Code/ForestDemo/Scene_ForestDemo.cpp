#include "Scene_ForestDemo.h"
#include "../../Expedition Engine/Graphics/Terrain/TerrainObjectManager.h"
#include "../../Expedition Engine/Graphics/Terrain/TerrainModel.h"
#include "../../Expedition Engine/Graphics/Model/Managers/ModelManager.h"
#include "../../Expedition Engine/DX12App/d3dUtil_12.h"

#include "../../Expedition Engine/Audio/AudioSystem.h"

Scene_ForestDemo::Scene_ForestDemo() : Scene(SceneName::SceneForest), go_Terrain(sceneName, TerrainObjectManager::Get(TerrainName::ForestTerrain)), cam(sceneName), 
	go_SkyBox(sceneName, ModelManager::Get(ModelName::SkyModel3)),
	musicEmitter("SongA.wav"),
 	go_CampFires(sceneName, ModelManager::Get(ModelName::CampfireModel)), fireParticles(sceneName, ParticleName::Fire), footsteps(sceneName)
{
	float halfSpots = .5f * treeSpotsPerSide;
	float halfLength = .5f * lengthOfTreeArea;

	int randNum;

	for (int i = 0; i < treeSpotsPerSide; i++) 
	{
		for (int j = 0; j < treeSpotsPerSide; j++)
		{
			randNum = rand() % chanceOfTreeSpawnDenominator;

			if (randNum < chanceOfTreeSpawnNumerator)
			{
				float x = halfLength - (i * sizeOfTreeSpot);
				float z = halfLength - (j * sizeOfTreeSpot);
				float y = go_Terrain.GetTerrainModel()->BarycentrifyHeight(Vector4F(x, 0, z, 1));

				Vector4F* vect = new Vector4F(x, y, z, 1);

				list_vWorldPos.PushFront(vect);
			}

		}
	}
	

	pgo_Trees = new GraphicsObject(sceneName, ModelManager::Get(ModelName::TreeModel), list_vWorldPos.GetSize());

}

Scene_ForestDemo::~Scene_ForestDemo()
{
	delete pgo_Trees;

	List<Vector4F*>::Iterator it;
	list_vWorldPos.SetFront(it);

	while (list_vWorldPos.GetSize() > 0)
	{
		delete list_vWorldPos.PopFront();
	}
}

void Scene_ForestDemo::SceneInitialize()
{
	List<Vector4F*>::Iterator it;
	list_vWorldPos.SetFront(it);

	int i = 0;

	for (int i = 0; i < list_vWorldPos.GetSize(); i++)
	{
		pgo_Trees->SetWorld(Matrix4F(TRANS, *it.GetCurrentObject()), i);
		pgo_Trees->SetMaterial(1, Colors::Brown * .1f, Colors::Brown * .3f, Colors::Brown * .3f, i);
		pgo_Trees->SetMaterial(0, Colors::ForestGreen * .1f, Colors::ForestGreen, Colors::ForestGreen, i);

		it.GetNext(it);
	}

	go_Terrain.SetMaterial(Colors::Chartreuse * .1f, Colors::Chartreuse, Colors::Chartreuse);

	go_SkyBox.SetTexture(TextureName::SkyTex1);


	go_CampFires.SetMaterial(0, Colors::Brown * .1f, Colors::Brown * .3f, Colors::Brown * .3f);
	go_CampFires.SetMaterial(1, Colors::Gray * .1f, Colors::Gray * .3f, Colors::Gray * .3f);


	Vector4F campfirePos(50, 0, 50, 1);

	campfirePos.Y() = go_Terrain.GetTerrainModel()->BarycentrifyHeight(campfirePos);

	go_CampFires.SetWorld(Matrix4F(TRANS, campfirePos));


	//Set position values
	fireParticles.SetParticlePosition(40, 60,  //X
		campfirePos.Y(), campfirePos.Y() + 15,  //Y
		40, 60); //Z

	//Set velocity values
	fireParticles.SetParticleVelocity(0.0f, 20.0f,  //X
		20.0f, 50.1f,  //Y
		0.0f, 20.0f); //Z
	
	//Set acceleration values
	fireParticles.SetParticleAcceleration(-1.0f, 1.0f,  //X
		-1.1f, -1.0f,  //Y
		-1.0f, 1.0f); //Z
	
	//Set color tint values
	//particleEmitterFire.SetParticleColorTint( 0.0f, 0.0f, //R
	//										  0.0f, 0.0f, //G
	//										  0.0f, 0.0f, //B
	//										  0.0f, 0.0f);//A
	
	//Spawn particles
	fireParticles.SetBurstLifetime(0.5, 1.0f);
	//particleEmitterFire.SpawnParticleBurst(10);
	fireParticles.StartSpawnParticleBurstRepeating(60, 0.01f);


	Vector4F  amb(0.1f, 0.1f, 0.1f, 1.0f);
	Vector4F diff(0.1f, 0.1f, 0.1f, 1.0f);
	Vector4F spec(0.1f, 0.1f, 0.1f, 0.2f);

	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->UpdateDirectionLight(0, Vector4F(0, -1, -1), amb, diff, spec);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->InitializeDirectionalLightShadow(0, 1024, Vector4F(0, 0, 0, 1), 10000);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->InitializeDirectionalLightShadow(1, 1024, Vector4F(0, 0, 0, 1), 10000);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->InitializeDirectionalLightShadow(2, 1024, Vector4F(0, 0, 0, 1), 10000);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->EnableDirectionLightShadows(0, sceneName);


	//Sara put this here so that I can test that the task graph is holding even with all of your shadows and gameplay running around.
	AudioSystem::SetMasterVolume(0.1f);
	//musicEmitter.Play(1);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->InitializeSpotLightShadow(0, 128);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->InitializeSpotLightShadow(1, 64);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->InitializeSpotLightShadow(2, 64);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->InitializeSpotLightShadow(3, 64);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->InitializeSpotLightShadow(4, 64);

	amb = Vector4F(0.0f, 0.0f, 0.0f, 0.0f);
	diff = Vector4F(2.0f, 2.0f, 2.0f, 1.0f);
	spec = Vector4F(0.5f, 0.5f, 0.5f, 1.0f);

	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->UpdateSpotLight(1,  campfirePos + Vector4F(20, 30, 0), Vector4F(1, -1, 0), Vector4F(0, .08f, 0, 0), 300, 2, amb, diff, spec);
	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->EnableSpotLightShadows(1, sceneName);

	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->UpdateSpotLight(2, campfirePos + Vector4F(-20, 30, 0), Vector4F(-1, -1, 0), Vector4F(0, .08f, 0, 0), 300, 2, amb, diff, spec);
	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->EnableSpotLightShadows(2, sceneName);

	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->UpdateSpotLight(3, campfirePos + Vector4F(0, 30, -20), Vector4F(0, -1, -1), Vector4F(0, .08f, 0, 0), 300, 2, amb, diff, spec);
	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->EnableSpotLightShadows(3, sceneName);

	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->UpdateSpotLight(4, campfirePos + Vector4F(0, 30, 20), Vector4F(0, -1, 1), Vector4F(0, .08f, 0, 0), 300, 2, amb, diff, spec);
	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->EnableSpotLightShadows(4, sceneName);

}

void Scene_ForestDemo::SceneStart()
{
	go_Terrain.StartDrawingColorLight();
	pgo_Trees->StartDrawingColorLight();
	go_SkyBox.StartDrawingTexture();

	go_CampFires.StartDrawingColorLight();

	cam.EnterScene(sceneName);
	cam.SetTerrainAlignInfo(go_Terrain.GetTerrainModel(), SceneManager::GetCurrentPerspectiveCamera(), 40);

	footsteps.EnterScene(sceneName);
}


void Scene_ForestDemo::SceneStop()
{
	go_SkyBox.StopDrawingTexture();
	go_Terrain.StopDrawingColorLight();
	pgo_Trees->StopDrawingColorLight();

	go_CampFires.StopDrawingColorLight();

	cam.ExitScene();
	footsteps.ExitScene();
}

void Scene_ForestDemo::SceneShutDown()
{
}
