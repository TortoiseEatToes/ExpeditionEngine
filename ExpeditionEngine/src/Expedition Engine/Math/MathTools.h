#pragma once

class CollisionComponent;

class CollisionVolume;
class CV_Sphere;
class CV_Plane;
class CV_AABB;
class CV_OBB;

class Vector4F;
class Matrix4F;


////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// \ingroup Utility
/// 
/// \par Math Tools
/// These math tools are primarily made to help the engine, but you are more than welcome to use any of them that may come in handy.
////////////////////////////////////////////////////////////////////////////////////////////////////

class MathTools
{
public:
	//static bool Intersect(CollisionComponent& thisComponent, CollisionVolume& thisVolume, CollisionComponent& otherComponent, CollisionVolume& otherVolume);

	static bool Intersect(const CV_Sphere& sphere1, const CV_Sphere& sphere2);
	static bool Intersect(const CV_Sphere& sphere1, const CV_Plane& plane1);
	static bool Intersect(const CV_Sphere& sphere1, const CV_AABB& volumeAABB2);
	static bool Intersect(const CV_Sphere& sphere1, const CV_OBB& volumeOBB2);

	static bool Intersect(const CV_Plane& plane1, const CV_Plane& plane2);
	static bool Intersect(const CV_Plane& plane1, const CV_AABB& volumeAABB2);
	static bool Intersect(const CV_Plane& plane1, const CV_OBB& volumeOBB2);

	static bool Intersect(const CV_AABB& volumeAABB1, const CV_AABB& volumeAABB2);
	static bool Intersect(const CV_AABB& volumeAABB1, const CV_OBB& volumeOBB2);

	static bool Intersect(const CV_OBB& volumeOBB1, const CV_OBB& volumeOBB2);

	static bool DetectOverlapOnAllVectors(const Matrix4F& world1, const Vector4F& center1WorldSpace, const Vector4F& halfDiagonal1LocalSpace, const float& scale1, const Matrix4F& world2, const Vector4F& center2WorldSpace, const Vector4F& halfDiagonal2LocalSpace, const float& scale2);
	static bool DetectOverlapOnVector(const Matrix4F& world1, const Vector4F& center1WorldSpace, const Vector4F& halfDiagonal1LocalSpace, const float& scale1, const Matrix4F& world2, const Vector4F& center2WorldSpace, const Vector4F& halfDiagonal2LocalSpace, const float& scale2, const Vector4F& Vector4ForToCheck);
	static float ProjectionMaximumInLocalSpace(const Matrix4F& world, const Vector4F& halfDiagonal, const float& scale, const Vector4F& Vector4ForToCheck);
	static float LengthOfProjectionInWorldSpace(const Vector4F& C1, const Vector4F& C2, const Vector4F& Vector4ForToCheck);

	static float DistanceBetweenTwoPointsSquared(const Vector4F& pointA, const Vector4F& pointB);
	static float DistanceBetweenTwoPointsSquared(const float& x1, const float& z1, const float& x2, const float& z2);

	static bool IntervalOverlap(const float& interval1Min, const float& interval1Max, const float& interval2Min, const float& interval2Max);
	static bool IntervalOverlap(const Vector4F& interval1Min, const Vector4F& interval1Max, const Vector4F& interval2Min, const Vector4F& interval2Max);

	static bool isPointInRange(const float& min, const float& max, const float& point);
	static bool isPointInRange(const float& xMin, const float& xMax, const float& yMin, const float& yMax, const float& pointX, const float& pointY);

	static float Clamp(const float& valueToBeClamped, const float& minValue, const float& maxValue);
	static bool TryClamp(float& outValueToBeClamped, const float& minValue, const float& maxValue);
	static Vector4F Clamp(const Vector4F& pointToBeClamped, const Vector4F& minValues, const Vector4F& maxValues);
	static bool TryClamp(Vector4F& outPointToBeClamped, const Vector4F& minValues, const Vector4F& maxValues);

	static float MaxValue(const float& valueA, const float& valueB);
	static Vector4F MaxValues(const Vector4F& valueA, const Vector4F& valueB);
	static Vector4F MaxValues(const CV_Sphere& sphere);

	static float MinValue(const float& valueA, const float& valueB);
	static Vector4F MinValues(const Vector4F& valueA, const Vector4F& valueB);
	static Vector4F MinValues(const CV_Sphere& sphere);

	static int AbsoluteValue(const int& value);
	static float AbsoluteValue(const float& value);
	static Vector4F AbsoluteValue(const Vector4F& Vector);
	static float DistanceBetweenTwoPoints(const Vector4F& pointA, const Vector4F& pointB);


	/// <summary>Returns a random float value between 0.0f (inclusive) and the max value (exclusive)</summary>
	/// <param name="maxValueExclusive">The max value that can be returned (exclusive)</param>
	/// <returns>float copy of the random value</returns>
	static float RandomFloat(const float& maxValueExclusive);

	/// <summary>Returns a random float value between the min value (inclusive) and the max value (exclusive).  The minimum must be greater than 0.0f</summary>
	/// <param name="minValueExclusive">The min value that can be returned (inclusive)</param>
	/// <param name="maxValueExclusive">The max value that can be returned (exclusive)</param>
	/// <returns>float copy of the random value</returns> 
	static float RandomFloat(const float& minValueInclusive, const float& maxValueExclusive);

	/// <summary>Returns a random float value between the min value (inclusive) and the max value (exclusive).  This function can include negatives.</summary>
	/// <param name="minValueExclusive">The min value that can be returned (inclusive)</param>
	/// <param name="maxValueExclusive">The max value that can be returned (exclusive)</param>
	/// <returns>float copy of the random value</returns> 
	static float RandomFloatIncludingNegatives(const float& minValueInclusive, const float& maxValueExclusive);

	/// <summary>Returns a random integer value between 0 (inclusive) and the max value (exclusive).</summary>
	/// <param name="maxValueExclusive">The max value that can be returned (exclusive)</param>
	/// <returns>int copy of the random value</returns>
	static int RandomInt(const int& minValueInclusive);

	/// <summary>Returns a random integer value between the min value (inclusive) and the max value (exclusive).  The minimum must be greater than 0.</summary>
	/// <param name="minValueExclusive">The min value that can be returned (inclusive)</param>
	/// <param name="maxValueExclusive">The max value that can be returned (exclusive)</param>
	/// <returns>int copy of the random value</returns> 
	static int RandomInt(const int& minValueInclusive, const int& maxValueExclusive);
};