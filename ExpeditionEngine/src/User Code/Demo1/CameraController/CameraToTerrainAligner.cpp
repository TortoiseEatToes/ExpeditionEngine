#include "CameraToTerrainAligner.h"

#include "../../../Expedition Engine/Camera/Camera.h"
#include "../../../Expedition Engine/Graphics/Terrain/TerrainModel.h"

#include "../../../Expedition Engine/GraphicsScene/GraphicsSceneManager.h"
#include "../../../Expedition Engine/GraphicsScene/GraphicsScene.h"

#include "../../../Expedition Engine/Scenes/SceneManager.h"

void CameraToTerrainAligner::OnUpdate()
{
	cam->AlignHeightToTerrain(terrain, offset);


	Vector4F amb = Vector4F (1.0f, 1.0f, 1.0f, 1.0f);
	Vector4F diff = Vector4F(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4F spec = Vector4F(1.0f, 1.0f, 1.0f, 0.2f);

	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->UpdateSpotLight(0, SceneManager::GetCurrentPerspectiveCamera()->GetPosition() + (SceneManager::GetCurrentPerspectiveCamera()->GetRight() * 30), -1 * SceneManager::GetCurrentPerspectiveCamera()->GetDirection(), Vector4F(0, 1, 0, 0), 1000, 32, amb, diff, spec);
	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->UpdateSpotLightShadows(0);

}
