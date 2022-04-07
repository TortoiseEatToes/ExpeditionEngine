#pragma once

#include "../../../Expedition Engine/Scene Components/Game Object/GameObject.h"
#include "..//..//..//Expedition Engine/Math/Matrix/Matrix4F.h"
#include "../../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject.h"
#include "..//Collision/PlaneCollision.h"

class PlaneController : public GameObject
{
public:
	PlaneController() = delete;
	PlaneController(const SceneName& sceneToExistIn);
	PlaneController(PlaneController&&) = delete;
	PlaneController(const PlaneController&) = delete;
	const PlaneController& operator = (PlaneController&&) = delete;
	const PlaneController& operator = (const PlaneController&) = delete;
	~PlaneController();

	void OnSceneEnter() override;
	void OnSceneExit() override;

private:
	const static int numOfPlanes = 6;

	Matrix4F worldMatrices[numOfPlanes];

	GraphicsObject go_Plane;
	GraphicsObject go_Sky;
	GraphicsObject go_Terrain;
	PlaneCollision** planeCollision;
};

