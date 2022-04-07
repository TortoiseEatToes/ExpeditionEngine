
#ifndef Matrix4F_H
#define Matrix4F_H

// Includes
#include <immintrin.h>

#include "../Vector/Vector4F.h"

class Matrix4F : public Align16
{
friend Vector4F;
private:
	//==========
	// Raw Data
	//==========

	// Nameless Union
	union
	{
		struct
		{
			__m256 m0;
			__m256 m1;
		};

		struct
		{
			Vector4F v0;
			Vector4F v1;
			Vector4F v2;
			Vector4F v3;
		};

		struct
		{
			FLOAT f0;
			FLOAT f1;
			FLOAT f2;
			FLOAT f3;
			FLOAT f4;
			FLOAT f5;
			FLOAT f6;
			FLOAT f7;
			FLOAT f8;
			FLOAT f9;
			FLOAT f10;
			FLOAT f11;
			FLOAT f12;
			FLOAT f13;
			FLOAT f14;
			FLOAT f15;
		};
	};

public:
	//=======
	// Big 6
	//=======
	Matrix4F();
	Matrix4F( const FLOAT inF0, const FLOAT inF1, const FLOAT inF2, const FLOAT inF3,
			  const FLOAT inF4, const FLOAT inF5, const FLOAT inF6, const FLOAT inF7,
			  const FLOAT inF8, const FLOAT inF9, const FLOAT inF10, const FLOAT inF11,
			  const FLOAT inF12, const FLOAT inF13, const FLOAT inF14, const FLOAT inF15 );
	Matrix4F( const Vector4F& rInV0, const Vector4F& rInV1, const Vector4F& rInV2, const Vector4F& rInV3 );
	Matrix4F( const __m128& rInV0, const __m128& rInV1, const __m128& rInV2, const __m128& rInV3 );
	Matrix4F( const __m256& rInM1, const __m256& rInM0 );
	Matrix4F( const RotType_X axis, const Vector4F& rInV );
	Matrix4F( const RotType_Y axis, const Vector4F& rInV );
	Matrix4F( const RotType_Z axis, const Vector4F& rInV );
	Matrix4F(const RotType_AxisAngle type, const Vector4F& axis, const float& angle);
	Matrix4F( const TransType type, const Vector4F& rInV );
	Matrix4F( const ScaleType type, const FLOAT scale );
	Matrix4F( const ScaleType type, const FLOAT scalex, const FLOAT scaley, const FLOAT scalez);
	Matrix4F( const SpecialType_Zero type );
	Matrix4F( const SpecialType_Identity type );
	Matrix4F( const Rot3AxisType_XYZ axisOrder );
	Matrix4F( const Rot3AxisType_XZY axisOrder );
	Matrix4F( const Rot3AxisType_YXZ axisOrder );
	Matrix4F( const Rot3AxisType_YZX axisOrder );
	Matrix4F( const Rot3AxisType_ZXY axisOrder );
	Matrix4F( const Rot3AxisType_ZYX axisOrder );
	Matrix4F( const Matrix4F& rInM );
	Matrix4F( Matrix4F&& rInM ) noexcept;
	void operator = ( const Matrix4F& rInM );
	void operator = ( Matrix4F&& rInM ) noexcept;
	~Matrix4F() = default;

	//=========
	// Bracket
	//=========
	FORCEINLINE FLOAT& operator[] ( const enum f0_enum ) { return f0; };
	FORCEINLINE FLOAT& operator[] ( const enum f1_enum ) { return f1; };
	FORCEINLINE FLOAT& operator[] ( const enum f2_enum ) { return f2; };
	FORCEINLINE FLOAT& operator[] ( const enum f3_enum ) { return f3; };
	FORCEINLINE FLOAT& operator[] ( const enum f4_enum ) { return f4; };
	FORCEINLINE FLOAT& operator[] ( const enum f5_enum ) { return f5; };
	FORCEINLINE FLOAT& operator[] ( const enum f6_enum ) { return f6; };
	FORCEINLINE FLOAT& operator[] ( const enum f7_enum ) { return f7; };
	FORCEINLINE FLOAT& operator[] ( const enum f8_enum ) { return f8; };
	FORCEINLINE FLOAT& operator[] ( const enum f9_enum ) { return f9; };
	FORCEINLINE FLOAT& operator[] ( const enum f10_enum ) { return f10; };
	FORCEINLINE FLOAT& operator[] ( const enum f11_enum ) { return f11; };
	FORCEINLINE FLOAT& operator[] ( const enum f12_enum ) { return f12; };
	FORCEINLINE FLOAT& operator[] ( const enum f13_enum ) { return f13; };
	FORCEINLINE FLOAT& operator[] ( const enum f14_enum ) { return f14; };
	FORCEINLINE FLOAT& operator[] ( const enum f15_enum ) { return f15; };

