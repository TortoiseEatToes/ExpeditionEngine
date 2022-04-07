#pragma once
#include "CV_BoundingBox.h"

class CV_AABB : public CV_BoundingBox
{
public:
	CV_AABB() = default;
	CV_AABB(const CV_AABB& other) = delete;
	CV_AABB& operator= (const CV_AABB& other) = delete;
	virtual ~CV_AABB() = default;

	bool CollideAccept(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CollisionVolume& otherVolume) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Plane& otherPlane) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Sphere& otherSphere) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_AABB& otherAABB) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_OBB& otherOBB) override;

	//void SetPosition(const Vector4F& min, const Vector4F& max);

	void SetWorld(const Matrix4F& worldMatrix) override;
	void Release(CollisionManager& collisionManager) override;

private:
};