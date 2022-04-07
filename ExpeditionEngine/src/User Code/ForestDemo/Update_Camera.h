#pragma once

#include "../../Expedition Engine/Scene Components/Update/UpdateComponent.h"

class TerrainModel;
class Camera;

class Update_Camera : public UpdateComponent
{
public:
	TerrainModel* terrain;
	float offset;
	Camera* cam;

	float camSpeed;

	int prevCamX;
	int prevCamY;

private:
	// Inherited via UpdateComponent
	virtual void OnUpdate() override;

	int currX;
	int currY;
};