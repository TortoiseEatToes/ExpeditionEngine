#include "CollisionComponent.h"

#include "Volumes/CV_Plane.h"
#include "Volumes/CV_Sphere.h"

#include "Manager/CollisionSystemAttorney.h"

#include "../../Scenes/SceneManagerAttorney.h"

CollisionComponent::~CollisionComponent()
{
	ReleaseCollisionVolume();
}

void CollisionComponent::StartDetectingCollision(const SceneName& sceneToRegisterInto)
{
	registeredScene = sceneToRegisterInto;
	RegisterIntoScene();
}

void CollisionComponent::StopDetectingCollision()
{
	DeregisterFromScene();
}

void CollisionComponent::SetCollisionVolumeSphere()
{
	if (currentCollisionVolumeType != CollisionVolumeType::Sphere)
	{
		ReleaseCollisionVolume();

		pCollisionVolume = &SceneManagerAttorney::EngineSceneGetter::GetEngineScene(registeredScene).GetCollisionManager().AcquireSphere();
		currentCollisionVolumeType = CollisionVolumeType::Sphere;
	}
}

void CollisionComponent::SetCollisionVolumePlane()
{
	if (currentCollisionVolumeType != CollisionVolumeType::Plane)
	{
		ReleaseCollisionVolume();

		pCollisionVolume = &SceneManagerAttorney::EngineSceneGetter::GetEngineScene(registeredScene).GetCollisionManager().AcquirePlane();
		currentCollisionVolumeType = CollisionVolumeType::Plane;
	}
}

void CollisionComponent::SetCollisionVolumeAABB()
{
	if (currentCollisionVolumeType != CollisionVolumeType::AABB)
	{
		ReleaseCollisionVolume();

		pCollisionVolume = &SceneManagerAttorney::EngineSceneGetter::GetEngineScene(registeredScene).GetCollisionManager().AcquireAABB();
		currentCollisionVolumeType = CollisionVolumeType::AABB;
	}
}

void CollisionComponent::SetCollisionVolumeOBB()
{
	if (currentCollisionVolumeType != CollisionVolumeType::OBB)
	{
		ReleaseCollisionVolume();

		pCollisionVolume = &SceneManagerAttorney::EngineSceneGetter::GetEngineScene(registeredScene).GetCollisionManager().AcquireOBB();
		currentCollisionVolumeType = CollisionVolumeType::OBB;
	}
}

void CollisionComponent::SetWorld(const Matrix4F& worldMatrix)
{
	pCollisionVolume->SetWorld(worldMatrix);
}

void CollisionComponent::RegisterIntoSceneChild(EngineScene& engineScene)
{
	engineScene.GetCollisionManager().Register(this);
}

void CollisionComponent::DeregisterFromSceneChild(EngineScene& engineScene)
{
	engineScene.GetCollisionManager().Deregister(this);
}

bool CollisionComponent::DetectCollision(CollisionComponent& otherComponent)
{
	return pCollisionVolume->CollideAccept(*this, otherComponent, *otherComponent.GetCollisionVolume());
}

void CollisionComponent::ReleaseCollisionVolume()
{
	if (pCollisionVolume != nullptr)
	{
		pCollisionVolume->Release(SceneManagerAttorney::EngineSceneGetter::GetEngineScene(registeredScene).GetCollisionManager());
		pCollisionVolume = nullptr;
	}
}

CollisionVolume* CollisionComponent::GetCollisionVolume()
{
	return pCollisionVolume;
}

List<CollisionComponent*>::Iterator& CollisionComponent::GetIterator()
{
	return iterator;
}
