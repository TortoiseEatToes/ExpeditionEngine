#include "Math.h"
#include "./../Math/Vector/Vector4F.h"


Vector4F Math::GetMaxCombinedVector4F(const Vector4F& a, const Vector4F& b) {
	return Vector4F(GetMax(a.X(), b.X()), GetMax(a.Y(), b.Y()), GetMax(a.Z(), b.Z()));
}

Vector4F Math::GetMinCombinedVector4F(const Vector4F& a, const Vector4F& b) {
	return Vector4F(GetMin(a.X(), b.X()), GetMin(a.Y(), b.Y()), GetMin(a.Z(), b.Z()));
}

float Math::GetMax(const float& a, const float& b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

float Math::GetMin(const float& a, const float& b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

Vector4F Math::GetCenter(const Vector4F& a, const Vector4F& b) {
	return Vector4F(a.X() + b.X(), a.Y() + b.Y(), a.Z() + b.Z())*.5f;
}

bool Math::CheckIntervalOverlap(const float& Max1, const float& Min1, const float& Max2, const float& Min2) {
	return !(Min1 > Max2 || Max1 < Min2);
}

bool Math::ClampVector4F(Vector4F& vClamp, const Vector4F& vMax, const Vector4F& vMin) {

	bool b1 = ClampFloat(vClamp.X(), vMax.X(), vMin.X());
	bool b2 = ClampFloat(vClamp.Y(), vMax.Y(), vMin.Y());
	bool b3 = ClampFloat(vClamp.Z(), vMax.Z(), vMin.Z());

	return b1 || b2 || b3;

}

bool Math::ClampFloat(float& clamp, const float& max, const float& min) {

	if (clamp > max) {
		clamp = max;
		return true;
	}
	else if (clamp < min) {
		clamp = min;
		return true;
	}
	else {
		return false;
	}


}

bool Math::ClampInt(int& clamp, const int& max, const int& min) {

	if (clamp > max) {
		clamp = max;
		return true;
	}
	else if (clamp < min) {
		clamp = min;
		return true;
	}
	else {
		return false;
	}
}

float Math::DistBetweenVectsSqr(const Vector4F& A, const Vector4F& B) {
	return (A - B).MagSqr();
}