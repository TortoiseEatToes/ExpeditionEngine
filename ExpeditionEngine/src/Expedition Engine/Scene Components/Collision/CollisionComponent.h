#pragma once

#include "../SceneComponent.h"
#include "../../Containers/List.h"

class CollisionVolume;
class CV_Sphere;
class CV_Plane;
class CV_AABB;
class CV_OBB;

class Matrix4F;

class CollisionComponent : public SceneComponent
{
public:
	CollisionComponent() = default;
	CollisionComponent(const CollisionComponent& other) = delete;
	CollisionComponent& operator= (const CollisionComponent& other) = delete;
	virtual ~CollisionComponent() ;

	/// <summary>On the next frame, start detecting collision between this component and the others in this scene.</summary>
	/// <param name="sceneToRegisterInto">The SceneName that this component should register into</param>
	void StartDetectingCollision(const SceneName& sceneToRegisterInto);

	/// <summary>Quite literally, remove this component from all collision detection</summary>
	void StopDetectingCollision();

	/// <summary>Use a sphere to represent this component during collision testing</summary>
	void SetCollisionVolumeSphere();

	/// <summary>Use a plane to represent this component during collision testing</summary>
	void SetCollisionVolumePlane();

	/// <summary>Use an axis aligned bounding box to represent this component during collision testing</summary>
	void SetCollisionVolumeAABB();

	/// <summary>Use an oriented bounding box to represent this component during collision testing</summary>
	void SetCollisionVolumeOBB();

	/// <summary>Set the world matrix.  This will update the attributes of the collision volume that this component owns.</summary>
	/// <param name="sceneToRegisterInto">A const reference to the worldMatrix that should be used</param> 
	void SetWorld(const Matrix4F& worldMatrix);

	/// <summary>Return a pointer to the collision volume that this component is currently using.</summary>
	/// <returns>Return a pointer to the collision volume that this component is currently using.</returns> 
	CollisionVolume* GetCollisionVolume();

protected:

	/// <summary>Override this function to define what should happen when this component collides with a sphere.</summary>
	/// <param name="otherComponent">A reference to the collision component that you collided with</param>
	/// <param name="otherSphere">A reference to the sphere that the other collision component was using</param>
	virtual void Collision(CollisionComponent& otherComponent, CV_Sphere& otherSphere) {};

	/// <summary>Override this function to define what should happen when this component collides with a plane.</summary>
	/// <param name="otherComponent">A reference to the collision component that you collided with</param>
	/// <param name="otherPlane">A reference to the plane that the other collision component was using</param>
	virtual void Collision(CollisionComponent& otherComponent, CV_Plane& otherPlane) {};

	/// <summary>Override this function to define what should happen when this component collides with an axis aligned bounding box.</summary>
	/// <param name="otherComponent">A reference to the collision component that you collided with</param>
	/// <param name="otherAABB">A reference to the axis aligned bounding box that the other collision component was using</param>
	virtual void Collision(CollisionComponent& otherComponent, CV_AABB& otherAABB) {};

	/// <summary>Override this function to define what should happen when this component collides with an oriented bounding box.</summary>
	/// <param name="otherComponent">A reference to the collision component that you collided with</param>
	/// <param name="otherAABB">A reference to the oriented bounding box that the other collision component was using</param>
	virtual void Collision(CollisionComponent& otherComponent, CV_OBB& otherOBB) {};

private:
	friend class CollisionComponentAttorney;

	void RegisterIntoSceneChild(EngineScene& engineScene) override;
	void DeregisterFromSceneChild(EngineScene& engineScene) override;

	bool DetectCollision(CollisionComponent& otherComponent);

	void ReleaseCollisionVolume();
	

	enum CollisionVolumeType
	{
		Sphere,
		Plane,
		AABB,
		OBB,
		Unassigned
	};

	CollisionVolume* pCollisionVolume = nullptr;
	CollisionVolumeType currentCollisionVolumeType = CollisionVolumeType::Unassigned;

	List<CollisionComponent*>::Iterator& GetIterator();
	List<CollisionComponent*>::Iterator iterator;
};