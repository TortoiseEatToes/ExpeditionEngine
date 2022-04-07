#pragma once

class CollisionVolume;
class CollisionManager;
class CV_Sphere;
class CV_Plane;

class CollisionSystem
{
public:

private:
	friend class CollisionSystemAttorney;

	CollisionSystem() = default;
	CollisionSystem(const CollisionSystem& other) = delete;
	CollisionSystem& operator= (const CollisionSystem& other) = delete;
	~CollisionSystem() = default;
	

	static void Initialize()
	{
		pInstance = new CollisionSystem();
	}

	static CollisionSystem& Instance()
	{
		return *pInstance;
	}

	static void Terminate()
	{
		delete pInstance;
	}

	/// <summary>This is called by the current scene to assign the pCurrentCollisionManager.</summary>
	/// <param name="collisionManager">The SceneName that this component should register into</param>
	static void SetCurrentCollisionManager(CollisionManager& collisionManager)
	{
		Instance().privSetCurrentCollisionManager(collisionManager);
	}
	void privSetCurrentCollisionManager(CollisionManager& collisionManager);

	// ------------------------- Get Volumes --------------------------------------
	/// <summary>Assign a plane volume to the given pointer.</summary>
	/// <param name="pCollisionVolume">Reference to the pointer that should be assigned to a plane volume</param>
	static void SetCollisionVolumePlane(CollisionVolume*& pCollisionVolume)
	{
		Instance().privSetCollisionVolumePlane(pCollisionVolume);
	}
	void privSetCollisionVolumePlane(CollisionVolume*& pCollisionVolume);

	/// <summary>Assign a sphere volume to the given pointer.</summary>
	/// <param name="pCollisionVolume">Reference to the pointer that should be assigned to a sphere volume</param>
	static void SetCollisionVolumeSphere(CollisionVolume*& pCollisionVolume)
	{
		Instance().privSetCollisionVolumeSphere(pCollisionVolume);
	}
	void privSetCollisionVolumeSphere(CollisionVolume*& pCollisionVolume);
	//-------------------------------------------------------------------------------


	//------------------ Recycle Volumes -----------------------------
	/// <summary>Use this to put the sphere volume back into the pool.</summary>
	/// <param name="pSphere">Reference to a pointer to the sphere to be put into the pool</param>
	static void RecycleCollisionVolume(CV_Sphere*& pSphere)
	{
		Instance().privRecycleCollisionVolume(pSphere);
	}
	void privRecycleCollisionVolume(CV_Sphere*& pSphere);

	/// <summary>Use this to put the plane volume back into the pool.</summary>
	/// <param name="pPlane">Reference to a pointer to the plane to be put into the pool</param>
	static void RecycleCollisionVolume(CV_Plane*& pPlane)
	{
		Instance().privRecycleCollisionVolume(pPlane);
	}
	void privRecycleCollisionVolume(CV_Plane*& pPlane);
	// -----------------------------------------------------------------



	static CollisionSystem* pInstance;
	CollisionManager* pCurrentCollisionManager;
};