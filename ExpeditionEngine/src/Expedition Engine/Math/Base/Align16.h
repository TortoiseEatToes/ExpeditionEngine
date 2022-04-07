
#ifndef Align_16_H
#define Align_16_H

#include <utility>

//=========================================
// Aligns the class to 16 bytes
//=========================================
class Align16
{
public:
	void* operator new( size_t size )
	{
		return _aligned_malloc( size, 16 );
	}

	void* operator new[]( size_t size )
	{
		return _aligned_malloc( size, 16 );
	}

	void operator delete( void* p )
	{
		_aligned_free( p );
	}

	void operator delete[]( void* p )
	{
		_aligned_free( p );
	}
};

#endif // !Align16_H

// --- End of File --- //