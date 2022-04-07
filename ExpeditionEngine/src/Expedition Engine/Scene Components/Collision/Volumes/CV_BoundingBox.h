#pragma once

#include "CollisionVolume.h"

#include "../../../Math/Matrix/Matrix4F.h"
//Inherits Vector4F from CollisionVolume

class CV_BoundingBox : public CollisionVolume
{
public:
	CV_BoundingBox() = default;
	CV_BoundingBox(const CV_BoundingBox&) = delete;
	CV_BoundingBox& operator= (const CV_BoundingBox&) = delete;
	virtual ~CV_BoundingBox() = default;


	const Vector4F& GetCornerMin() const;
	const Vector4F& GetCornerMax() const;


	const Vector4F& GetHalfDiagonal() const;
	const Vector4F& GetCenter() const;
	const Vector4F& GetScale() const;


	const Matrix4F& GetWorldMatrix() const;

	void ComputeCenter();
	void ComputeScale();
	void ComputeHalfDiagonal();

	void Sanitize();

protected:
	//World Space
	Matrix4F world;

	//Depends
	Vector4F cornerMax;
	Vector4F cornerMin;

	//Local Space
	Vector4F halfDiagonal;
	Vector4F center;
	Vector4F scale;
};