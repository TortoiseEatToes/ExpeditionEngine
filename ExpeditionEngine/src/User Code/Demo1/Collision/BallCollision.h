#pragma once

#include "../../../Expedition Engine/Scene Components/Collision/CollisionComponent.h"

class GraphicObject_ColorLight;
class Vector4F;
class MAtrix4F;

class BallCollision : public CollisionComponent
{
public:
	BallCollision() = delete;
	BallCollision(const SceneName& sceneToExistIn);
	BallCollision(BallCollision&&) = delete;
	BallCollision(const BallCollision&) = delete;
	const BallCollision& operator = (BallCollision&&) = delete;
	const BallCollision& operator = (const BallCollision&) = delete;
	~BallCollision();

	Vector4F* velocityVector;
	Matrix4F* worldMatrix;

	int bounceCounter;

private:
	void Collision(CollisionComponent& otherVolume, CV_Sphere& otherSphere) override;
	void Collision(CollisionComponent& otherVolume, CV_Plane& otherPlane) override;
};

