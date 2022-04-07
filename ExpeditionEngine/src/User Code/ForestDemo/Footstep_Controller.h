#pragma once
#include "../../Expedition Engine/Scene Components/Game Object/GameObject.h"

#include "Footstep_Input.h"

class Footstep_Controller : public GameObject
{
public:
	Footstep_Controller() = delete;
	Footstep_Controller(Footstep_Controller&&) = delete;
	Footstep_Controller(const Footstep_Controller&) = delete;
	const Footstep_Controller& operator = (Footstep_Controller&&) = delete;
	const Footstep_Controller& operator = (const Footstep_Controller&) = delete;

	Footstep_Controller(SceneName sceneName);
	~Footstep_Controller();

private:
	Footstep_Input input;

	// Inherited via GameObject
	virtual void OnSceneEnter() override;
	virtual void OnSceneExit() override;
};