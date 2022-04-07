#include "MathTools.h"

#include "../Scene Components/Collision/CollisionComponent.h"
#include "../Scene Components/Collision/Volumes/CV_Plane.h"
#include "../Scene Components/Collision/Volumes/CV_Sphere.h"
#include "../Scene Components/Collision/Volumes/CV_AABB.h"
#include "../Scene Components/Collision/Volumes/CV_OBB.h"

#include "../Tools/Colors.h"

#include "../Math/Vector/Vector4F.h"
#include "../Math/Matrix/Matrix4F.h"

#include <limits>

//bool MathTools::Intersect(CollisionComponent& thisComponent, CollisionVolume& thisVolume, CollisionComponent& otherComponent, CollisionVolume& otherVolume)
//{
//	return thisVolume.CollideAccept(thisComponent, otherComponent, otherVolume);
//}

//Compute this intersection using the magnitude squared trick to avoid using a square root
bool MathTools::Intersect(const CV_Sphere& sphere1, const CV_Sphere& sphere2)
{
	bool flag = false;

	float sumOfRadii = sphere1.GetRadius() + sphere2.GetRadius();
	//Check Collision
	if (sumOfRadii * sumOfRadii
		> DistanceBetweenTwoPointsSquared(sphere1.GetCenter(), sphere2.GetCenter()))
	{
		flag = true;
	}

	return flag;
}

bool MathTools::Intersect(const CV_Sphere& sphere1, const CV_Plane& plane1)
{
	bool flag = false;

	//Check Collision
	Vector4F tempVector = sphere1.GetCenter() - plane1.GetOrigin();
	Vector4F tempVector2 = plane1.GetNormal();

	float radiusSquared = sphere1.GetRadius() * sphere1.GetRadius();

	float distanceSqr = tempVector.Dot(plane1.GetNormal());
	distanceSqr *= distanceSqr;
	
	if (distanceSqr < radiusSquared)
	{

		//tempVector.M

		flag = true;
	}

	return flag;
}

bool MathTools::Intersect(const CV_Sphere & sphere1, const CV_AABB & volumeAABB2)
{
	bool flag = false;
	
	Vector4F clampedPoint = sphere1.GetCenter();
	clampedPoint = Clamp(clampedPoint, volumeAABB2.GetCornerMin(), volumeAABB2.GetCornerMax());
	
	if (sphere1.GetRadius() * sphere1.GetRadius()
		> DistanceBetweenTwoPointsSquared(sphere1.GetCenter(), clampedPoint))
	{
		flag = true;
	}
	
	return flag;
}

bool MathTools::Intersect(const CV_Sphere & sphere1, const CV_OBB & volumeOBB2)
{
	bool flag = false;

	Vector4F clampedPoint = sphere1.GetCenter();
	clampedPoint *= volumeOBB2.GetWorldMatrix().InverseCopy(); //Put clampedPoint in OBB local space

	clampedPoint = Clamp(clampedPoint, volumeOBB2.GetCornerMin(), volumeOBB2.GetCornerMax());
	clampedPoint *= volumeOBB2.GetWorldMatrix(); //Put clampedPoint in world space

	if (sphere1.GetRadius() * sphere1.GetRadius()
		> DistanceBetweenTwoPointsSquared(sphere1.GetCenter(), clampedPoint))
	{
		flag = true;
	}

	return flag;
}

bool MathTools::Intersect(const CV_Plane& plane1, const CV_Plane& plane2)
{
	bool flag = false;

	//TODO NEEDS IMPLEMENTATION

	return flag;
}

bool MathTools::Intersect(const CV_Plane & plane1, const CV_AABB & volumeAABB2)
{
	bool flag = false;

	//TODO NEEDS IMPLEMENTATION

	return flag;
}

bool MathTools::Intersect(const CV_Plane & plane1, const CV_OBB & volumeOBB2)
{
	bool flag = false;

	//TODO NEEDS IMPLEMENTATION

	return flag;
}

