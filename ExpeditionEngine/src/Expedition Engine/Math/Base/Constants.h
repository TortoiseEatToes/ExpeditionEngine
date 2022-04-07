
#ifndef Constants_H
#define Constants_H

#include "Types.h"

	//====================================
	// Constant Values
	//====================================
	
	#define MATH_PI		3.14159265359f	/*  < Constant - pi >  */
	#define MATH_2PI	6.28318530718f	/*  < Constant - 2.0f * pi >  */
	
	#define MATH_PI2	1.57079632679f	/*  < Constant - pi / 2.0f >  */
	
	#define MATH_PI3	1.04719755120f	/*  < Constant - pi / 3.0f >  */
	#define MATH_2PI3	2.09439510239f	/*  < Constant - ( 2.0f * pi ) / 3.0f >  */
	
	#define MATH_PI4	0.78539816339f	/*  < Constant - pi / 4.0f >  */
	#define MATH_3PI4	2.35619449019f	/*  < Constant - ( 3.0f * pi ) / 4.0f >  */
	
	#define MATH_PI5	0.62831853071f	/*  < Constant - pi / 5.0f >  */
	#define MATH_2PI5	1.25663706144f	/*  < Constant - ( 2.0f * pi ) / 5.0f >  */
	#define MATH_3PI5	1.88495559215f	/*  < Constant - ( 3.0f * pi ) / 5.0f >  */
	#define MATH_4PI5	2.51327412287f	/*  < Constant - ( 4.0f * pi ) / 5.0f >  */
	
	#define MATH_PI6	0.52359877559f	/*  < Constant - pi / 6.0f >  */
	#define MATH_5PI6	2.61799387799f	/*  < Constant - ( 5.0f * pi ) / 6.0f >  */
	
	#define MATH_PI8	0.39269908169f	/*  < Constant - pi / 8.0f >  */
	#define MATH_3PI8	1.1780972451f	/*  < Constant - ( 3.0f * pi ) / 8.0f >  */
	#define MATH_5PI8	1.96349540849f	/*  < Constant - ( 5.0f * pi ) / 8.0f >  */
	#define MATH_7PI8	2.74889357189f	/*  < Constant - ( 7.0f * pi ) / 8.0f >  */
	 
	#define MATH_PI16	0.19634954084f	/*  < Constant - pi / 16.0f >  */
	#define MATH_3PI16	0.58904862254f	/*  < Constant - ( 3.0f * pi ) / 16.0f >  */
	#define MATH_5PI16	0.98174770424f	/*  < Constant - ( 5.0f * pi ) / 16.0f >  */
	#define MATH_7PI16	1.37444678595f	/*  < Constant - ( 7.0f * pi ) / 16.0f >  */
	#define MATH_9PI16	1.76714586764f	/*  < Constant - ( 9.0f * pi ) / 16.0f >  */
	#define MATH_11PI16	2.15984494934f	/*  < Constant - ( 11.0f * pi ) / 16.0f >  */
	#define MATH_13PI16	2.55254403104f	/*  < Constant - ( 13.0f * pi ) / 16.0f >  */
	#define MATH_15PI16	2.94524311274f	/*  < Constant - ( 15.0f * pi ) / 15.0f >  */
	
	#define MATH_TOLERANCE	.0000005f	/*  < Constant - FLOAT Rounding Error Tolerance >  */
	
	constexpr size_t FLOATSIZE		= sizeof( FLOAT );
	constexpr size_t INTSIZE		= sizeof( S32 );
	constexpr size_t POINTERSIZE	= sizeof( void* );
	
	#define FLOATSIZE	FLOATSIZE	/*  < Constant - size of a FLOAT >  */
	#define INTSIZE		INTSIZE		/*  < Constant - size of an int >  */
	#define POINTERSIZE POINTERSIZE	/*  < Constant - size of a pointer >  */
	
	constexpr U8 TRUE = 1;
	constexpr U8 FALSE = 0;

	#define TRUE TRUE	/*  < Constant - bool true >  */
	#define FALSE FALSE /*  < Constant - bool false >  */

#endif // !Constants_H

// --- End of File --- //