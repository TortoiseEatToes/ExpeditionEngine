#pragma once

#include "../../../Containers/List.h"
#include "../../../Containers/Pool.h"

#include "../Volumes/CV_Plane.h"
#include "../Volumes/CV_Sphere.h"
#include "../Volumes/CV_AABB.h"
#include "../Volumes/CV_OBB.h"

class CollisionComponent;

class CollisionManager
{
public:
	CollisionManager() = default;
	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager& operator= (const CollisionManager& other) = delete;
	~CollisionManager() = default;

	/// <summary>Once per frame, the current scene calls this to check for collisions.</summary>
	void ProcessCollisions();


	/// <summary>Get a sphere volume from the pool.</summary>
	/// <returns>Reference to the sphere volume to be used by a collision component</returns>
	CV_Sphere& AcquireSphere();

	/// <summary>Get a plane volume from the pool.</summary>
	/// <returns>Reference to the plane volume to be used by a collision component</returns>
	CV_Plane& AcquirePlane();

	/// <summary>Get an axis aligned bounding box from the pool.</summary>
	/// <returns>Reference to the axis aligned bounding box to be used by a collision component</returns>
	CV_AABB& AcquireAABB();

	/// <summary>Get an oriented bounding box from the pool.</summary>
	/// <returns>Reference to the oriented bounding box to be used by a collision component</returns>
	CV_OBB& AcquireOBB();


	/// <summary>Return a sphere volume back into the sphere pool.</summary>
	/// <param name="cvSphere">Reference to the sphere volume to be inserted into the sphere pool</param>
	void ReleaseSphere(CV_Sphere& cvSphere);

	/// <summary>Return a plane volume back into the plane pool.</summary>
	/// <param name="cvPlane">Reference to the sphere volume to be inserted into the plane pool</param>
	void ReleasePlane(CV_Plane& cvPlane);

	/// <summary>Return an axis aligned bounding box back into the plane pool.</summary>
	/// <param name="cvPlane">Reference to the axis aligned bounding box to be inserted into the plane pool</param>
	void ReleaseAABB(CV_AABB& cvAABB);

	/// <summary>Return an oriented bounding box back into the plane pool.</summary>
	/// <param name="cvPlane">Reference to the oriented bounding box to be inserted into the plane pool</param>
	void ReleaseOBB(CV_OBB& cvOBB);


	/// <summary>Register a new collision component for collision checking.</summary>
	/// <param name="pComponent">The component to be inserted into the activeComponentList</param>
	void Register(CollisionComponent* pComponent);

	/// <summary>Deregister an old collision component from collision checking.</summary>
	/// <param name="pComponent">The component to be removed from the activeComponentList</param>
	void Deregister(CollisionComponent* pComponent);


private:
	Pool<CV_Sphere> cvPoolSphere;
	Pool<CV_Plane> cvPoolPlane;
	Pool<CV_AABB> cvPoolAABB;
	Pool<CV_OBB> cvPoolOBB;

	List<CollisionComponent*> activeComponentList;
	List<CollisionComponent*>::Iterator iterator;
	List<CollisionComponent*>::Iterator iteratorInnerLoop;
};