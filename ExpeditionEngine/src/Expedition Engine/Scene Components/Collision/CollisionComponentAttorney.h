#pragma once

#include "CollisionComponent.h"

class CollisionComponentAttorney
{
public:
	struct CVControl
	{
	private:
		friend class CV_Sphere;
		friend class CV_Plane;
		friend class CV_AABB;
		friend class CV_OBB;

		static void Collision(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Sphere& otherSphere)
		{
			thisComponent.Collision(otherComponent, otherSphere);
		}

		static void Collision(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Plane& otherPlane)
		{
			thisComponent.Collision(otherComponent, otherPlane);
		}

		static void Collision(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_AABB& otherAABB)
		{
			thisComponent.Collision(otherComponent, otherAABB);
		}

		static void Collision(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_OBB& otherOBB)
		{
			thisComponent.Collision(otherComponent, otherOBB);
		}
	};

	class ManagerControl
	{
	private:
		friend class CollisionManager;

		static List<CollisionComponent*>::Iterator& GetIterator(CollisionComponent*& component)
		{
			return component->GetIterator();
		}

		static bool DetectCollision(CollisionComponent& component, CollisionComponent& otherComponent)
		{
			return component.DetectCollision(otherComponent);
		}
	};
};