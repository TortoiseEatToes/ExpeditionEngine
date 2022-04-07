#include "Input_FlashLight.h"

#include "../../Expedition Engine/GraphicsScene/GraphicsSceneManager.h"
#include "../../Expedition Engine/GraphicsScene/GraphicsScene.h"



void Input_FlashLight::OnKeyPressed()
{
	if (flashOn) 
	{
		updateLight.StopUpdating();
		GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->DisableSpotLightShadows(0, GetRegisteredScene());
		GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->ClearSpotLight(0);

		flashOn = false;
	}
	else
	{
		updateLight.StartUpdating(GetRegisteredScene());
		GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->EnableSpotLightShadows(0, GetRegisteredScene());

		flashOn = true;
	}
}

void Input_FlashLight::OnKeyReleased()
{
	if (!flashOn)
	{
		GraphicsSceneManager::GetCurrentScene()->GetLightMgr()->ClearSpotLight(0);
	}
}
