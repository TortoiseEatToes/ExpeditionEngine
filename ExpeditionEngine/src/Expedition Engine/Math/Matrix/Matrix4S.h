
#ifndef Matrix4S_H
#define Matrix4S_H

// Includes
#include <immintrin.h>

#include "../Vector/Vector4S.h"

class Matrix4S : public Align16
{
	friend Vector4S;
private:
	//==========
	// Raw Data
	//==========

	// Nameless Union
	union
	{
		struct
		{
			__m256i m0;
			__m256i m1;
		};

		struct
		{
			Vector4S v0;
			Vector4S v1;
			Vector4S v2;
			Vector4S v3;
		};

		struct
		{
			S32 s0;
			S32 s1;
			S32 s2;
			S32 s3;
			S32 s4;
			S32 s5;
			S32 s6;
			S32 s7;
			S32 s8;
			S32 s9;
			S32 s10;
			S32 s11;
			S32 s12;
			S32 s13;
			S32 s14;
			S32 s15;
		};
	};

public:
	//=======
	// Big 6
	//=======
	Matrix4S();
	Matrix4S( const S32 inF0, const S32 inF1, const S32 inF2, const S32 inF3,
			  const S32 inF4, const S32 inF5, const S32 inF6, const S32 inF7,
			  const S32 inF8, const S32 inF9, const S32 inF10, const S32 inF11,
			  const S32 inF12, const S32 inF13, const S32 inF14, const S32 inF15 );
	Matrix4S( const Vector4S& rInV0, const Vector4S& rInV1, const Vector4S& rInV2, const Vector4S& rInV3 );
	Matrix4S( const __m128i& rInV0, const __m128i& rInV1, const __m128i& rInV2, const __m128i& rInV3 );
	Matrix4S( const __m256i& rInM0, const __m256i& rInM1 );
	Matrix4S( const RotType_X axis, const Vector4S& rInV );
	Matrix4S( const RotType_Y axis, const Vector4S& rInV );
	Matrix4S( const RotType_Z axis, const Vector4S& rInV );
	Matrix4S( const TransType type, const Vector4S& rInV );
	Matrix4S( const ScaleType type, const S32 scale );
	Matrix4S( const SpecialType_Zero type );
	Matrix4S( const SpecialType_Identity type );
	Matrix4S( const Rot3AxisType_XYZ axisOrder );
	Matrix4S( const Rot3AxisType_XZY axisOrder );
	Matrix4S( const Rot3AxisType_YXZ axisOrder );
	Matrix4S( const Rot3AxisType_YZX axisOrder );
	Matrix4S( const Rot3AxisType_ZXY axisOrder );
	Matrix4S( const Rot3AxisType_ZYX axisOrder );
	Matrix4S( const Matrix4S& rInM );
	Matrix4S( Matrix4S&& rInM ) noexcept;
	void operator = ( const Matrix4S& rInM );
	void operator = ( Matrix4S&& rInM ) noexcept;
	~Matrix4S() = default;

	//=========
	// Bracket
	//=========
	FORCEINLINE S32& operator[] ( const enum f0_enum ) { return s0; };
	FORCEINLINE S32& operator[] ( const enum f1_enum ) { return s1; };
	FORCEINLINE S32& operator[] ( const enum f2_enum ) { return s2; };
	FORCEINLINE S32& operator[] ( const enum f3_enum ) { return s3; };
	FORCEINLINE S32& operator[] ( const enum f4_enum ) { return s4; };
	FORCEINLINE S32& operator[] ( const enum f5_enum ) { return s5; };
	FORCEINLINE S32& operator[] ( const enum f6_enum ) { return s6; };
	FORCEINLINE S32& operator[] ( const enum f7_enum ) { return s7; };
	FORCEINLINE S32& operator[] ( const enum f8_enum ) { return s8; };
	FORCEINLINE S32& operator[] ( const enum f9_enum ) { return s9; };
	FORCEINLINE S32& operator[] ( const enum f10_enum ) { return s10; };
	FORCEINLINE S32& operator[] ( const enum f11_enum ) { return s11; };
	FORCEINLINE S32& operator[] ( const enum f12_enum ) { return s12; };
	FORCEINLINE S32& operator[] ( const enum f13_enum ) { return s13; };
	FORCEINLINE S32& operator[] ( const enum f14_enum ) { return s14; };
	FORCEINLINE S32& operator[] ( const enum f15_enum ) { return s15; };

