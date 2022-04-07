
#include "Matrix4S.h"

#include <utility>
#include <assert.h>

//=======
// Big 6
//=======
Matrix4S::Matrix4S()
	:	m0( _mm256_set1_epi32( 0 ) )
	,	m1( _mm256_set1_epi32( 0 ) )
{

}

Matrix4S::Matrix4S( const S32 inF0, const S32 inF1, const S32 inF2, const S32 inF3,
					const S32 inF4, const S32 inF5, const S32 inF6, const S32 inF7,
					const S32 inF8, const S32 inF9, const S32 inF10, const S32 inF11,
					const S32 inF12, const S32 inF13, const S32 inF14, const S32 inF15 )
	:	m0( _mm256_set_epi32( inF7, inF6, inF5, inF4,
							  inF3, inF2, inF1, inF0 ) )	
	,	m1( _mm256_set_epi32( inF15, inF14, inF13, inF12,
							  inF11, inF10, inF9, inF8 ) )
{

}

Matrix4S::Matrix4S( const Vector4S& rInV0, const Vector4S& rInV1, const Vector4S& rInV2, const Vector4S& rInV3 )
	:	v0( rInV0 )
	,	v1( rInV1 )
	,	v2( rInV2 )
	,	v3( rInV3 )
{
	UNUSEDVAR( m0 );
	UNUSEDVAR( m1 );
}

Matrix4S::Matrix4S( const __m128i& rInV0, const __m128i& rInV1, const __m128i& rInV2, const __m128i& rInV3 )
	:	v0( rInV0 )
	,	v1( rInV1 )
	,	v2( rInV2 )
	,	v3( rInV3 )
{
	UNUSEDVAR( m0 );
	UNUSEDVAR( m1 );
}

Matrix4S::Matrix4S( const __m256i& rInM0, const __m256i& rInM1 )
	:	m0( rInM0 )
	,	m1( rInM1 )
{

}

Matrix4S::Matrix4S( const RotType_X axis, const Vector4S& rInV )
	:	v0( rInV )
	,	v1( 0, 1, 0, 0 )
	,	v2( 0, 0, 1, 0 )
	,	v3( 0, 0, 0, 1 )
{
	// TODO // Test
	// :	m0( _mm512_set_epi32( rInV.x, rInV.y, rInV.z, rInV.w,
	//						   0, 1, 0, 0,
	//						   0, 0, 1, 0,
	//						   0, 0, 0, 1 ) )
}

Matrix4S::Matrix4S( const RotType_Y axis, const Vector4S& rInV )
	:	v0( 1, 0, 0, 0 )
	,	v1( rInV )
	,	v2( 0, 0, 1, 0 )
	,	v3( 0, 0, 0, 1 )
{
	// TODO // Test
	// :	m0( _mm512_set_epi32( 1, 0, 0, 0,
	// 						   rInV.x, rInV.y, rInV.z, rInV.w,
	// 						   0, 0, 1, 0,
	// 						   0, 0, 0, 1 ) )
}

Matrix4S::Matrix4S( const RotType_Z axis, const Vector4S& rInV )
	:	v0( 1, 0, 0, 0 )
	,	v1( 0, 1, 0, 0 )
	,	v2( rInV )
	,	v3( 0, 0, 0, 1 )
{
	// TODO // Test
	// :	m0( _mm512_set_epi32( 1, 0, 0, 0,
	// 						   0, 1, 0, 0,
	// 						   rInV.x, rInV.y, rInV.z, rInV.w,
	// 						   0, 0, 0, 1 ) )
}

Matrix4S::Matrix4S( const TransType type, const Vector4S& rInV )
	:	v0( 1, 0, 0, 0 )
	,	v1( 0, 1, 0, 0 )
	,	v2( 0, 0, 1, 0 )
	,	v3( rInV )
{
	// TODO // Test
	// :	m0( _mm512_set_epi32( 1, 0, 0, 0,
	// 						   0, 1, 0, 0,
	// 						   0, 0, 1, 0,
	// 						   rInV.x, rInV.y, rInV.z, rInV.w,) )
}

Matrix4S::Matrix4S( const ScaleType type, const S32 scale )
	:	m0( _mm256_set_epi32( 0, 0, scale, 0,
							  0, 0, 0, scale ) )
	,	m1( _mm256_set_epi32( scale, 0, 0, 0,
							  0, 1, 0, 0 ) )
{

}

Matrix4S::Matrix4S( const SpecialType_Zero type )
	:	m0( _mm256_set1_epi32( 0 ) )
	,	m1( _mm256_set1_epi32( 0 ) )
{

}

Matrix4S::Matrix4S( const SpecialType_Identity type )
	:	m0( _mm256_set_epi32( 0, 0, 1, 0,
							  0, 0, 0, 1 ) )
	,	m1( _mm256_set_epi32( 1, 0, 0, 0,
							  0, 1, 0, 0 ) )
{

}

Matrix4S::Matrix4S( const Rot3AxisType_XYZ axisOrder )
	:	m0( _mm256_set1_epi32( 0 ) )
	,	m1( _mm256_set1_epi32( 0 ) ) 
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4S::Matrix4S( const Rot3AxisType_XZY axisOrder )
	:	m0( _mm256_set1_epi32( 0 ) )
	,	m1( _mm256_set1_epi32( 0 ) ) 
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4S::Matrix4S( const Rot3AxisType_YXZ axisOrder )
	:	m0( _mm256_set1_epi32( 0 ) )
	,	m1( _mm256_set1_epi32( 0 ) )
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4S::Matrix4S( const Rot3AxisType_YZX axisOrder )
	:	m0( _mm256_set1_epi32( 0 ) )
	,	m1( _mm256_set1_epi32( 0 ) ) 
{
	// TODO // DDOUGH
	// not implemented yet
	assert( false );
}

Matrix4S::Matrix4S( const Rot3AxisType_ZXY axisOrder )
	:	m0( _mm256_set1_epi32( 0 ) )
	,	m1( _mm256_set1_epi32( 0 ) ) 
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4S::Matrix4S( const Rot3AxisType_ZYX axisOrder )
	:	m0( _mm256_set1_epi32( 0 ) )
	,	m1( _mm256_set1_epi32( 0 ) )
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4S::Matrix4S( const Matrix4S& rInM )
	:	m0( rInM.m0 )
	,	m1( rInM.m1 )
{

}

Matrix4S::Matrix4S( Matrix4S&& rInM ) noexcept
	:	m0( std::move( rInM.m0 ) )
	,	m1( std::move( rInM.m1 ) )
{

}

void Matrix4S::operator = ( const Matrix4S& rInM )
{
	m0 = rInM.m0;
	m1 = rInM.m1;
}

void Matrix4S::operator = ( Matrix4S&& rInM ) noexcept
{
	m0 = std::move( rInM.m0 );
	m1 = std::move( rInM.m1 );
}

//===================
// Matrix functions
//===================
void Matrix4S::Transpose()
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4S Matrix4S::TransposeCopy()
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
	return *this;
}

void Matrix4S::Inverse()
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4S Matrix4S::InverseCopy()
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
	return *this;
}

// --- End of File --- //