#pragma once

#include "../../../Math/Vector/Vector4F.h"

class CollisionComponent;
class CollisionManager;

class CV_Plane;
class CV_Sphere;
class CV_AABB;
class CV_OBB;

class CollisionVolume : public Align16
{
public:
	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume& other) = delete;
	CollisionVolume& operator= (const CollisionVolume& other) = delete;
	virtual ~CollisionVolume() = default;

	/// <summary>This collision manager calls this function to kick off the visitor pattern for handling collisions.</summary>
	/// <param name="thisComponent">Reference to the component that is being check for collision</param>
	/// <param name="otherComponent">Reference to the other component that is being checked against</param>
	/// <param name="otherVolume">Reference to the volume that belongs to the otherComponent</param>
	/// <returns>bool wether or not the thisComponent and otherComponent did collide</returns>
	virtual bool CollideAccept(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CollisionVolume& otherVolume) = 0;

	/// <summary>This is called by the visitor pattern when the other volume is a plane.</summary>
	/// <param name="thisComponent">Reference to the component that is being check for collision</param>
	/// <param name="otherComponent">Reference to the other component that is being checked against</param>
	/// <param name="otherPlane">Reference to the plane volume that belongs to the otherComponent</param>
	/// <returns>bool wether or not the thisComponent and otherComponent did collide</returns>
	virtual bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Plane& otherPlane) = 0;

	/// <summary>This is called by the visitor pattern when the other volume is a sphere.</summary>
	/// <param name="thisComponent">Reference to the component that is being check for collision</param>
	/// <param name="otherComponent">Reference to the other component that is being checked against</param>
	/// <param name="otherSphere">Reference to the sphere volume that belongs to the otherComponent</param>
	/// <returns>bool wether or not the thisComponent and otherComponent did collide</returns>
	virtual bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Sphere& otherSphere) = 0;

	/// <summary>This is called by the visitor pattern when the other volume is an axis aligned bounding box.</summary>
	/// <param name="thisComponent">Reference to the component that is being check for collision</param>
	/// <param name="otherComponent">Reference to the other component that is being checked against</param>
	/// <param name="otherSphere">Reference to the axis aligned bounding box volume that belongs to the otherComponent</param>
	/// <returns>bool wether or not the thisComponent and otherComponent did collide</returns>
	virtual bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_AABB& otherAABB) = 0;

	/// <summary>This is called by the visitor pattern when the other volume is an oriented bounding box.</summary>
	/// <param name="thisComponent">Reference to the component that is being check for collision</param>
	/// <param name="otherComponent">Reference to the other component that is being checked against</param>
	/// <param name="otherSphere">Reference to the oriented bounding box volume that belongs to the otherComponent</param>
	/// <returns>bool wether or not the thisComponent and otherComponent did collide</returns>
	virtual bool CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_OBB& otherOBB) = 0;

	/// <summary>Call this to move your specific component.</summary>
	/// <param name="sceneToRegisterInto">The world matrix that should be used to update the position, rotation, and scale of this volume</param>
	virtual void SetWorld(const Matrix4F& worldMatrix) = 0;

	virtual void Release(CollisionManager& collisionManager) = 0;

protected:

	


};