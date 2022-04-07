#pragma once
#include "CV_BoundingBox.h"

class CV_OBB : public CV_BoundingBox
{
public:
	CV_OBB() = default;
	CV_OBB(const CV_OBB& other) = delete;
	CV_OBB& operator= (const CV_OBB& other) = delete;
	virtual ~CV_OBB() = default;

	bool CollideAccept(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CollisionVolume& otherVolume) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Plane& otherPlane) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Sphere& otherSphere) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_AABB& otherAABB) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_OBB& otherOBB) override;

	void SetPosition(const Vector4F& min, const Vector4F& max);

	void SetWorld(const Matrix4F& worldMatrix) override;
	void Release(CollisionManager& collisionManager) override;

private:
};