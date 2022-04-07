
#include "Matrix4F.h"

#include <assert.h>

//=======
// Big 6
//=======
Matrix4F::Matrix4F()
	:	m0( _mm256_set1_ps( 0.0f ) )
	,	m1( _mm256_set1_ps( 0.0f ) )
{

}

Matrix4F::Matrix4F( const FLOAT inF0, const FLOAT inF1, const FLOAT inF2, const FLOAT inF3, 
					const FLOAT inF4, const FLOAT inF5, const FLOAT inF6, const FLOAT inF7, 
					const FLOAT inF8, const FLOAT inF9, const FLOAT inF10, const FLOAT inF11,
					const FLOAT inF12, const FLOAT inF13, const FLOAT inF14, const FLOAT inF15 )
	:	m0( _mm256_set_ps( inF7, inF6, inF5, inF4,
						   inF3, inF2, inF1, inF0 ) )
	,	m1( _mm256_set_ps( inF15, inF14, inF13, inF12,
						   inF11, inF10, inF9, inF8 ) )

{

}

Matrix4F::Matrix4F( const Vector4F& rInV0, const Vector4F& rInV1, const Vector4F& rInV2, const Vector4F& rInV3 )
	:	v0( rInV0 )
	,	v1( rInV1 )
	,	v2( rInV2 )
	,	v3( rInV3 )
{
	UNUSEDVAR( m0 );
	UNUSEDVAR( m1 );
}

Matrix4F::Matrix4F( const __m128& rInV0, const __m128& rInV1, const __m128& rInV2, const __m128& rInV3 )
	:	v0( rInV0 )
	,	v1( rInV1 ) 
	,	v2( rInV2 )
	,	v3( rInV3 )
{
	UNUSEDVAR( m0 );
	UNUSEDVAR( m1 );
}

Matrix4F::Matrix4F( const __m256& rInM0, const __m256& rInM1 )
	:	m0( rInM0 )
	,	m1( rInM1 )
{

}

Matrix4F::Matrix4F( const RotType_X axis, const Vector4F& rInV )
	:	v0( rInV )
	,	v1( 0.0f, 1.0f, 0.0f, 0.0f )
	,	v2( 0.0f, 0.0f, 1.0f, 0.0f )
	,	v3( 0.0f, 0.0f, 0.0f, 1.0f )
{

}

Matrix4F::Matrix4F( const RotType_Y axis, const Vector4F& rInV )
	:	v0( 1.0f, 0.0f, 0.0f, 0.0f )
	,	v1( rInV )
	,	v2( 0.0f, 0.0f, 1.0f, 0.0f )
	,	v3( 0.0f, 0.0f, 0.0f, 1.0f )
{

}

Matrix4F::Matrix4F( const RotType_Z axis, const Vector4F& rInV )
	:	v0( 1.0f, 0.0f, 0.0f, 0.0f )
	,	v1( 0.0f, 1.0f, 0.0f, 0.0f )
	,	v2( rInV )
	,	v3( 0.0f, 0.0f, 0.0f, 1.0f )
{
	
}

Matrix4F::Matrix4F(const RotType_AxisAngle type, const Vector4F& axis, const float& angle) {
	
	Vector4F axisNorm = axis.NormCopy();
	
	const float c = cosf(angle);
	const float s = sinf(angle);
	const float t = 1 - c;

	v0 = Vector4F(t * axisNorm.x * axisNorm.x + c, t * axisNorm.x * axisNorm.y + s * axisNorm.z, t * axisNorm.x * axisNorm.z - s * axisNorm.y, 0);
	v1 = Vector4F(t * axisNorm.x * axisNorm.y - s * axisNorm.z, t * axisNorm.y * axisNorm.y + c, t * axisNorm.y * axisNorm.z + s * axisNorm.x, 0);
	v2 = Vector4F(t * axisNorm.x * axisNorm.z + s * axisNorm.y, t * axisNorm.y * axisNorm.z - s * axisNorm.x, t * axisNorm.z * axisNorm.z + c, 0);
	v3 = Vector4F(0, 0, 0, 1);

}


Matrix4F::Matrix4F( const TransType type, const Vector4F& rInV )
	:	v0( 1.0f, 0.0f, 0.0f, 0.0f )
	,	v1( 0.0f, 1.0f, 0.0f, 0.0f )
	,	v2( 0.0f, 0.0f, 1.0f, 0.0f )
	,	v3(rInV)
{

}

