
#include "Vector4S.h"
#include "../Matrix/Matrix4S.h"

#include <utility>
#include <assert.h>

//========
// Big 6
//========

Vector4S::Vector4S()
	: v0( _mm_set1_epi32( 0 ) )
{

}

Vector4S::Vector4S( const __m128i& inV )
	: v0( inV )
{

}

Vector4S::Vector4S( const S32 inX, const S32 inY, const S32 inZ, const S32 inW )
	: v0( _mm_set_epi32( inW, inZ, inY, inX ) )
{

}

Vector4S::Vector4S( const Vector4S& inV )
	: v0( inV.v0 )
{

}

Vector4S::Vector4S( Vector4S&& inV ) noexcept
	: v0( std::move( inV.v0 ) )
{

}

void Vector4S::operator = ( const Vector4S& inV )
{
	v0 = inV.v0;
}

void Vector4S::operator = ( Vector4S&& inV ) noexcept
{
	v0 = std::move( inV.v0 );
}


//================
// Vect * Matrix
//================

const Vector4S Vector4S::operator * ( const Matrix4S& rInM ) const
{
	const __m128i column0 = _mm_set_epi32( rInM[f0], rInM[f4], rInM[f8], rInM[f12] );
	const __m128i column1 = _mm_set_epi32( rInM[f1], rInM[f5], rInM[f9], rInM[f13] );;
	const __m128i column2 = _mm_set_epi32( rInM[f2], rInM[f6], rInM[f10], rInM[f14] );;
	const __m128i column3 = _mm_set_epi32( rInM[f3], rInM[f7], rInM[f11], rInM[f15] );;

	return *this;

	// TODO // Dougherty
	// This intrinsic doesn't exist for __m128i
	// return Vector4S( _mm_dp_epi32( v0, column0, 0xFE ).m128_f32[3],
	// 				 _mm_dp_epi32( v0, column1, 0xFE ).m128_f32[3],
	// 				 _mm_dp_epi32( v0, column2, 0xFE ).m128_f32[3],
	// 				 _mm_dp_epi32( v0, column3, 0xFE ).m128_f32[3] );
}

void Vector4S::operator *= ( const Matrix4S& rInM )
{
	const __m128i column0 = _mm_set_epi32( rInM[f0], rInM[f4], rInM[f8], rInM[f12] );
	const __m128i column1 = _mm_set_epi32( rInM[f1], rInM[f5], rInM[f9], rInM[f13] );
	const __m128i column2 = _mm_set_epi32( rInM[f2], rInM[f6], rInM[f10], rInM[f14] );
	const __m128i column3 = _mm_set_epi32( rInM[f3], rInM[f7], rInM[f11], rInM[f15] );

	// TODO // Dougherty
// This intrinsic doesn't exist for __m128i
	// x = _mm_dp_epi32( v0, column0, 0xFE ).m128_f32[3];
	// y = _mm_dp_epi32( v0, column1, 0xFE ).m128_f32[3];
	// z = _mm_dp_epi32( v0, column2, 0xFE ).m128_f32[3];
	// w = _mm_dp_epi32( v0, column3, 0xFE ).m128_f32[3];
}


//===================
// Vector functions
//===================

void Vector4S::Norm()
{
	//v0 = _mm_div_epi32( v0, _mm_set1_epi32( (S32) Mag() ) );
}

Vector4S Vector4S::NormCopy() const
{
	return _mm_mul_epi32( v0, _mm_set1_epi32( (S32)Mag() ) );
}

S32 Vector4S::Dot( const Vector4S& rInV ) const
{
	// TODO // Dougherty
	// This intrinsic doesn't exist for __m128i
	// return _mm_dp_epi32( v0, rInV.v0, 0xFE ).m128_f32[3];
	return 0;
}

FLOAT Vector4S::Mag() const
{
	return sqrtf( MagSqr() );
}

FLOAT Vector4S::MagSqr() const
{
	// TODO // Dougherty
	// These intrinsic doesn't exist for __m128i
	// __m128i shuf = _mm_movehdup_epi32( v0 );
	// __m128i sums = _mm_add_epi32( v0, shuf );
	// 
	// shuf = _mm_movehl_epi32( shuf, sums );
	// sums = _mm_add_ss( sums, shuf );
	// 
	// return _mm_cvtss_f32( sums );

	return 0;
}

const Vector4S Vector4S::Cross( const Vector4S& rInVect ) const
{
	constexpr U32 shuf = _MM_SHUFFLE( 3, 0, 2, 1 );

	__m128i result = _mm_sub_epi32( _mm_mul_epi32( rInVect.v0, _mm_shuffle_epi32( v0, shuf ) ),
					 _mm_mul_epi32( v0, _mm_shuffle_epi32( rInVect.v0, shuf ) ) );

	return _mm_shuffle_epi32( result, shuf );
}


//=========
// Setters
//=========

void Vector4S::Set( const S32 inX, const S32 inY, const S32 inZ, const S32 inW )
{
	v0 = _mm_set_epi32( inW, inZ, inY, inX );
}

void Vector4S::Set( const Vector4S& rInV )
{
	v0 = rInV.v0;
}

// --- End of File --- //