
#include "Vector4F.h"
#include "../Matrix/Matrix4F.h"

#include <utility>
#include <assert.h>

//========
// Big 6
//========

Vector4F::Vector4F()
	:	v0( _mm_set_ps1( 0.0f ) )
{

}

Vector4F::Vector4F( const __m128& inV )
	:	v0( inV )
{

}

Vector4F::Vector4F( const FLOAT inX, const FLOAT inY, const FLOAT inZ, const FLOAT inW )
	:	v0( _mm_set_ps( inW, inZ, inY, inX ) )
{

}

Vector4F::Vector4F( const Vector4F& inV )
	:	v0( inV.v0 )
{

}

Vector4F::Vector4F( Vector4F&& inV ) noexcept
	:	v0( std::move( inV.v0 ) )
{

}

void Vector4F::operator = ( const Vector4F& inV )
{
	v0 = inV.v0;
}

void Vector4F::operator = ( Vector4F&& inV ) noexcept
{
	v0 = std::move( inV.v0 );
}

void Vector4F::operator *= (const Vector4F& inVect) {
	this->x *= inVect.x;
	this->y *= inVect.y;
	this->z *= inVect.z;
	this->w *= inVect.w;
}

Vector4F Vector4F::operator * (const Vector4F& inVect) {
	return Vector4F(this->x *= inVect.x,
		this->y *= inVect.y,
		this->z *= inVect.z,
		this->w *= inVect.w);
}

//================
// Vect * Matrix
//================

const Vector4F Vector4F::operator * ( const Matrix4F& rInM ) const
{
	const __m128 column0 = _mm_set_ps( rInM[f0], rInM[f4], rInM[f8], rInM[f12] );
	const __m128 column1 = _mm_set_ps( rInM[f1], rInM[f5], rInM[f9], rInM[f13] );;
	const __m128 column2 = _mm_set_ps( rInM[f2], rInM[f6], rInM[f10], rInM[f14] );;
	const __m128 column3 = _mm_set_ps( rInM[f3], rInM[f7], rInM[f11], rInM[f15] );;

	return Vector4F( _mm_dp_ps( v0, column0, 0xFE ).m128_f32[3],
					 _mm_dp_ps( v0, column1, 0xFE ).m128_f32[3],
					 _mm_dp_ps( v0, column2, 0xFE ).m128_f32[3],
					 _mm_dp_ps( v0, column3, 0xFE ).m128_f32[3] );
}

void Vector4F::operator *= ( const Matrix4F& rInM )
{
	const __m128 column0 = _mm_set_ps( rInM[f0], rInM[f4], rInM[f8], rInM[f12] );
	const __m128 column1 = _mm_set_ps( rInM[f1], rInM[f5], rInM[f9], rInM[f13] );
	const __m128 column2 = _mm_set_ps( rInM[f2], rInM[f6], rInM[f10], rInM[f14] );
	const __m128 column3 = _mm_set_ps( rInM[f3], rInM[f7], rInM[f11], rInM[f15] );

	x = _mm_dp_ps( v0, column0, 0xFE ).m128_f32[3];
	y = _mm_dp_ps( v0, column1, 0xFE ).m128_f32[3];
	z = _mm_dp_ps( v0, column2, 0xFE ).m128_f32[3];
	w = _mm_dp_ps( v0, column3, 0xFE ).m128_f32[3];
}


//===================
// Vector functions
//===================

void Vector4F::Norm( )
{
	float mag = Mag();
	*this  = static_cast<Vector4F>(v0) * (1.0f / mag);

	//v0 = _mm_mul_ps( v0, _mm_set_ps1( 1.0f / Mag() ) );
}

Vector4F Vector4F::NormCopy() const
{
	float mag = Mag();
	return this->operator*(1.0f / mag);
	
}

FLOAT Vector4F::Dot( const Vector4F& rInV ) const
{

	//return (x*rInV.x)+(y*rInV.y)+(z*rInV.z)+(w*rInV.w);

	//__m128 test = _mm_dp_ps(v0, rInV.v0, 0xF1);
	//test = _mm_hadd_ps(test, test);
	//test = _mm_hadd_ps(test, test);

	return _mm_dp_ps(v0, rInV.v0, 0xF1).m128_f32[0];
}

FLOAT Vector4F::Mag() const
{
	return sqrtf( MagSqr() );
}

FLOAT Vector4F::MagSqr() const
{
	//Multiply each number by itself
	__m128 individualMultiply = _mm_mul_ps(v0, v0);

	//Now use hadd to summ the value into the 0 index
	individualMultiply = _mm_hadd_ps(individualMultiply, individualMultiply);
	individualMultiply = _mm_hadd_ps(individualMultiply, individualMultiply);

	return individualMultiply.m128_f32[0];
}

const Vector4F Vector4F::Cross( const Vector4F& rInVect ) const
{

	return Vector4F(((y*rInVect.z) - (z*rInVect.y)), (-x * rInVect.z + z * rInVect.x), (x*rInVect.y - y * rInVect.x), 0);

	//constexpr U32 shuf = _MM_SHUFFLE( 3, 0, 2, 1 );
	//
	//__m128 result = _mm_sub_ps( _mm_mul_ps( rInVect.v0, _mm_shuffle_ps( v0, v0, shuf ) ),
	//							_mm_mul_ps( v0, _mm_shuffle_ps( rInVect.v0, rInVect.v0, shuf ) ) );
	//
	//return _mm_shuffle_ps( result, result, shuf );
}

void Vector4F::RotateAxisAngle(const Vector4F& axis, const float& angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Vector4F axisNorm = axis.NormCopy();

	v0 = this->operator*(cos) +(1 - cos) * (this->Dot(axisNorm)) * axisNorm + (axisNorm.Cross(this->v0) * sin);
}

Vector4F Vector4F::RotateAxisAngleCopy(const Vector4F& axis, const float& angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);

	Vector4F axisNorm = axis.NormCopy();

	return (this->operator*(cos) +(1 - cos) * (this->Dot(axisNorm)) * axisNorm + (axisNorm.Cross(this->v0) * sin));
}
//=========
// Setters
//=========

void Vector4F::Set( const FLOAT inX, const FLOAT inY, const FLOAT inZ, const FLOAT inW )
{
	v0 = _mm_set_ps( inW, inZ, inY, inX );
}

void Vector4F::Set( const Vector4F& rInV )
{
	v0 = rInV.v0;
}

// --- End of File --- //