	FORCEINLINE FLOAT operator[] ( const enum f0_enum ) const { return f0; };
	FORCEINLINE FLOAT operator[] ( const enum f1_enum ) const { return f1; };
	FORCEINLINE FLOAT operator[] ( const enum f2_enum ) const { return f2; };
	FORCEINLINE FLOAT operator[] ( const enum f3_enum ) const { return f3; };
	FORCEINLINE FLOAT operator[] ( const enum f4_enum ) const { return f4; };
	FORCEINLINE FLOAT operator[] ( const enum f5_enum ) const { return f5; };
	FORCEINLINE FLOAT operator[] ( const enum f6_enum ) const { return f6; };
	FORCEINLINE FLOAT operator[] ( const enum f7_enum ) const { return f7; };
	FORCEINLINE FLOAT operator[] ( const enum f8_enum ) const { return f8; };
	FORCEINLINE FLOAT operator[] ( const enum f9_enum ) const { return f9; };
	FORCEINLINE FLOAT operator[] ( const enum f10_enum ) const { return f10; };
	FORCEINLINE FLOAT operator[] ( const enum f11_enum ) const { return f11; };
	FORCEINLINE FLOAT operator[] ( const enum f12_enum ) const { return f12; };
	FORCEINLINE FLOAT operator[] ( const enum f13_enum ) const { return f13; };
	FORCEINLINE FLOAT operator[] ( const enum f14_enum ) const { return f14; };
	FORCEINLINE FLOAT operator[] ( const enum f15_enum ) const { return f15; };


	//============
	// Accessors 
	//============
	FORCEINLINE FLOAT& F0()	{ return f0; };
	FORCEINLINE FLOAT& F1()	{ return f1; };
	FORCEINLINE FLOAT& F2()	{ return f2; };
	FORCEINLINE FLOAT& F3()	{ return f3; };
	FORCEINLINE FLOAT& F4()	{ return f4; };
	FORCEINLINE FLOAT& F5()	{ return f5; };
	FORCEINLINE FLOAT& F6()	{ return f6; };
	FORCEINLINE FLOAT& F7()	{ return f7; };
	FORCEINLINE FLOAT& F8()	{ return f8; };
	FORCEINLINE FLOAT& F9()	{ return f9; };
	FORCEINLINE FLOAT& F10() { return f10; };
	FORCEINLINE FLOAT& F11() { return f11; };
	FORCEINLINE FLOAT& F12() { return f12; };
	FORCEINLINE FLOAT& F13() { return f13; };
	FORCEINLINE FLOAT& F14() { return f14; };
	FORCEINLINE FLOAT& F15() { return f15; };

	FORCEINLINE FLOAT F0() const { return f0; };
	FORCEINLINE FLOAT F1() const { return f1; };
	FORCEINLINE FLOAT F2() const { return f2; };
	FORCEINLINE FLOAT F3() const { return f3; };
	FORCEINLINE FLOAT F4() const { return f4; };
	FORCEINLINE FLOAT F5() const { return f5; };
	FORCEINLINE FLOAT F6() const { return f6; };
	FORCEINLINE FLOAT F7() const { return f7; };
	FORCEINLINE FLOAT F8() const { return f8; };
	FORCEINLINE FLOAT F9() const { return f9; };
	FORCEINLINE FLOAT F10() const { return f10; };
	FORCEINLINE FLOAT F11() const { return f11; };
	FORCEINLINE FLOAT F12() const { return f12; };
	FORCEINLINE FLOAT F13() const { return f13; };
	FORCEINLINE FLOAT F14() const { return f14; };
	FORCEINLINE FLOAT F15() const { return f15; };
										  
	FORCEINLINE Vector4F V0() const { return v0; };
	FORCEINLINE Vector4F V1() const { return v1; };
	FORCEINLINE Vector4F V2() const { return v2; };
	FORCEINLINE Vector4F V3() const { return v3; };
			
	FORCEINLINE Vector4F& V0() { return v0; };
	FORCEINLINE Vector4F& V1() { return v1; };
	FORCEINLINE Vector4F& V2() { return v2; };
	FORCEINLINE Vector4F& V3() { return v3; };

