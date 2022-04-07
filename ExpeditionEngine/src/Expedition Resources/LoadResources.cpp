#include "../Expedition Engine/Engine/ExpeditionEngine.h"

#include "../Expedition Engine/Graphics/Model/Managers/ModelManager.h"
#include "../Expedition Engine/Graphics/Model/Managers/TextureManager.h"
#include "../Expedition Engine/Graphics/Terrain/TerrainObjectManager.h"
#include "../Expedition Engine//Graphics/Image/ImageManager.h"
#include "../Expedition Engine/Graphics/Sprites/Manager/SpriteFontManager.h"
#include "../Expedition Resources/FontSettings.h"
#include "../Expedition Engine/Graphics/Model/FlatPlane.h"
#include "../Expedition Engine/Graphics/Model/SkyBox.h"
#include "../Expedition Engine/Graphics/Model/SpriteModel.h"
#include "../Expedition Engine/Audio/Clips/AudioClipManager.h"

#include "../Expedition Engine/Graphics/Particles/ParticleSettingsManagerAttorney.h"
#include "AudioSettings.h"

#include "GraphicsResourcesSettings.h"

//This is the first function called by the ExpeditionEngine.  Use this to load all of the external assets that you will need for your game.
void ExpeditionEngine::LoadResources()
{
	ModelManager::Load(ModelName::SphereModel, Model::PreMadeModels::UnitSphere);
	ModelManager::LoadSprite(ModelName::ParticleModel, 5.0f, 5.0f);
	ModelManager::Load(ModelName::CubeModel, Model::PreMadeModels::UnitBoxRepTexture);
	ModelManager::Load(ModelName::TankModel, "Assets/t99body.azul");
	ModelManager::LoadFlatPlane(ModelName::PlaneModel, 3,3);
	ModelManager::LoadSkyBox(ModelName::SkyModel, 200,200,200);
	ModelManager::LoadSkyBox(ModelName::SkyModel2, 200, 50,200);
	ModelManager::LoadSkyBox(ModelName::SkyModel3, 20000, 20000, 20000);

	//ModelManager::LoadBox(ModelName::TreeModel, 1, 3, 1);
	ModelManager::Load(ModelName::TreeModel, "Assets/Models/tree.azul");
	ModelManager::Load(ModelName::VaseModel, "Assets/Models/Vases.azul");
	ModelManager::Load(ModelName::CampfireModel, "Assets/Models/Campfire1.azul");


	AudioClipManager::Load(AudioClipName::SongA, "SongA.wav");
	AudioClipManager::Load(AudioClipName::AudioFootSteps, "Footsteps.wav");

	TextureManager::Load(TextureName::DanceFloorTexture, L"Assets/Textures/DanceFloor.dds");
	TextureManager::Load(TextureName::SkyTex, L"Assets/Textures/SkyTex.dds");
	TextureManager::Load(TextureName::SkyTex1, L"Assets/Textures/SkyTex_Dark.dds");
	TextureManager::Load(TextureName::FlameTexture, L"Assets/Textures/FireParticle3.dds");
	TextureManager::Load(TextureName::WhiteParticleTexture, L"Assets/Textures/WhiteParticle.dds");

	TerrainObjectManager::Load(TerrainName::TestTerrain, L"Assets/Textures/HMHills2.tga", 210, 50, -99, 1, 1);
	TerrainObjectManager::Load(TerrainName::ForestTerrain, L"Assets/Textures/HMHills2.tga", 10000, 200, 0, 1, 1);
	TerrainObjectManager::Load(TerrainName::BasinTerrain, L"Assets/Textures/HMBasin2.tga", 200, 50, 0, 1, 1);

	ParticleSettingsManagerAttorney::LoadResourcesControl::AllocateParticleMemory(ParticleName::Water, ModelManager::Get(ModelName::ParticleModel), TextureManager::Get(TextureName::WhiteParticleTexture), NumberOfParticles);
	ParticleSettingsManagerAttorney::LoadResourcesControl::AllocateParticleMemory(ParticleName::Earth, ModelManager::Get(ModelName::ParticleModel), TextureManager::Get(TextureName::WhiteParticleTexture), NumberOfParticles);
	ParticleSettingsManagerAttorney::LoadResourcesControl::AllocateParticleMemory(ParticleName::Fire, ModelManager::Get(ModelName::ParticleModel), TextureManager::Get(TextureName::FlameTexture), NumberOfParticles);
	ParticleSettingsManagerAttorney::LoadResourcesControl::AllocateParticleMemory(ParticleName::Air, ModelManager::Get(ModelName::ParticleModel), TextureManager::Get(TextureName::WhiteParticleTexture), NumberOfParticles);
}