Matrix4F::Matrix4F( const ScaleType type, const FLOAT scale )
	:	m0( _mm256_set_ps( 0.0f, 0.0f, scale, 0.0f,
						   0.0f, 0.0f, 0.0f, scale ) )
	,	m1( _mm256_set_ps( 1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, scale, 0.0f, 0.0f ) )
{

}
Matrix4F::Matrix4F(const ScaleType type, const FLOAT scalex, const FLOAT scaley, const FLOAT scalez)
	: m0(_mm256_set_ps(0.0f, 0.0f, scaley, 0.0f,
		0.0f, 0.0f, 0.0f, scalex))
	, m1(_mm256_set_ps(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, scalez, 0.0f, 0.0f))
{

}

Matrix4F::Matrix4F( const SpecialType_Zero type )
	:	m0( _mm256_set1_ps( 0.0f ) )
	,	m1( _mm256_set1_ps( 0.0f ) )
{

}

Matrix4F::Matrix4F( const SpecialType_Identity type )
	:	m0( _mm256_set_ps( 0.0f, 0.0f, 1.0f, 0.0f,
						   0.0f, 0.0f, 0.0f, 1.0f ) )
	,	m1( _mm256_set_ps( 1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f ) )
{

}

Matrix4F::Matrix4F( const Rot3AxisType_XYZ axisOrder )
	:	m0( _mm256_set1_ps( 0.0f ) )
	,	m1( _mm256_set1_ps( 0.0f ) )
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4F::Matrix4F( const Rot3AxisType_XZY axisOrder )
	:	m0( _mm256_set1_ps( 0.0f ) )
	,	m1( _mm256_set1_ps( 0.0f ) )
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4F::Matrix4F( const Rot3AxisType_YXZ axisOrder )
	:	m0( _mm256_set1_ps( 0.0f ) )
	,	m1( _mm256_set1_ps( 0.0f ) )
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4F::Matrix4F( const Rot3AxisType_YZX axisOrder )
	:	m0( _mm256_set1_ps( 0.0f ) )
	,	m1( _mm256_set1_ps( 0.0f ) )
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4F::Matrix4F( const Rot3AxisType_ZXY axisOrder )
	:	m0( _mm256_set1_ps( 0.0f ) )
	,	m1( _mm256_set1_ps( 0.0f ) )
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4F::Matrix4F( const Rot3AxisType_ZYX axisOrder )
	:	m0( _mm256_set1_ps( 0.0f ) )
	,	m1( _mm256_set1_ps( 0.0f ) )
{
	// TODO // DDOUGH
	// not implemented yet;
	assert( false );
}

Matrix4F::Matrix4F( const Matrix4F& rInM )
	:	m0( rInM.m0 )
	,	m1( rInM.m1 )
{

}

Matrix4F::Matrix4F( Matrix4F&& rInM ) noexcept
	:	m0( std::move( rInM.m0 ) )
	,	m1( std::move( rInM.m1 ) )
{

}

void Matrix4F::operator = ( const Matrix4F& rInM )
{
	m0 = rInM.m0;
	m1 = rInM.m1;
}

void Matrix4F::operator = ( Matrix4F&& rInM ) noexcept
{
	m0 = std::move( rInM.m0 );
	m1 = std::move( rInM.m1 );
}

//===================
// Matrix functions
//===================
void Matrix4F::Transpose()
{
	// TODO // DDOUGH
	// Convert this to __m256 instead, but need to look more into how you would shuffle that

	__m128 tmp0, tmp1, tmp2, tmp3;
	tmp0 = _mm_shuffle_ps( v0.v0, v1.v0, 0x88 );
	tmp1 = _mm_shuffle_ps( v0.v0, v1.v0, 0xdd );
	tmp2 = _mm_shuffle_ps( v2.v0, v3.v0, 0x88 );
	tmp3 = _mm_shuffle_ps( v2.v0, v3.v0, 0xdd );

	v0.v0 = _mm_shuffle_ps( tmp0, tmp2, 0x88 );
	v1.v0 = _mm_shuffle_ps( tmp1, tmp3, 0x88 );
	v2.v0 = _mm_shuffle_ps( tmp0, tmp2, 0xdd );
	v3.v0 = _mm_shuffle_ps( tmp1, tmp3, 0xdd );
}

