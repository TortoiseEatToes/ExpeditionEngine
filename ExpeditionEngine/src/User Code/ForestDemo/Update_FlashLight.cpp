#include "Update_FlashLight.h"

#include "../../Expedition Engine/Scenes/SceneManager.h"
#include "../../Expedition Engine/Camera/Camera.h"

void Update_FlashLight::OnUpdate()
{

	Vector4F flashPos = SceneManager::GetCurrentPerspectiveCamera()->GetPosition() + (SceneManager::GetCurrentPerspectiveCamera()->GetRight() * 30);
	Vector4F flashDirc = -1 * SceneManager::GetCurrentPerspectiveCamera()->GetDirection(); //(GraphicsSceneManager::GetCurrentScene()->currentCamera->GetPosition() + -1 * GraphicsSceneManager::GetCurrentScene()->currentCamera->GetDirection()) - flashPos;

	GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->UpdateSpotLight(0, flashPos, flashDirc, Vector4F(0.0f, .008f, 0.0f, 0.0f), 2000, 16, amb, diff, spec);
	//GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->UpdateSpotLightShadows(0);
}
