#pragma once

#include "../../../Expedition Engine/Scene Components/Collision/CollisionComponent.h"

class PlaneCollision : public CollisionComponent
{
public:
	PlaneCollision() = delete;
	PlaneCollision(const SceneName& sceneToExistIn) { registeredScene = sceneToExistIn; };
	PlaneCollision(PlaneCollision&&) = delete;
	PlaneCollision(const PlaneCollision&) = delete;
	const PlaneCollision& operator = (PlaneCollision&&) = delete;
	const PlaneCollision& operator = (const PlaneCollision&) = delete;
	~PlaneCollision() {};


private:
	void Collision(CollisionComponent& otherVolume, CV_Sphere& otherSphere) override {};
	void Collision(CollisionComponent& otherVolume, CV_Plane& otherPlane) override {};
};