Matrix4F Matrix4F::TransposeCopy() const 
{
	// TODO // DDOUGH
	// Convert this to __m256 instead, but need to look more into how you would shuffle that

	__m128 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
	tmp0 = _mm_shuffle_ps( v0.v0, v1.v0, 0x88 );
	tmp1 = _mm_shuffle_ps( v0.v0, v1.v0, 0xdd );
	tmp2 = _mm_shuffle_ps( v2.v0, v3.v0, 0x88 );
	tmp3 = _mm_shuffle_ps( v2.v0, v3.v0, 0xdd );

	tmp4 = _mm_shuffle_ps( tmp0, tmp2, 0x88 );
	tmp5 = _mm_shuffle_ps( tmp1, tmp3, 0x88 );
	tmp6 = _mm_shuffle_ps( tmp0, tmp2, 0xdd );
	tmp7 = _mm_shuffle_ps( tmp1, tmp3, 0xdd );

	return Matrix4F( tmp4, tmp5, tmp6, tmp7 );
}

void Matrix4F::Inverse()
{
	// TODO // DDOUGH
	// Not yet implemented

	FLOAT determinant = Determinant();

	FLOAT t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	t0 = f5 * f10 * f15 + f9 * f14 * f7 + f13 * f6 * f11 - f13 * f10 * f7 - f9 * f6 * f15 - f5 * f14 * f11;
	t4 = -f4 * f10*f15 - f8 * f14*f7 - f12 * f6*f11 + f12 * f10*f7 + f8 * f6*f15 + f4 * f14*f11;
	t8 = f4 * f9*f15 + f8 * f13*f7 + f12 * f5*f11 - f12 * f9*f7 - f8 * f5*f15 - f4 * f13*f11;
	t12 = -f4 * f9*f14 - f8 * f13*f6 - f8 * f5*f10 + f12 * f9*f6 + f8 * f5*f14 + f4 * f13*f10;

	t1 = -(f1 * f10 * f15) - (f9 * f14 * f3) - (f13 * f2 * f11) + f13 * f10*f3 + f9 * f2*f15 + f1 * f14*f11;
	t5 = f0 * f10*f15 + f8 * f14*f3 + f12 * f2*f11 - f12 * f10*f3 - f8 * f2*f15 - f0 * f14*f11;
	t9 = -f0 * f9*f15 - f8 * f13*f3 - f12 * f1*f11 + f12 * f9*f3 + f8 * f1*f15 + f0 * f13*f11;
	t13 = f0 * f9*f14 + f8 * f13*f2 + f12 * f1*f10 - f12 * f9*f2 - f8 * f1*f14 - f0 * f13*f10;

	t2 = f1 * f6*f15 + f5 * f14*f3 + f13 * f2*f7 - f13 * f6*f3 - f5 * f2*f15 - f1 * f14*f7;
	t6 = -f0 * f6*f15 - f4 * f14*f3 - f12 * f2*f7 + f12 * f6*f3 + f4 * f2*f15 + f0 * f14*f7;
	t10 = f0 * f5*f15 + f4 * f13*f3 + f12 * f1*f7 - f12 * f5*f3 - f4 * f1*f15 - f0 * f13*f7;
	t14 = -f0 * f5*f14 - f4 * f13*f2 - f12 * f1*f6 + f12 * f5*f2 + f4 * f1*f14 + f0 * f13*f6;

	t3 = -f1 * f6*f11 - f5 * f10*f3 - f9 * f2*f7 + f9 * f6*f3 + f5 * f2*f11 + f1 * f10*f7;
	t7 = f0 * f6*f11 + f4 * f10*f3 + f8 * f2*f7 - f8 * f6*f3 - f4 * f2*f11 - f0 * f10*f7;
	t11 = -f0 * f5*f11 - f4 * f9*f3 - f8 * f1*f7 + f8 * f5*f7 + f4 * f1*f11 + f0 * f9*f7;
	t15 = f0 * f5*f10 + f4 * f9*f2 + f8 * f1*f6 - f0 * f5*f10 - f4 * f9*f2 - f0 * f9*f6;

	Matrix4F tmp = (1/determinant)*Matrix4F(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);

	this->m0 = tmp.m0;
	this->m1 = tmp.m1;
}

