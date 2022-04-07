
#ifndef Constants_H
#define Constants_H

	#define MATH_TOLERANCE	0.0001f	/*<   TOLERANCE  >*/
	
	#define MATH_ZERO		0.0f			/*<  1  >*/
	#define MATH_ONE		1.0f			/*<  2  >*/
	#define MATH_INV_SQRT	0.70710678118f	/*<  1 / sqrt( 2 ) >*/
	
	#define MATH_PI			3.14159265359f	/*<  PI  >*/
	#define MATH_2PI		6.28318530718f	/*<  2 * PI  >*/
	
	#define MATH_PI2		1.57079632679f	/*<  PI / 2  >*/
	#define MATH_PI3		1.04719755120f	/*<  PI / 3  >*/
	#define MATH_PI4		0.78539816339f	/*<  PI / 4  >*/
	#define MATH_PI8		0.39269908169f	/*<  PI / 8  >*/
	#define MATH_PI16		0.19634954084f	/*<  PI / 16  >*/
	
	#define MATH_2PI3		2.09439510239f	/*<  ( 2 * PI ) / 3  >*/
	#define MATH_3PI4		2.35619449019f	/*<  ( 3 * PI ) / 4  >*/
	#define MATH_3PI8		1.17809724510f	/*<  ( 3 * PI ) / 8  >*/
	#define MATH_5PI8		1.96349540849f	/*<  ( 5 * PI ) / 8  >*/
	#define MATH_7PI8		2.74889357189f	/*<  ( 7 * PI ) / 8  >*/
	#define MATH_3PI16		1.37444678595f	/*<  ( 3 * PI ) / 16  >*/
	#define MATH_5PI16		0.98174770424f	/*<  ( 5 * PI ) / 16  >*/
	#define MATH_7PI16		1.37444678595f	/*<  ( 7 * PI ) / 16  >*/
	#define MATH_9PI16		1.76714586764f	/*<  ( 9 * PI ) / 16  >*/
	#define MATH_11PI16		2.15984494934f	/*<  ( 11 * PI ) / 16  >*/
	#define MATH_13PI16		2.55254403104f	/*<  ( 13 * PI ) / 16  >*/
	#define MATH_15PI16		2.94524311274f	/*<  ( 15 * PI ) / 16  >*/
	
	constexpr size_t INTSIZE = sizeof( int );
	constexpr size_t UINTSIZE = sizeof( unsigned int );
	constexpr size_t FLOATSIZE = sizeof( float );
	constexpr size_t POINTERSIZE = sizeof( void* );
	
	#define INTSIZE		INTSIZE		/*<  Int Size  >*/
	#define UINTSIZE	UINTSIZE	/*<  uInt Size  >*/
	#define FLOATSIZE	FLOATSIZE	/*<  Float Size  >*/
	#define POINTERSIZE	POINTERSIZE	/*<  Pointer Size  >*/

#endif