#pragma once

#include "CollisionVolume.h"

class CV_Sphere : public CollisionVolume
{
public:
	CV_Sphere() = default;
	CV_Sphere(const CV_Sphere& other) = delete;
	CV_Sphere& operator= (const CV_Sphere& other) = delete;
	~CV_Sphere() = default;

	bool CollideAccept(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CollisionVolume& otherVolume) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Plane& otherPlane) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Sphere& otherSphere) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_AABB& otherAABB) override;
	bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_OBB& otherOBB) override;

	void SetWorld(const Matrix4F& worldMatrix) override;

	const Vector4F& GetCenter() const;
	const float& GetRadius() const;

	
	void Release(CollisionManager& collisionManager) override;

private:
	void Sanitize();

	Vector4F center = Vector4F(0.0f, 0.0f, 0.0f, 1.0f);
	float radius = 1.0f;

};