
#ifndef Vector4F_H
#define Vector4F_H

// Includes
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "../Base/Align16.h"
#include "../Base/MathEnums.h"
#include "../Base/Defs.h"
#include "../Base/Types.h"

// Forward Declarations
class Matrix4F;

//====================
// Design Notes
//	*4 FLOAT class
//====================

class Texture;

class Vector4F : public Align16
{
friend Matrix4F;
friend class Vector4FDoubleBuffer;
private:
	//===========
	// Raw Data
	//===========

	
	union Attribute
	{
		Texture* pTexture;
		int Integer;
	};

	// Nameless Union
	union
	{
		__m128 v0;

		struct
		{
			FLOAT x;
			FLOAT y;
			FLOAT z;
			FLOAT w;
		};

		struct
		{
			Attribute attribute0;
			Attribute attribute1;
			Attribute attribute2;
			Attribute attribute3;
		};
	};

public:
	//========
	// Big 6
	//========
	Vector4F();
	Vector4F( const __m128& inV );
	Vector4F( const FLOAT inX, const FLOAT inY, const FLOAT inZ, const FLOAT inW = 0.0f );
	Vector4F( const Vector4F& inV );
	Vector4F( Vector4F&& inV ) noexcept;
	void operator = ( const Vector4F& inV );
	void operator = ( Vector4F&& inV ) noexcept;
	~Vector4F() = default;

	//=======
	// Cast
	//=======
	FORCEINLINE operator __m128( ) { return v0; };
	FORCEINLINE operator __m128( ) const { return v0; };

	//=========
	// Bracket
	//=========
	FORCEINLINE FLOAT& operator[] ( const enum x_enum ) { return x; };
	FORCEINLINE FLOAT& operator[] ( const enum y_enum ) { return y; };
	FORCEINLINE FLOAT& operator[] ( const enum z_enum ) { return z; };
	FORCEINLINE FLOAT& operator[] ( const enum w_enum ) { return w; };

	FORCEINLINE FLOAT operator[] ( const enum x_enum ) const { return x; };
	FORCEINLINE FLOAT operator[] ( const enum y_enum ) const { return y; };
	FORCEINLINE FLOAT operator[] ( const enum z_enum ) const { return z; };
	FORCEINLINE FLOAT operator[] ( const enum w_enum ) const { return w; };

	//============
	// Accessors 
	//============
	FORCEINLINE FLOAT& X() { return x; };
	FORCEINLINE FLOAT& Y() { return y; };
	FORCEINLINE FLOAT& Z() { return z; };
	FORCEINLINE FLOAT& W() { return w; };

	FORCEINLINE FLOAT X() const { return x; };
	FORCEINLINE FLOAT Y() const { return y; };
	FORCEINLINE FLOAT Z() const { return z; };
	FORCEINLINE FLOAT W() const { return w; };

	//======================
	// Add and Sub operator
	//======================
	FORCEINLINE const Vector4F operator + () const { return *this; }; // TODO // What calls this?
	FORCEINLINE const Vector4F operator - () const { return *this; }; // TODO // What calls this?
	FORCEINLINE const Vector4F operator + ( const Vector4F& rInV ) const { return _mm_add_ps( v0, rInV.v0 ); };
	FORCEINLINE const Vector4F operator - ( const Vector4F& rInV ) const { return _mm_sub_ps( v0, rInV.v0 ); };
	FORCEINLINE void operator += ( const Vector4F& rInV ) { v0 = _mm_add_ps( v0, rInV.v0 ); };
	FORCEINLINE void operator -= ( const Vector4F& rInV ) { v0 = _mm_sub_ps( v0, rInV.v0 ); };

	//=====================
	// Mult operators
	//=====================
	FORCEINLINE const Vector4F operator * ( const FLOAT scale ) const { return _mm_mul_ps( v0, _mm_set1_ps( scale ) ); };
	friend FORCEINLINE const Vector4F operator * ( const FLOAT scale, const Vector4F& rInV ) { return _mm_mul_ps( rInV.v0, _mm_set1_ps( scale ) ); };
	FORCEINLINE void operator *= ( const FLOAT scale ) { v0 = _mm_mul_ps( v0, _mm_set1_ps( scale ) ); };
	void operator *= (const Vector4F& inVect);
	Vector4F operator * (const Vector4F& inVect);

	//================
	// Vect * Matrix
	//================
	const Vector4F operator * ( const Matrix4F& rInM ) const;
	void operator *= ( const Matrix4F& rInM );

	//===================
	// Vector functions
	//===================
	void Norm();
	Vector4F NormCopy() const;
	FLOAT Dot( const Vector4F& rInV ) const;
	const Vector4F Cross( const Vector4F& rInV ) const;
	FLOAT Mag() const;
	FLOAT MagSqr() const;
	void RotateAxisAngle(const Vector4F& axis, const float& angle);
	Vector4F RotateAxisAngleCopy(const Vector4F& axis, const float& angle);

	//=========
	// Setters
	//=========
	void Set( const FLOAT inX, const FLOAT inY, const FLOAT inZ, const FLOAT inW = 0.0f );
	void Set( const Vector4F& rInV );
};

#endif // !Vector4F_H

// --- End of File --- //