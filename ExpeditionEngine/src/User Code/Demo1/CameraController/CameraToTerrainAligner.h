#pragma once

#include "../../../Expedition Engine/Scene Components/Update/UpdateComponent.h"

class TerrainModel;
class Camera;

class CameraToTerrainAligner : public UpdateComponent
{
public:
	TerrainModel* terrain;
	float offset;
	Camera* cam;

private:
	// Inherited via UpdateComponent
	virtual void OnUpdate() override;
};