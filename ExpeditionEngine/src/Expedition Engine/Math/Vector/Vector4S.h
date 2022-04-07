
#ifndef Vector4S_H
#define Vector4S_H

// Includes
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "../Base/Align16.h"
#include "../Base/MathEnums.h"
#include "../Base/Defs.h"
#include "../Base/Types.h"

// Forward Declarations
class Matrix4S;

//====================
// Design Notes
//	*4 INT class
//====================
class Vector4S : public Align16
{
	friend Matrix4S;
private:
	//===========
	// Raw Data
	//===========

	// Nameless Union
	union
	{
		__m128i v0;

		struct
		{
			S32 x;
			S32 y;
			S32 z;
			S32 w;
		};
	};
public:
	//========
	// Big 6
	//========
	Vector4S();
	Vector4S( const __m128i& inV );
	Vector4S( const S32 inX, const S32 inY, const S32 inZ, const S32 inW = 0.0f );
	Vector4S( const Vector4S& inV );
	Vector4S( Vector4S&& inV ) noexcept;
	void operator = ( const Vector4S& inV );
	void operator = ( Vector4S&& inV ) noexcept;
	~Vector4S() = default;

	//=======
	// Cast
	//=======
	FORCEINLINE operator __m128i( ) { return v0; };
	FORCEINLINE operator __m128i( ) const { return v0; };

	//=========
	// Bracket
	//=========
	FORCEINLINE S32& operator[] ( const enum x_enum ) { return x; };
	FORCEINLINE S32& operator[] ( const enum y_enum ) { return y; };
	FORCEINLINE S32& operator[] ( const enum z_enum ) { return z; };
	FORCEINLINE S32& operator[] ( const enum w_enum ) { return w; };

	FORCEINLINE S32 operator[] ( const enum x_enum ) const { return x; };
	FORCEINLINE S32 operator[] ( const enum y_enum ) const { return y; };
	FORCEINLINE S32 operator[] ( const enum z_enum ) const { return z; };
	FORCEINLINE S32 operator[] ( const enum w_enum ) const { return w; };

	//============
	// Accessors 
	//============
	FORCEINLINE S32& X() { return x; };
	FORCEINLINE S32& Y() { return y; };
	FORCEINLINE S32& Z() { return z; };
	FORCEINLINE S32& W() { return w; };

	FORCEINLINE S32 X() const { return x; };
	FORCEINLINE S32 Y() const { return y; };
	FORCEINLINE S32 Z() const { return z; };
	FORCEINLINE S32 W() const { return w; };

	//======================
	// Add and Sub operator
	//======================
	FORCEINLINE const Vector4S operator + () const { return *this; }; // TODO // What calls this?
	FORCEINLINE const Vector4S operator - () const { return *this; }; // TODO // What calls this?
	FORCEINLINE const Vector4S operator + ( const Vector4S& rInV ) const { return _mm_add_epi32( v0, rInV.v0 ); };
	FORCEINLINE const Vector4S operator - ( const Vector4S& rInV ) const { return _mm_add_epi32( v0, rInV.v0 ); };
	FORCEINLINE void operator += ( const Vector4S& rInV ) { v0 = _mm_add_epi32( v0, rInV.v0 ); };
	FORCEINLINE void operator -= ( const Vector4S& rInV ) { v0 = _mm_add_epi32( v0, rInV.v0 ); };

	//=====================
	// Mult operators
	//=====================
	FORCEINLINE const Vector4S operator * ( const S32 scale ) const { return _mm_mul_epi32( v0, _mm_set1_epi32( scale ) ); };
	friend FORCEINLINE const Vector4S operator * ( const S32 scale, const Vector4S& rInV ) { return _mm_mul_epi32( rInV.v0, _mm_set1_epi32( scale ) ); };
	FORCEINLINE void operator *= ( const S32 scale ) { v0 = _mm_mul_epi32( v0, _mm_set1_epi32( scale ) ); };

	//================
	// Vect * Matrix
	//================
	const Vector4S operator * ( const Matrix4S& rInM ) const;
	void operator *= ( const Matrix4S& rInM );

	//===================
	// Vector functions
	//===================
	void Norm();
	Vector4S NormCopy() const;
	S32 Dot( const Vector4S& rInV ) const;
	const Vector4S Cross( const Vector4S& rInV ) const;
	FLOAT Mag() const;
	FLOAT MagSqr() const;

	//=========
	// Setters
	//=========
	void Set( const S32 inX, const S32 inY, const S32 inZ, const S32 inW = 0.0f );
	void Set( const Vector4S& rInV );
};

#endif // !Vector4S_H

// --- End of File --- //