FLOAT Matrix4F::Determinant() const{
	return (f0 * f5 * f10 * f15) + (f0 * f9 * f14 * f7) + (f0 * f13 * f6 * f11)
		- (f0 * f13 * f10 * f7) - (f0 * f9 * f6 * f15) - (f0 * f5 * f14 * f11)
		- (f4 * f1 * f10 * f15) - (f8 * f1 * f14 * f7) - (f12 * f1 * f6 * f11)
		+ (f12 * f1 * f10 * f7) + (f8 * f1 * f6 * f15) + (f4 * f1 * f14 * f11)
		+ (f4 * f9 * f2 * f15) + (f8 * f13 * f2 * f7) + (f12 * f5 * f2 * f11)
		- (f12 * f9 * f2 * f7) - (f8 * f5 * f2 * f15) - (f4 * f13 * f2 * f11)
		- (f4 * f9 * f14 * f3) - (f8 * f13 * f6 * f3) - (f12 * f5 * f10 * f3)
		+ (f12 * f9 * f6 * f3) + (f8 * f5 * f14 * f3) + (f4 * f13 * f10 * f3);
}

Matrix4F Matrix4F::InverseCopy() const
{
	// TODO // DDOUGH
	// Not yet implemented

	FLOAT determinant = Determinant();

	FLOAT t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

	t0 = f5 * f10 * f15 + f9 * f14 * f7 + f13 * f6 * f11 - f13 * f10 * f7 - f9 * f6 * f15 - f5 * f14 * f11;
	t4 = -f4 * f10*f15 - f8 * f14*f7 - f12 * f6*f11 + f12 * f10*f7 + f8 * f6*f15 + f4 * f14*f11;
	t8 = f4 * f9*f15 + f8 * f13*f7 + f12 * f5*f11 - f12 * f9*f7 - f8 * f5*f15 - f4 * f13*f11;
	t12 = -f4 * f9*f14 - f8 * f13*f6 - f12 * f5*f10 + f12 * f9*f6 + f8 * f5*f14 + f4 * f13*f10;

	t1 = -(f1 * f10 * f15) - (f9 * f14 * f3) - (f13 * f2 * f11) + f13 * f10*f3 + f9 * f2*f15 + f1 * f14*f11;
	t5 = f0 * f10*f15 + f8 * f14*f3 + f12 * f2*f11 - f12 * f10*f3 - f8 * f2*f15 - f0 * f14*f11;
	t9 = -f0 * f9*f15 - f8 * f13*f3 - f12 * f1*f11 + f12 * f9*f3 + f8 * f1*f15 + f0 * f13*f11;
	t13 = f0 * f9*f14 + f8 * f13*f2 + f12 * f1*f10 - f12 * f9*f2 - f8 * f1*f14 - f0 * f13*f10;

	t2 = f1 * f6*f15 + f5 * f14*f3 + f13 * f2*f7 - f13 * f6*f3 - f5 * f2*f15 - f1 * f14*f7;
	t6 = -f0 * f6*f15 - f4 * f14*f3 - f12 * f2*f7 + f12 * f6*f3 + f4 * f2*f15 + f0 * f14*f7;
	t10 = f0 * f5*f15 + f4 * f13*f3 + f12 * f1*f7 - f12 * f5*f3 - f4 * f1*f15 - f0 * f13*f7;
	t14 = -f0 * f5*f14 - f4 * f13*f2 - f12 * f1*f6 + f12 * f5*f2 + f4 * f1*f14 + f0 * f13*f6;

	t3 = -f1 * f6*f11 - f5 * f10*f3 - f9 * f2*f7 + f9 * f6*f3 + f5 * f2*f11 + f1 * f10*f7;
	t7 = f0 * f6*f11 + f4 * f10*f3 + f8 * f2*f7 - f8 * f6*f3 - f4 * f2*f11 - f0 * f10*f7;
	t11 = -f0 * f5*f11 - f4 * f9*f3 - f8 * f1*f7 + f8 * f5*f7 + f4 * f1*f11 + f0 * f9*f7;
	t15 = f0 * f5*f10 + f4 * f9*f2 + f8 * f1*f6 - f8 * f5*f2 - f4 * f1*f2 - f0 * f9*f6;

	return (1 / determinant)*Matrix4F(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
}

// --- End of File --- //