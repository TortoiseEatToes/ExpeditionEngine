#ifndef Defs_H
#define Defs_H

	#define FORCEINLINE __forceinline	/*  < Keyword - Force method/function to be inlined >  */
	#define UNUSEDVAR( var )			/*  < Function - Shuts up the compiler of unused variables >  */
	#define PREDICTTRUE( expr ) __builtin_expect( expr, 1 );	/*  < Conditional - true for branch prediction >  */
	#define PREDICTFALSE( expr ) __builtin_expect( expr, 0 );	/*  < Conditional - false for branch prediction >  */
	#define NOCOPYASSIGNMENT( type ) type( const type& ) = delete; \
									 type& operator = (const type& ) = delete;	/*  < Replacement - Short hand for no Copy/Assignment operator >  */

#endif // !Defs_H

// --- End of File --- //