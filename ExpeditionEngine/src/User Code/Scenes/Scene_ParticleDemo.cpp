#include "Scene_ParticleDemo.h"

#include "../../Expedition Engine/GraphicsScene/GraphicsSceneManager.h"
#include "../../Expedition Engine/GraphicsScene/GraphicsScene.h"
#include "../../Expedition Engine/Camera/Camera.h"

#include "../../Expedition Engine/Graphics/Model/Managers/ModelManager.h"
#include "../../Expedition Engine/Graphics/Terrain/TerrainObjectManager.h"
#include "../../Expedition Engine/Graphics/Light/LightManager.h"
#include "../../Expedition Engine/DX12App/d3dUtil_12.h"

#include "../../Expedition Engine/Audio/AudioSystem.h"

Scene_ParticleDemo::Scene_ParticleDemo()
	: Scene(SceneName::Scene1),
	particleEmitterFire(sceneName, ParticleName::Fire), go_Vases(sceneName, ModelManager::Get(ModelName::VaseModel), 1), camControl(sceneName), particleEmitterWater(sceneName, ParticleName::Water),
	particleEmitterEarth(sceneName, ParticleName::Earth), particleEmitterAir(sceneName, ParticleName::Air), go_Sky(sceneName, ModelManager::Get(ModelName::SkyModel2), 1),
	musicEmitter("SongA.wav"), go_Plane(sceneName, ModelManager::Get(ModelName::PlaneModel), 1), go_Terrain(sceneName, TerrainObjectManager::Get(TerrainName::TestTerrain))
{
	sceneSwapper.sceneToSwapTo = SceneName::Scene2;
	sceneSwapper2.sceneToSwapTo = SceneName::Scene3;
}

Scene_ParticleDemo::~Scene_ParticleDemo()
{
}