bool MathTools::Intersect(const CV_AABB & volumeAABB1, const CV_AABB & volumeAABB2)
{
	bool flag = false;

	if (IntervalOverlap(volumeAABB1.GetCornerMin(), volumeAABB1.GetCornerMax(),
		volumeAABB2.GetCornerMin(), volumeAABB2.GetCornerMax()))
	{
		flag = true;
	}

	return flag;
}

bool MathTools::Intersect(const CV_AABB & volumeAABB1, const CV_OBB & volumeOBB2)
{
	bool flag = false;

	float scale1 = 1.0f; //The scale is already accounted for in the min and max values
	float scale2 = volumeOBB2.GetWorldMatrix().V2().Mag();
	scale2 *= scale2;
	
	Vector4F center1 = volumeAABB1.GetCenter(); //This is already in world scale
	Vector4F center2 = volumeOBB2.GetCenter() * volumeOBB2.GetWorldMatrix();
	
	//This is me testing if the visualizer can work
	//Visualizer::ShowLineBetweenPoints(center1, center2, Color::Black);
	
	if (DetectOverlapOnAllVectors(volumeAABB1.GetWorldMatrix(), center1, volumeAABB1.GetHalfDiagonal(), scale1, volumeOBB2.GetWorldMatrix(), center2, volumeOBB2.GetHalfDiagonal(), scale2))
	{
		flag = true;
	}

	return flag;
}

bool MathTools::Intersect(const CV_OBB & volumeOBB1, const CV_OBB & volumeOBB2)
{
	bool flag = false;

	float scale1 = volumeOBB1.GetWorldMatrix().V2().Mag();
	scale1 *= scale1;
	float scale2 = volumeOBB2.GetWorldMatrix().V2().Mag();
	scale2 *= scale2;

	Vector4F center1 = volumeOBB1.GetCenter() * volumeOBB1.GetWorldMatrix();
	Vector4F center2 = volumeOBB2.GetCenter() * volumeOBB2.GetWorldMatrix();

	//Visualizer::ShowLineBetweenPoints(center1, center2, Color::Black);

	if (DetectOverlapOnAllVectors(volumeOBB1.GetWorldMatrix(), center1, volumeOBB1.GetHalfDiagonal(), scale1, volumeOBB2.GetWorldMatrix(), center2, volumeOBB2.GetHalfDiagonal(), scale2))
	{
		flag = true;
	}

	return flag;
}


bool MathTools::DetectOverlapOnAllVectors(const Matrix4F& world1, const Vector4F& center1WorldSpace, const Vector4F& halfDiagonal1LocalSpace, const float& scale1, const Matrix4F& world2, const Vector4F& center2WorldSpace, const Vector4F& halfDiagonal2LocalSpace, const float& scale2)
{
	bool flag = false;

	if (DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V0())
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V1())
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V2())
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world2.V0())
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world2.V1())
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world2.V2())
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V0().Cross(world2.V0()))
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V0().Cross(world2.V1()))
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V0().Cross(world2.V2()))
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V1().Cross(world2.V0()))
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V1().Cross(world2.V1()))
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V1().Cross(world2.V2()))
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V2().Cross(world2.V0()))
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V2().Cross(world2.V1()))
		&& DetectOverlapOnVector(world1, center1WorldSpace, halfDiagonal1LocalSpace, scale1, world2, center2WorldSpace, halfDiagonal2LocalSpace, scale2, world1.V2().Cross(world2.V2()))
		)
	{
		flag = true;
	}

	return flag;
}

float MathTools::ProjectionMaximumInLocalSpace(const Matrix4F& world, const Vector4F& halfDiagonal, const float& scale, const Vector4F& Vector4ForToCheck)
{
	Vector4F vPrime = Vector4ForToCheck * world.InverseCopy();

	return scale * (abs(vPrime.X() * halfDiagonal.X()) +
		abs(vPrime.Y() * halfDiagonal.Y()) +
		abs(vPrime.Z() * halfDiagonal.Z()))
		/ Vector4ForToCheck.Mag();
}