	FORCEINLINE S32 operator[] ( const enum f0_enum ) const { return s0; };
	FORCEINLINE S32 operator[] ( const enum f1_enum ) const { return s1; };
	FORCEINLINE S32 operator[] ( const enum f2_enum ) const { return s2; };
	FORCEINLINE S32 operator[] ( const enum f3_enum ) const { return s3; };
	FORCEINLINE S32 operator[] ( const enum f4_enum ) const { return s4; };
	FORCEINLINE S32 operator[] ( const enum f5_enum ) const { return s5; };
	FORCEINLINE S32 operator[] ( const enum f6_enum ) const { return s6; };
	FORCEINLINE S32 operator[] ( const enum f7_enum ) const { return s7; };
	FORCEINLINE S32 operator[] ( const enum f8_enum ) const { return s8; };
	FORCEINLINE S32 operator[] ( const enum f9_enum ) const { return s9; };
	FORCEINLINE S32 operator[] ( const enum f10_enum ) const { return s10; };
	FORCEINLINE S32 operator[] ( const enum f11_enum ) const { return s11; };
	FORCEINLINE S32 operator[] ( const enum f12_enum ) const { return s12; };
	FORCEINLINE S32 operator[] ( const enum f13_enum ) const { return s13; };
	FORCEINLINE S32 operator[] ( const enum f14_enum ) const { return s14; };
	FORCEINLINE S32 operator[] ( const enum f15_enum ) const { return s15; };


	//============
	// Accessors 
	//============
	FORCEINLINE S32& F0() { return s0; };
	FORCEINLINE S32& F1() { return s1; };
	FORCEINLINE S32& F2() { return s2; };
	FORCEINLINE S32& F3() { return s3; };
	FORCEINLINE S32& F4() { return s4; };
	FORCEINLINE S32& F5() { return s5; };
	FORCEINLINE S32& F6() { return s6; };
	FORCEINLINE S32& F7() { return s7; };
	FORCEINLINE S32& F8() { return s8; };
	FORCEINLINE S32& F9() { return s9; };
	FORCEINLINE S32& F10() { return s10; };
	FORCEINLINE S32& F11() { return s11; };
	FORCEINLINE S32& F12() { return s12; };
	FORCEINLINE S32& F13() { return s13; };
	FORCEINLINE S32& F14() { return s14; };
	FORCEINLINE S32& F15() { return s15; };

	FORCEINLINE S32 F0() const { return s0; };
	FORCEINLINE S32 F1() const { return s1; };
	FORCEINLINE S32 F2() const { return s2; };
	FORCEINLINE S32 F3() const { return s3; };
	FORCEINLINE S32 F4() const { return s4; };
	FORCEINLINE S32 F5() const { return s5; };
	FORCEINLINE S32 F6() const { return s6; };
	FORCEINLINE S32 F7() const { return s7; };
	FORCEINLINE S32 F8() const { return s8; };
	FORCEINLINE S32 F9() const { return s9; };
	FORCEINLINE S32 F10() const { return s10; };
	FORCEINLINE S32 F11() const { return s11; };
	FORCEINLINE S32 F12() const { return s12; };
	FORCEINLINE S32 F13() const { return s13; };
	FORCEINLINE S32 F14() const { return s14; };
	FORCEINLINE S32 F15() const { return s15; };

	//======================
	// Add and Sub operator
	//======================
	FORCEINLINE const Matrix4S operator + () const { return *this; }; // TO DO // What calls this?
	FORCEINLINE const Matrix4S operator - () const { return *this; }; // TO DO // What calls this?
	FORCEINLINE const Matrix4S operator + ( const Matrix4S& rInM ) const { return Matrix4S( _mm256_add_epi32( m0, rInM.m0 ), _mm256_add_epi32( m1, rInM.m1) ); };
	FORCEINLINE const Matrix4S operator - ( const Matrix4S& rInM ) const { return Matrix4S( _mm256_sub_epi32( m0, rInM.m0 ), _mm256_sub_epi32( m1, rInM.m1 ) ); };
	FORCEINLINE void operator += ( const Matrix4S& rInM ) { m0 = _mm256_add_epi32( m0, rInM.m0 ); m1 = _mm256_add_epi32( m1, rInM.m1 );  };
	FORCEINLINE void operator -= ( const Matrix4S& rInM ) { m0 = _mm256_sub_epi32( m0, rInM.m0 ); m1 = _mm256_sub_epi32( m1, rInM.m1 );  };

