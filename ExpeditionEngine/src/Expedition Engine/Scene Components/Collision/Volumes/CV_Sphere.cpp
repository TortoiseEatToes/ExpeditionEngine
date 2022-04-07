#include "CV_Sphere.h"

#include "CV_Plane.h"


#include "../Manager/CollisionManager.h"
#include "../CollisionComponentAttorney.h"
#include "../../../Math/MathTools.h"

#include "../../../Math/Matrix/Matrix4F.h"


bool CV_Sphere::CollideAccept(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CollisionVolume& otherVolume)
{
	return otherVolume.CollideVisit(otherComponent, thisComponent, *this);
}

bool CV_Sphere::CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Plane& otherPlane)
{
	if (MathTools::Intersect(*this, otherPlane))
	{
		CollisionComponentAttorney::CVControl::Collision(thisComponent, otherComponent, otherPlane);
		CollisionComponentAttorney::CVControl::Collision(otherComponent, thisComponent, *this);
		return true;
	}
	else
	{
		return false;
	}
}

bool CV_Sphere::CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Sphere& otherSphere)
{
	if (MathTools::Intersect(*this, otherSphere))
	{
		CollisionComponentAttorney::CVControl::Collision(thisComponent, otherComponent, otherSphere);
		CollisionComponentAttorney::CVControl::Collision(otherComponent, thisComponent, *this);
		return true;
	}
	else
	{
		return false;
	}
}

bool CV_Sphere::CollideVisit(CollisionComponent & thisComponent, CollisionComponent & otherComponent, CV_AABB & otherAABB)
{
	if (MathTools::Intersect(*this, otherAABB))
	{
		CollisionComponentAttorney::CVControl::Collision(thisComponent, otherComponent, otherAABB);
		CollisionComponentAttorney::CVControl::Collision(otherComponent, thisComponent, *this);
		return true;
	}
	else
	{
		return false;
	}
}

bool CV_Sphere::CollideVisit(CollisionComponent & thisComponent, CollisionComponent & otherComponent, CV_OBB & otherOBB)
{
	if (MathTools::Intersect(*this, otherOBB))
	{
		CollisionComponentAttorney::CVControl::Collision(thisComponent, otherComponent, otherOBB);
		CollisionComponentAttorney::CVControl::Collision(otherComponent, thisComponent, *this);
		return true;
	}
	else
	{
		return false;
	}
}

void CV_Sphere::SetWorld(const Matrix4F& worldMatrix)
{
	center = worldMatrix.V3();
	radius = worldMatrix.V0().Mag();
}

const Vector4F& CV_Sphere::GetCenter() const
{
	return center;
}

const float& CV_Sphere::GetRadius() const
{
	return radius;
}

void CV_Sphere::Sanitize()
{
	center = Vector4F(0.0f, 0.0f, 0.0f, 1.0f);
	radius = 1.0f;
}

void CV_Sphere::Release(CollisionManager & collisionManager)
{
	Sanitize();
	collisionManager.ReleaseSphere(*this);
}
