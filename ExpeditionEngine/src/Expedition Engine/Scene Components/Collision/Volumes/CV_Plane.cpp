#include "CV_Plane.h"

#include "CV_Sphere.h"

#include "../../../Math/MathTools.h"
#include "../Manager/CollisionManager.h"

#include "../CollisionComponentAttorney.h"
#include "../../../Math/Matrix/Matrix4F.h"

bool CV_Plane::CollideAccept(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CollisionVolume& otherVolume)
{
	return otherVolume.CollideVisit(otherComponent, thisComponent, *this);
}

bool CV_Plane::CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Plane& otherPlane)
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

bool CV_Plane::CollideVisit(CollisionComponent& thisComponent, CollisionComponent& otherComponent, CV_Sphere& otherSphere)
{
	if (MathTools::Intersect(otherSphere, *this))
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

bool CV_Plane::CollideVisit(CollisionComponent & thisComponent, CollisionComponent & otherComponent, CV_AABB & otherAABB)
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

bool CV_Plane::CollideVisit(CollisionComponent & thisComponent, CollisionComponent & otherComponent, CV_OBB & otherOBB)
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

void CV_Plane::SetWorld(const Matrix4F& worldMatrix)
{
	origin = worldMatrix.V3();
	normal = worldMatrix.V1().NormCopy();
	length = worldMatrix.V0().Mag();
}

const Vector4F& CV_Plane::GetOrigin() const
{
	return origin;
}

const Vector4F& CV_Plane::GetNormal() const
{
	return normal;
}

const float& CV_Plane::GetLength() const
{
	return length;
}

void CV_Plane::Sanitize()
{
	origin = Vector4F(0.0f, 0.0f, 0.0f, 1.0f);
	normal = Vector4F(0.0f, 0.0f, 0.0f, 0.0f);
	length = 1.0f;
}

void CV_Plane::Release(CollisionManager & collisionManager)
{
	Sanitize();
	collisionManager.ReleasePlane(*this);
}