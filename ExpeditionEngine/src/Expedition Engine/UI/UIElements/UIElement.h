#pragma once

#include "../../../Expedition Resources/LayerSettings.h"
#include "../../../Expedition Resources/SceneSettings.h"

#include "../../Scene Components/SceneComponent.h"

class UIElement : public SceneComponent
{
public:
	UIElement() = default;
	UIElement(const UIElement& other) = delete;
	UIElement& operator= (const UIElement& other) = delete;
	~UIElement() = default;
	
	virtual void StartDrawing(const SceneName& sceneToRegisterTo) = 0;
	virtual void StopDrawing() = 0;

	virtual void SetLayer(const LayerName& layer) = 0;
	

protected:
	

private:
};