#pragma once

#include "../../Expedition Engine/Game Object/GameObject.h"
#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_Sprite.h"
#include "../../Expedition Resources/LayerSettings.h"

#include "../../Expedition Engine/Math/Vector/Vector4F.h"
#include "../../Expedition Engine/Math/Matrix/Matrix4F.h"


class PlayerControllerSwapToLayer1 : public KeyboardInputComponent
{
public:

	GraphicsObject_Sprite* pSprite;
	LayerName originalLayer;

private:

	void OnKeyPressed() override 
	{
		Matrix4F world(pSprite->GetWorldUpdate(0));

		originalLayer = static_cast<LayerName>(static_cast<int>(world[f14]));

		pSprite->SetLayer(LayerFront);

	}

	void OnKeyHeld() override
	{

	}

	void OnKeyReleased() override
	{
		Matrix4F world(pSprite->GetWorldUpdate(0));

		pSprite->SetLayer(originalLayer);
	}
};