	//======================
	// Add and Sub operator
	//======================
	FORCEINLINE const Matrix4F operator + () const { return *this; }; // TO DO // What calls this?
	FORCEINLINE const Matrix4F operator - () const { return *this; }; // TO DO // What calls this?
	FORCEINLINE const Matrix4F operator + ( const Matrix4F& rInM ) const { return Matrix4F( _mm256_add_ps( m0, rInM.m0 ), _mm256_add_ps( m1, rInM.m1 ) ); };
	FORCEINLINE const Matrix4F operator - ( const Matrix4F& rInM ) const { return Matrix4F( _mm256_sub_ps( m0, rInM.m0 ), _mm256_sub_ps( m1, rInM.m1 ) ); };
	FORCEINLINE void operator += ( const Matrix4F& rInM ) { m0 = _mm256_add_ps( m0, rInM.m0 ); m1 = _mm256_add_ps( m1, rInM.m1 ); };
	FORCEINLINE void operator -= ( const Matrix4F& rInM ) { m0 = _mm256_sub_ps( m0, rInM.m0 ); m1 = _mm256_sub_ps( m1, rInM.m1 ); };

	//=====================
	// Mult operators
	//=====================
	FORCEINLINE const Matrix4F operator * ( const FLOAT scale ) const
	{
		const __m256 scaleMat = _mm256_set1_ps( scale );
		return Matrix4F( _mm256_mul_ps( m0, scaleMat ), _mm256_mul_ps( m1, scaleMat ) );
	};
	friend FORCEINLINE const Matrix4F operator * ( const FLOAT scale, const Matrix4F& rInM )
	{ 
		const __m256 scaleMat = _mm256_set1_ps( scale );
		return Matrix4F( _mm256_mul_ps( rInM.m0, scaleMat ), _mm256_mul_ps( rInM.m1, scaleMat ) );
	};
	FORCEINLINE void operator *= ( const FLOAT scale )
	{
		const __m256 scaleMat = _mm256_set1_ps( scale );
		m0 = _mm256_mul_ps( m0, scaleMat );
		m1 = _mm256_mul_ps( m1, scaleMat );
	}
	const Matrix4F operator * ( const Matrix4F& rInMat )
	{ 
		Matrix4F result;
		Matrix4F trans = TransposeCopy();

		result.f0 = rInMat.v0.Dot(trans.v0);
		result.f1 = rInMat.v1.Dot(trans.v0);
		result.f2 = rInMat.v2.Dot(trans.v0);
		result.f3 = rInMat.v3.Dot(trans.v0);

		result.f4 = rInMat.v0.Dot(trans.v1);
		result.f5 = rInMat.v1.Dot(trans.v1);
		result.f6 = rInMat.v2.Dot(trans.v1);
		result.f7 = rInMat.v3.Dot(trans.v1);

		result.f8 = rInMat.v0.Dot(trans.v2);
		result.f9 = rInMat.v1.Dot(trans.v2);
		result.f10 = rInMat.v2.Dot(trans.v2);
		result.f11 = rInMat.v3.Dot(trans.v2);

		result.f12 = rInMat.v0.Dot(trans.v3);
		result.f13 = rInMat.v1.Dot(trans.v3);
		result.f14 = rInMat.v2.Dot(trans.v3);
		result.f15 = rInMat.v3.Dot(trans.v3);

		return result;
	};
	FORCEINLINE void operator *= ( const Matrix4F& rInMat)
	{ 
		Matrix4F result;
		Matrix4F trans = TransposeCopy();

		result.f0 = rInMat.v0.Dot( trans.v0 );
		result.f1 = rInMat.v0.Dot( trans.v1 );
		result.f2 = rInMat.v0.Dot( trans.v2 );
		result.f3 = rInMat.v0.Dot( trans.v3 );

		result.f4 = rInMat.v1.Dot( trans.v0 );
		result.f5 = rInMat.v1.Dot( trans.v1 );
		result.f6 = rInMat.v1.Dot( trans.v2 );
		result.f7 = rInMat.v1.Dot( trans.v3 );

		result.f8 = rInMat.v2.Dot( trans.v0 );
		result.f9 = rInMat.v2.Dot( trans.v1 );
		result.f10 = rInMat.v2.Dot( trans.v2 );
		result.f11 = rInMat.v2.Dot( trans.v3 );

		result.f12 = rInMat.v3.Dot( trans.v0 );
		result.f13 = rInMat.v3.Dot( trans.v1 );
		result.f14 = rInMat.v3.Dot( trans.v2 );
		result.f15 = rInMat.v3.Dot( trans.v3 );

		m0 = result.m0;
		m1 = result.m1;
	}

	//===================
	// Matrix functions
	//===================
	void Transpose();
	Matrix4F TransposeCopy() const;
	void Inverse();
	Matrix4F InverseCopy() const;
	FLOAT Determinant() const;

	// void Decomposition


	//=========
	// Setters
	//=========
	// void Set( const FLOAT inX, const FLOAT inY, const FLOAT inZ, const FLOAT inW = 1.0f );
	// void Set( const Vector4F& rInV );
};

// M x M x M x V ( helps dummy multi )

#endif // !Matrix4F_H

// --- End of File --- //