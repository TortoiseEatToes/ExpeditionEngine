#include "CollisionSystem.h"

CollisionSystem* CollisionSystem::pInstance = nullptr;

#include "CollisionManager.h"

void CollisionSystem::privSetCurrentCollisionManager(CollisionManager& collisionManager)
{
	pCurrentCollisionManager = &collisionManager;
}

void CollisionSystem::privSetCollisionVolumeSphere(CollisionVolume*& pCollisionVolume)
{
	pCollisionVolume = &pCurrentCollisionManager->AcquireSphere();
}

void CollisionSystem::privRecycleCollisionVolume(CV_Sphere*& pSphere)
{
	pCurrentCollisionManager->ReleaseSphere(*pSphere);
}

void CollisionSystem::privRecycleCollisionVolume(CV_Plane*& pPlane)
{
	pCurrentCollisionManager->ReleasePlane(*pPlane);
}

void CollisionSystem::privSetCollisionVolumePlane(CollisionVolume*& pCollisionVolume)
{
	pCollisionVolume = &pCurrentCollisionManager->AcquirePlane();
}
