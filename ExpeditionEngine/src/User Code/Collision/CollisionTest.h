#pragma once

#include "../../Expedition Engine/Game Object/Components/Collision/CollisionComponent.h"

class CollisionTest : public CollisionComponent
{
public:
	CollisionTest();
	CollisionTest(const CollisionTest& other) = delete;
	CollisionTest& operator= (const CollisionTest& other) = delete;
	~CollisionTest();

private:
	void Collision(CollisionComponent& otherVolume, CV_Sphere& otherSphere) override;
	void Collision(CollisionComponent& otherVolume, CV_Plane& otherPlane) override;
};