	//=====================
	// Mult operators
	//=====================
	FORCEINLINE const Matrix4S operator * ( const S32 scale ) const
	{ 
		const __m256i scaleMat = _mm256_set1_epi32( scale );
		return Matrix4S( _mm256_mul_epi32( m0, scaleMat ), _mm256_mul_epi32( m1, scaleMat ) );
	};
	friend FORCEINLINE const Matrix4S operator * ( const S32 scale, const Matrix4S& rInM )
	{ 
		const __m256i scaleMat = _mm256_set1_epi32( scale );
		return Matrix4S( _mm256_mul_epi32( rInM.m0, scaleMat ), _mm256_mul_epi32( rInM.m1, scaleMat ) );
	};
	FORCEINLINE void operator *= ( const S32 scale ) 
	{ 
		const __m256i scaleMat = _mm256_set1_epi32( scale );
		m0 = _mm256_mul_epi32( m0, scaleMat ); 
		m1 = _mm256_mul_epi32( m1, scaleMat );
	}
	FORCEINLINE const Matrix4S operator * ( const Matrix4S& rInMat )
	{ 
		Matrix4S result;
		Matrix4S trans = TransposeCopy();

		result.s0 = rInMat.v0.Dot( trans.v0 );
		result.s1 = rInMat.v1.Dot( trans.v0 );
		result.s2 = rInMat.v2.Dot( trans.v0 );
		result.s3 = rInMat.v3.Dot( trans.v0 );

		result.s4 = rInMat.v0.Dot( trans.v0 );
		result.s5 = rInMat.v1.Dot( trans.v1 );
		result.s6 = rInMat.v2.Dot( trans.v1 );
		result.s7 = rInMat.v3.Dot( trans.v1 );
		
		result.s8 = rInMat.v0.Dot( trans.v2 );
		result.s9 = rInMat.v1.Dot( trans.v2 );
		result.s10 = rInMat.v2.Dot( trans.v2 );
		result.s11 = rInMat.v3.Dot( trans.v2 );
		
		result.s12 = rInMat.v0.Dot( trans.v3 );
		result.s13 = rInMat.v1.Dot( trans.v3 );
		result.s14 = rInMat.v2.Dot( trans.v3 );
		result.s15 = rInMat.v3.Dot( trans.v3 );

		return result;
	};
	FORCEINLINE void operator *= ( const Matrix4S& rInMat ) 
	{
		Matrix4S result;
		Matrix4S trans = TransposeCopy();

		result.s0 = rInMat.v0.Dot( trans.v0 );
		result.s1 = rInMat.v0.Dot( trans.v1 );
		result.s2 = rInMat.v0.Dot( trans.v2 );
		result.s3 = rInMat.v0.Dot( trans.v3 );

		result.s4 = rInMat.v1.Dot( trans.v0 );
		result.s5 = rInMat.v1.Dot( trans.v1 );
		result.s6 = rInMat.v1.Dot( trans.v2 );
		result.s7 = rInMat.v1.Dot( trans.v3 );

		result.s8 = rInMat.v2.Dot( trans.v0 );
		result.s9 = rInMat.v2.Dot( trans.v1 );
		result.s10 = rInMat.v2.Dot( trans.v2 );
		result.s11 = rInMat.v2.Dot( trans.v3 );

		result.s12 = rInMat.v3.Dot( trans.v0 );
		result.s13 = rInMat.v3.Dot( trans.v1 );
		result.s14 = rInMat.v3.Dot( trans.v2 );
		result.s15 = rInMat.v3.Dot( trans.v3 );

		m0 = result.m0;
		m1 = result.m1;
	}

	//===================
	// Matrix functions
	//===================
	void Transpose();
	Matrix4S TransposeCopy();
	void Inverse();
	Matrix4S InverseCopy();

	// void Decomposition


	//=========
	// Setters
	//=========
	// void Set( const S32 inX, const S32 inY, const S32 inZ, const S32 inW = 1.0f );
	// void Set( const Vector4S& rInV );
};

// M x M x M x V ( helps dummy multi )

#endif // !Matrix4S_H

// --- End of File --- //