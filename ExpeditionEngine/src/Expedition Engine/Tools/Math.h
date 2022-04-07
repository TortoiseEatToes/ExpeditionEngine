#pragma once

class Vector4F;

////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// \ingroup Utility
///
/// \par Math Tools
/// These math tools are primarily made to help the engine, but you are more than welcome to use any of them that may come in handy.
////////////////////////////////////////////////////////////////////////////////////////////////////

class Math
{
public:

		///Finds the max x,y, and z values of the two vects and returns a Vector4F with those max values
	static Vector4F GetMaxCombinedVector4F(const Vector4F& a, const Vector4F& b);

	///Finds the min x,y, and z values of the two vects and returns a Vector4F with those min values
	static Vector4F GetMinCombinedVector4F(const Vector4F& a, const Vector4F& b);

	static float GetMax(const float& a, const float& b);
	static float GetMin(const float& a, const float& b);

	static Vector4F GetCenter(const Vector4F& a, const Vector4F& b);

	static bool CheckIntervalOverlap(const float& Max1, const float& Min1, const float& Max2, const float& Min2);

	/// if clamp is already inside range, returns false, other wise returns true and clamps
	static bool ClampVector4F(Vector4F& vClamp, const Vector4F& vMax, const Vector4F& vMin);
	static bool ClampFloat(float& clamp, const float& max, const float& min);
	static bool ClampInt(int& clamp, const int& max, const int& min);

	static float DistBetweenVectsSqr(const Vector4F& A, const Vector4F& B);


};