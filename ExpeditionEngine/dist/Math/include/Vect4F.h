
#ifndef Vect4F_H
#define Vect4F_H

// Includes
#include "Align16.h"
#include "MathEnums.h"
#include "Constants.h"

#include <xmmintrin.h>
#include <smmintrin.h> 
#include <pmmintrin.h>
#include <immintrin.h>

// Forward Declaration
class Matrix4F;

//===============================================
// Vect4F : public Align16
//	Data Class - Stores 4 floats
//
//	* Aligned on 16 bytes for SIMD
//===============================================
class Vect4F final : public Align16
{
friend class Matrix4F;
public:
	// Data
	#pragma warning( disable : 4201)	// Nameless Union/Structs
	union
	{
		__m128 v0;

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

	};

public:
	// Big 4
	Vect4F();
	Vect4F( const Vect4F& );
	Vect4F& operator = ( const Vect4F& );
	~Vect4F() = default; // Allows Compiler Optimization

	// Casts
	inline operator __m128() { return v0; }
	inline operator const __m128() { return v0; }
	inline operator const __m128() const { return v0; }

	inline operator __m128*() { return &v0; }
	inline operator const __m128*() { return &v0; }
	inline operator const __m128*() const { return &v0; }

	// Specialized Constructors
	Vect4F( const __m128 );
	Vect4F( const float inX, const float inY, const float inZ, const float inW = 0.0f );

	// Bracket
	float& operator[] ( const enum x_enum );
	float& operator[] ( const enum y_enum );
	float& operator[] ( const enum z_enum );
	float& operator[] ( const enum w_enum );

	float operator[] ( const enum x_enum ) const;
	float operator[] ( const enum y_enum ) const;
	float operator[] ( const enum z_enum ) const;
	float operator[] ( const enum w_enum ) const;

	// Add Operators
	const Vect4F operator + () const;
	const Vect4F operator + ( const Vect4F& ) const;
	void operator += ( const Vect4F& inV );

	// Sub Operators
	const Vect4F operator - () const;
	const Vect4F operator - ( const Vect4F& ) const;
	void operator -= ( const Vect4F& );

	// Mult Operators
	const Vect4F operator * ( const float ) const;
	const Vect4F operator * ( const Matrix4F& ) const;
	friend Vect4F operator * ( const float, const Vect4F& );
	void operator *= ( const Matrix4F& );
	void operator *= ( const float );

	// Div Operators
	const Vect4F operator / ( const float ) const;
	void operator /= ( const float );

	// Vect Methods
	void FastNormalize();
	void Normalize();
	const Vect4F FastNormalizeCopy();
	const Vect4F NormalizeCopy();
	const Vect4F Cross( const Vect4F& inVect );
	float Dot( const Vect4F& inVect );
	float Mag();
	float MagSqr();
	float AngleBetween( const Vect4F& inVect );

	// Accessors
	float& X();
	float& Y();
	float& Z();
	float& W();

	float X() const;
	float Y() const;
	float Z() const;
	float W() const;

	// Setters
	void set( const float inX, const float inY, const float inZ, const float inW = 0.0f );
	void set( const Vect4F &inV );

	// Comparisons
	bool IsEqual( const Vect4F&, const float epsilon ) const;
	bool IsZero( const float epsilon ) const;
};

#endif