#include "CV_BoundingBox.h"

const Vector4F & CV_BoundingBox::GetCornerMin() const
{
	return cornerMin;
}

const Vector4F & CV_BoundingBox::GetCornerMax() const
{
	return cornerMax;
}

const Vector4F & CV_BoundingBox::GetScale() const
{
	return scale;
}

const Vector4F & CV_BoundingBox::GetHalfDiagonal() const
{
	return halfDiagonal;
}

const Vector4F & CV_BoundingBox::GetCenter() const
{
	return center;
}

const Matrix4F & CV_BoundingBox::GetWorldMatrix() const
{
	return world;
}

void CV_BoundingBox::ComputeCenter()
{
	center = (cornerMax + cornerMin) * 0.5f;
}

void CV_BoundingBox::ComputeScale()
{
	scale = cornerMax - cornerMin;
}

void CV_BoundingBox::ComputeHalfDiagonal()
{
	halfDiagonal = (cornerMax - cornerMin) * 0.5f;
}

void CV_BoundingBox::Sanitize()
{
	world = Matrix4F();

	cornerMax = Vector4F();
	cornerMin = Vector4F();

	halfDiagonal = Vector4F();
	center = Vector4F();
	scale = Vector4F();
}