#pragma once

#include "CollisionSystem.h"

class CollisionSystemAttorney
{
public:
	class EngineControl
	{
	private:
		friend class ExpeditionEngine;

		static void Initialize()
		{
			CollisionSystem::Initialize();
		}

		static void Terminate()
		{
			CollisionSystem::Terminate();
		}
	};

	class EngineSceneControl
	{
	private:
		friend class EngineScene;

		static void SetCurrentCollisionManager(CollisionManager& collisionManager)
		{
			CollisionSystem::SetCurrentCollisionManager(collisionManager);
		}
	};

	class CollisionComponentControl
	{
	private:
		friend class CollisionComponent;

		static void SetCollisionVolumeSphere(CollisionVolume*& pCollisionVolume)
		{
			CollisionSystem::SetCollisionVolumeSphere(pCollisionVolume);
		}

		static void SetCollisionVolumePlane(CollisionVolume*& pCollisionVolume)
		{
			CollisionSystem::SetCollisionVolumePlane(pCollisionVolume);
		}
	};
};