#pragma once

#include "CollisionVolume.h"

class CV_Plane : public CollisionVolume
{
public:
	CV_Plane() = default;
	CV_Plane(const CV_Plane& other) = delete;
	CV_Plane& operator= (const CV_Plane& other) = delete;
	~CV_Plane() = default;

	bool CollideAccept(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CollisionVolume& otherVolume) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Plane& otherPlane) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Sphere& otherSphere) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_AABB& otherAABB) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_OBB& otherOBB) override;

	void SetWorld(const Matrix4F& worldMatrix) override;

	const Vector4F& GetOrigin() const;
	const Vector4F& GetNormal() const;
	const float& GetLength() const;

	void Release(CollisionManager& collisionManager) override;

private:
	void Sanitize();

	Vector4F origin;
	Vector4F normal;
	float length = 1.0f;

	
};