float MathTools::LengthOfProjectionInWorldSpace(const Vector4F& C1, const Vector4F& C2, const Vector4F& Vector4ForToCheck)
{
	return abs((C2 - C1).Dot(Vector4ForToCheck)) / Vector4ForToCheck.Mag();
}

bool MathTools::DetectOverlapOnVector(const Matrix4F& world1, const Vector4F& center1WorldSpace, const Vector4F& halfDiagonal1LocalSpace, const float& scale1, const Matrix4F& world2, const Vector4F& center2WorldSpace, const Vector4F& halfDiagonal2LocalSpace, const float& scale2, const Vector4F& Vector4ForToCheck)
{
	bool flag = false;

	if (Vector4ForToCheck.MagSqr() <= FLT_EPSILON) //Protect against division by zero issues
	{
		flag = true;
	}
	else
	{
		if (LengthOfProjectionInWorldSpace(center1WorldSpace, center2WorldSpace, Vector4ForToCheck) <=
			ProjectionMaximumInLocalSpace(world1, halfDiagonal1LocalSpace, scale1, Vector4ForToCheck) +
			ProjectionMaximumInLocalSpace(world2, halfDiagonal2LocalSpace, scale2, Vector4ForToCheck))
		{
			flag = true;
		}
	}

	return flag;
}

int MathTools::AbsoluteValue(const int& value)
{
	if (value < 0)
	{
		return value * -1;
	}
	else
	{
		return value;
	}
}

float MathTools::AbsoluteValue(const float& value)
{
	if (value < 0.0f)
	{
		return value * -1.0f;
	}
	else
	{
		return value;
	}
}

Vector4F MathTools::AbsoluteValue(const Vector4F& Vector)
{
	return Vector4F(AbsoluteValue(Vector.X()), AbsoluteValue(Vector.Y()), AbsoluteValue(Vector.Z()));
}

float MathTools::DistanceBetweenTwoPointsSquared(const Vector4F& pointA, const Vector4F& pointB)
{
	return (pointB - pointA).MagSqr();
}

float MathTools::DistanceBetweenTwoPointsSquared(const float& x1, const float& z1, const float& x2, const float& z2)
{
	float xDist = (x2 - x1);
	float zDist = (z2 - z1);

	return (xDist * xDist) + (zDist * zDist);
}

float MathTools::DistanceBetweenTwoPoints(const Vector4F& pointA, const Vector4F& pointB)
{
	return (pointB - pointA).Mag();
}

float MathTools::RandomFloat(const float& maxValueExclusive)
{
	assert(maxValueExclusive >= 0.0f);

	return maxValueExclusive * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}

float MathTools::RandomFloat(const float& minValueInclusive, const float& maxValueExclusive)
{
	assert(minValueInclusive >= 0.0f);
	assert(maxValueExclusive > minValueInclusive);
	
	return minValueInclusive + (maxValueExclusive - minValueInclusive) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}

float MathTools::RandomFloatIncludingNegatives(const float & minValueInclusive, const float & maxValueExclusive)
{
	assert(maxValueExclusive > minValueInclusive);

	return maxValueExclusive - RandomFloat(maxValueExclusive - minValueInclusive);
}

int MathTools::RandomInt(const int& maxValueExclusive)
{
	assert(maxValueExclusive > 0);

	return rand() % maxValueExclusive;
}

int MathTools::RandomInt(const int& minValueInclusive, const int& maxValueExclusive)
{
	assert(minValueInclusive >= 0);
	assert(maxValueExclusive > minValueInclusive);
	
	return minValueInclusive + ((rand() % maxValueExclusive) - minValueInclusive);
}

bool MathTools::IntervalOverlap(const float& interval1Min, const float& interval1Max, const float& interval2Min, const float& interval2Max)
{
	bool flag = false;

	if (interval1Max < interval2Min || interval2Max < interval1Min)
	{
		flag = true;
	}

	return flag;
}

