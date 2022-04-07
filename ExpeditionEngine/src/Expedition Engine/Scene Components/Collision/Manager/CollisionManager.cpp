#include "CollisionManager.h"

#include "../CollisionComponentAttorney.h"

void CollisionManager::ProcessCollisions()
{
	//Create 


	activeComponentList.SetFront(iterator);
	while (!iterator.IsOutOfNodes())
	{
		iterator.GetNext(iteratorInnerLoop);

		while (!iteratorInnerLoop.IsOutOfNodes())
		{
			CollisionComponentAttorney::ManagerControl::DetectCollision(*iterator.GetCurrentObject(), *iteratorInnerLoop.GetCurrentObject());
			++iteratorInnerLoop;
		}

		++iterator;
	}
}

CV_Sphere& CollisionManager::AcquireSphere()
{
	return *cvPoolSphere.GetPooledObject();
}

void CollisionManager::ReleaseSphere(CV_Sphere& cvSphere)
{
	cvPoolSphere.RecycleObject(&cvSphere);
}

CV_Plane& CollisionManager::AcquirePlane()
{
	return *cvPoolPlane.GetPooledObject();
}

void CollisionManager::ReleasePlane(CV_Plane& cvPlane)
{
	cvPoolPlane.RecycleObject(&cvPlane);
}

CV_AABB & CollisionManager::AcquireAABB()
{
	return *cvPoolAABB.GetPooledObject();
}

void CollisionManager::ReleaseAABB(CV_AABB & cvAABB)
{
	cvPoolAABB.RecycleObject(&cvAABB);
}

CV_OBB & CollisionManager::AcquireOBB()
{
	return *cvPoolOBB.GetPooledObject();
}

void CollisionManager::ReleaseOBB(CV_OBB & cvOBB)
{
	cvPoolOBB.RecycleObject(&cvOBB);
}

void CollisionManager::Register(CollisionComponent* pComponent)
{
	activeComponentList.PushFront(pComponent, CollisionComponentAttorney::ManagerControl::GetIterator(pComponent));
}

void CollisionManager::Deregister(CollisionComponent* pComponent)
{
	activeComponentList.Remove(CollisionComponentAttorney::ManagerControl::GetIterator(pComponent));
}
