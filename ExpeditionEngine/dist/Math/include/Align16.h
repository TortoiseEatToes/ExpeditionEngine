
#ifndef Align16_H
#define Align16_h

// Incase unused Aligned16 Var
#define ALIGN_UNUSED_VAR( x ) ( void( x ) )

// Unbind new and Bind ours
#pragma push_macro("new");
#undef new

// Includes
#include <stdlib.h>  

//===================================
// Aligns the instance to 16 bytes
//===================================
class Align16
{
private:

public:
	//===================================
	// Big 6
	//===================================
	Align16() = default;
	Align16( const Align16& ) = default;
	Align16( Align16&& ) = default;
	Align16& operator = ( const Align16& ) = default;
	Align16& operator = ( Align16&& ) = default;
	virtual ~Align16() = default;

	//========================================================
	// Operators new/delete with Keenan's memory tracking off
	//========================================================
	void* operator new ( size_t inSize )
	{
		return _aligned_malloc( inSize, 16 );
	}

	void operator delete ( void* pIn )
	{
		_aligned_free( pIn );
	}

	void* operator new[] ( size_t inSize )
	{
		return _aligned_malloc( inSize, 16 );
	}

	void operator delete[] ( void* pIn )
	{
		_aligned_free( pIn );
	}

	//========================================================
	// Operators new/delete with Keenan's memory tracking on
	//========================================================
	void* operator new ( size_t	   inSize,
						 int			   inBlockUse,
						 const char* const pInFileName,
						 int			   inLineNumber )
	{
		ALIGN_UNUSED_VAR( inBlockUse );
		ALIGN_UNUSED_VAR( pInFileName );
		ALIGN_UNUSED_VAR( inLineNumber );

		return _aligned_malloc( inSize, 16 );
	}

	void operator delete ( void*			 pIn,
						   int				 inBlockUse,
						   const char* const pInFileName,
						   int				 inLineNumber )
	{
		ALIGN_UNUSED_VAR( inBlockUse );
		ALIGN_UNUSED_VAR( pInFileName );
		ALIGN_UNUSED_VAR( inLineNumber );

		_aligned_free( pIn );
	}

	void* operator new[] (size_t		inSize,
						  int				inBlockUse,
						  const char* const pInFileName,
						  int				inLineNumber )
	{
		ALIGN_UNUSED_VAR( inBlockUse );
		ALIGN_UNUSED_VAR( pInFileName );
		ALIGN_UNUSED_VAR( inLineNumber );

		return _aligned_malloc( inSize, 16 );
	}

	void operator delete[] ( void* pIn,
							 int	inBlockUse,
							 const char* const pInFileName,
							 int inLineNumber )
	{
		ALIGN_UNUSED_VAR( inBlockUse );
		ALIGN_UNUSED_VAR( pInFileName );
		ALIGN_UNUSED_VAR( inLineNumber );

		_aligned_free( pIn );
	}
};

#pragma pop_macro("new")

#endif

// --- End of File --- //