bool MathTools::IntervalOverlap(const Vector4F& interval1Min, const Vector4F& interval1Max, const Vector4F& interval2Min, const Vector4F& interval2Max)
{
	bool flag = false;

	if (IntervalOverlap(interval1Min.X(), interval1Max.X(), interval2Min.X(), interval2Max.X())
		&& IntervalOverlap(interval1Min.Y(), interval1Max.Y(), interval2Min.Y(), interval2Max.Y())
		&& IntervalOverlap(interval1Min.Z(), interval1Max.Z(), interval2Min.Z(), interval2Max.Z()))
	{
		flag = true;
	}

	return flag;
}

bool MathTools::isPointInRange(const float& min, const float& max, const float& point)
{
	bool flag = false;

	if (point >= min && point <= max)
	{
		flag = true;
	}

	return flag;
}

bool MathTools::isPointInRange(const float& xMin, const float& xMax, const float& yMin, const float& yMax, const float& pointX, const float& pointY)
{
	bool flag = false;

	if (isPointInRange(xMin, xMax, pointX) && isPointInRange(yMin, yMax, pointY))
	{
		flag = true;
	}

	return flag;
}

float MathTools::Clamp(const float& valueToBeClamped, const float& minValue, const float& maxValue)
{
	if (valueToBeClamped < minValue)
	{
		return minValue;
	}
	else if (valueToBeClamped > maxValue)
	{
		return maxValue;
	}
	else
	{
		return valueToBeClamped;
	}
}

bool MathTools::TryClamp(float& outValueToBeClamped, const float& minValue, const float& maxValue)
{
	if (outValueToBeClamped < minValue)
	{
		outValueToBeClamped = minValue;
		return true;
	}
	else if (outValueToBeClamped > maxValue)
	{
		outValueToBeClamped = maxValue;
		return true;
	}
	else
	{
		return false;
	}
}

Vector4F MathTools::Clamp(const Vector4F& pointToBeClamped, const Vector4F& minValues, const Vector4F& maxValues)
{
	return Vector4F(Clamp(pointToBeClamped.X(), minValues.X(), maxValues.X()),
		Clamp(pointToBeClamped.Y(), minValues.Y(), maxValues.Y()),
		Clamp(pointToBeClamped.Z(), minValues.Z(), maxValues.Z()), 1.0f);
}

bool MathTools::TryClamp(Vector4F& outPointToBeClamped, const Vector4F& minValues, const Vector4F& maxValues)
{
	bool flag = false;

	flag |= TryClamp(outPointToBeClamped.X(), minValues.X(), maxValues.X());
	flag |= TryClamp(outPointToBeClamped.Y(), minValues.Y(), maxValues.Y());
	flag |= TryClamp(outPointToBeClamped.Z(), minValues.Z(), maxValues.Z());

	return flag;
}

float MathTools::MaxValue(const float& valueA, const float& valueB)
{
	if (valueA > valueB)
	{
		return valueA;
	}
	else
	{
		return valueB;
	}
}

Vector4F MathTools::MaxValues(const Vector4F& valueA, const Vector4F& valueB)
{
	return Vector4F(MaxValue(valueA.X(), valueB.X()), MaxValue(valueA.Y(), valueB.Y()), MaxValue(valueA.Z(), valueB.Z()));
}

Vector4F MathTools::MaxValues(const CV_Sphere& sphere)
{
	return Vector4F(sphere.GetCenter().X() + sphere.GetRadius(),
		sphere.GetCenter().Y() + sphere.GetRadius(),
		sphere.GetCenter().Z() + sphere.GetRadius());
}

float MathTools::MinValue(const float& valueA, const float& valueB)
{
	if (valueA < valueB)
	{
		return valueA;
	}
	else
	{
		return valueB;
	}
}

Vector4F MathTools::MinValues(const Vector4F& valueA, const Vector4F& valueB)
{
	return Vector4F(MinValue(valueA.X(), valueB.X()), MinValue(valueA.Y(), valueB.Y()), MinValue(valueA.Z(), valueB.Z()));
}

Vector4F MathTools::MinValues(const CV_Sphere& sphere)
{
	return Vector4F(sphere.GetCenter().X() - sphere.GetRadius(),
		sphere.GetCenter().Y() - sphere.GetRadius(),
		sphere.GetCenter().Z() - sphere.GetRadius());
}