void Scene_ParticleDemo::SceneInitialize()
{
	sceneSwapper.RegisterForOnPressed(sceneName, Input::Number2);
	sceneSwapper2.RegisterForOnPressed(sceneName, Input::Number3);

	//------------------------------------
	// Set Fire
	//------------------------------------

	//Set position values
	particleEmitterFire.SetParticlePosition(-0.55f, -0.5f,  //X
											2.0f, 2.1f,  //Y
											0.0f, 0.1f); //Z

	//Set velocity values
	particleEmitterFire.SetParticleVelocity(-2.0f, 2.0f,  //X
											 8.0f, 10.1f,  //Y
											 -2.0f, 2.0f); //Z

	//Set acceleration values
	particleEmitterFire.SetParticleAcceleration(-1.0f, 1.0f,  //X
												-9.8f, -9.7f,  //Y
												-1.0f, 1.0f); //Z

	//Set color tint values
	//particleEmitterFire.SetParticleColorTint( 0.0f, 0.0f, //R
	//										  0.0f, 0.0f, //G
	//										  0.0f, 0.0f, //B
	//										  0.0f, 0.0f);//A

	//Spawn particles
	particleEmitterFire.SetBurstLifetime(0.5f, 1.0f);
	//particleEmitterFire.SpawnParticleBurst(10);
	particleEmitterFire.StartSpawnParticleBurstRepeating(40, 0.01f);

	//------------------------------------
	// Set Water
	//------------------------------------

	//Set position values
	particleEmitterWater.SetParticlePosition(-3.0f, -2.9f,  //X
											2.5f, 2.6f,  //Y
											0.0f, 0.01f); //Z

	//Set velocity values
	particleEmitterWater.SetParticleVelocity(-2.0f, 2.0f,  //X
												8.0f, 10.1f,  //Y
												-2.0f, 2.0f); //Z
	
	//Set acceleration values
	particleEmitterWater.SetParticleAcceleration(-1.0f, 1.0f,  //X
													-9.8f, -9.7f,  //Y
													-1.0f, 1.0f); //Z
	
	//Set color tint values
	particleEmitterWater.SetParticleColorTint(Colors::LightSkyBlue);
	
	//Spawn particles
	particleEmitterWater.SetBurstLifetime(0.5f, 1.0f);
	//particleEmitterFire.SpawnParticleBurst(10);
	particleEmitterWater.StartSpawnParticleBurstRepeating(40, 0.01f);

	//------------------------------------
	// Set Earth
	//------------------------------------

	//Set position values
	particleEmitterEarth.SetParticlePosition(1.3f, 1.4f,  //X
												2.5f, 2.6f,  //Y
												0.0f, 0.01f); //Z

	//Set velocity values
	particleEmitterEarth.SetParticleVelocity(-2.0f, 2.0f,  //X
											8.0f, 10.1f,  //Y
											-2.0f, 2.0f); //Z

	//Set acceleration values
	particleEmitterEarth.SetParticleAcceleration(-1.0f, 1.0f,  //X
												-9.8f, -9.7f,  //
												-1.0f, 1.0f); //Z

	//Set color tint values
	particleEmitterEarth.SetParticleColorTint(Colors::BurlyWood);

	//Spawn particles
	particleEmitterEarth.SetBurstLifetime(0.5f, 1.0f);
	//particleEmitterFire.SpawnParticleBurst(10);
	particleEmitterEarth.StartSpawnParticleBurstRepeating(40, 0.01f);

	//------------------------------------
	// Set Air
	//------------------------------------

	//Set position values
	particleEmitterAir.SetParticlePosition(3.25f, 3.3f,  //X
											1.5f, 1.6f,  //Y
											0.1f, 0.11f); //Z

	//Set velocity values
	particleEmitterAir.SetParticleVelocity(-2.0f, 2.0f,  //X
											8.0f, 10.1f,  //Y
											-2.0f, 2.0f); //Z

	//Set acceleration values
	particleEmitterAir.SetParticleAcceleration(-1.0f, 1.0f,  //X
												-9.8f, -9.7f,  //
												-1.0f, 1.0f); //Z

	//Set color tint values
	particleEmitterAir.SetParticleColorTint(Colors::WhiteSmoke);

	//Spawn particles
	particleEmitterAir.SetBurstLifetime(0.5f, 1.0f);
	//particleEmitterFire.SpawnParticleBurst(10);
	particleEmitterAir.StartSpawnParticleBurstRepeating(40, 0.01f);


	go_Vases.SetWorld(Matrix4F(TRANS, Vector4F(0, 0, 0, 1)));
	go_Vases.SetMaterial(0, Colors::Black, Colors::Black, Colors::White);
	go_Vases.SetMaterial(1, Colors::Black, Colors::Green, Colors::White);
	go_Vases.SetMaterial(2, Colors::Black, Colors::Blue, Colors::White);
	go_Vases.SetMaterial(3, Colors::Black, Colors::Purple, Colors::White);

	go_Sky.SetWorld(Matrix4F(TRANS, Vector4F(0, 25, 0, 1)));
	go_Sky.SetMaterial(Colors::White, Colors::White, Colors::White);

	go_Plane.SetWorld(Matrix4F(TRANS, Vector4F(10, 5, 0, 1)));

	go_Terrain.SetWorld(Matrix4F(IDENTITY));
	go_Terrain.SetMaterial(0, Colors::Green, Colors::ForestGreen, Colors::White);

	Vector4F  amb(0.5f, 0.5f, 0.5f, 1.0f);
	Vector4F diff(0.5f, 0.5f, 0.5f, 1.0f);
	Vector4F spec(0.5f, 0.5f, 0.5f, 0.2f);

	//GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->UpdateDirectionLight(0, Vector4F(0, -1, -1), amb, diff, spec);
	//GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->EnableDirectionLightShadows(0, 2048, Vector4F(0,0,0,1), 10, sceneName);
	//
	//GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->UpdateDirectionLight(1, Vector4F(2, -2, 1), amb, diff, spec);
	//GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->EnableDirectionLightShadows(1, 2048, Vector4F(0, 0, 0, 1), 10, sceneName);						
	//
	//GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->UpdateDirectionLight(2, Vector4F(10, -3, -5), amb, diff, spec);
	//GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->EnableDirectionLightShadows(2, 2048, Vector4F(0, 0, 0, 1), 10, sceneName);

	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->UpdateSpotLight(0, Vector4F(0, 5, 6, 1), Vector4F(0,-1,-6,0), Vector4F(0,1,0,0), 100, 8, amb, diff, spec);
	GraphicsSceneManager::GetScene(sceneName)->GetLightMgr()->EnableSpotLightShadows(0,sceneName);

	SceneManager::GetCurrentPerspectiveCamera()->SetOrientAndPosition(Vector4F(0, 1, 0, 0), Vector4F(0.0f, 4.0f, 0.0f, 0.0f), Vector4F(0, 4, 10, 1));
	SceneManager::GetCurrentPerspectiveCamera()->Update();

	//GraphicsSceneManager::GetScene(sceneName)->currentCamera->setOrthographic(0, 100, 0, 100, 0, 20);
	//GraphicsSceneManager::GetScene(sceneName)->currentCamera->setOrientAndPosition(Vector4F(0, 1, 0), Vector4F(0, 0, 0, 1), Vector4F(0, 10, 10, 1));
	//GraphicsSceneManager::GetScene(sceneName)->currentCamera->SetType(Camera::Type::ORTHOGRAPHIC_2D);
	//GraphicsSceneManager::GetScene(sceneName)->currentCamera->updateCamera();

	//Emmaline, set this to 0.0f if you want to silence the audio system.
	AudioSystem::SetMasterVolume(0.1f);

	//musicEmitter.SetPan(2.1f);
	//musicEmitter.SetVolume(0.1f);
	musicEmitter.Play(1);
	//musicEmitter.SetPitch(2.1f);
	//musicEmitter.Pause();
	//musicEmitter.Play();
}

void Scene_ParticleDemo::SceneStart()
{
	go_Vases.StartDrawingColorLight();
	go_Sky.StartDrawingColorLight();
	//go_Plane.StartDrawingTexture();

	//go_Terrain.StartDrawingColorLight();

	camControl.EnterScene(sceneName);
}

void Scene_ParticleDemo::SceneStop()
{	
	go_Vases.StopDrawingColorLight();
	go_Sky.StopDrawingColorLight();
	//go_Plane.StopDrawingTexture();

	//go_Terrain.StopDrawingColorLight();
	camControl.ExitScene();
}

void Scene_ParticleDemo::SceneShutDown()
{
}
