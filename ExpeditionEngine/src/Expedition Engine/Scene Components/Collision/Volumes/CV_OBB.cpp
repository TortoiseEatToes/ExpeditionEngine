#include "CV_OBB.h"

#include "../CollisionComponentAttorney.h"
#include "../../../Math/MathTools.h"
#include "../Manager/CollisionManager.h"

bool CV_OBB::CollideAccept(CollisionComponent & thisComponent, CollisionComponent & otherComponent, CollisionVolume & otherVolume)
{
	return otherVolume.CollideVisit(otherComponent, thisComponent, *this);
}

bool CV_OBB::CollideVisit(CollisionComponent & thisComponent, CollisionComponent & otherComponent, CV_Plane & otherPlane)
{
	if (MathTools::Intersect(otherPlane, *this))
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

bool CV_OBB::CollideVisit(CollisionComponent & thisComponent, CollisionComponent & otherComponent, CV_Sphere & otherSphere)
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

bool CV_OBB::CollideVisit(CollisionComponent & thisComponent, CollisionComponent & otherComponent, CV_AABB & otherAABB)
{
	if (MathTools::Intersect(otherAABB, *this))
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

bool CV_OBB::CollideVisit(CollisionComponent & thisComponent, CollisionComponent & otherComponent, CV_OBB & otherOBB)
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

void CV_OBB::SetPosition(const Vector4F & min, const Vector4F & max)
{
}

void CV_OBB::SetWorld(const Matrix4F & worldMatrix)
{
}

void CV_OBB::Release(CollisionManager & collisionManager)
{
	Sanitize();
	collisionManager.ReleaseOBB(*this);
}