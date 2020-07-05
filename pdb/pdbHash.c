/*
	pdb::Hash
*/
#include "pdbHash.h"

uint8_t pdbHash_getBase64( char Ascii )
{
	if( Ascii >= 65 && Ascii <= 90 )
		return Ascii - 65 ; // Capital Alphabet
	else if( Ascii >= 97 && Ascii <= 122 )
		return Ascii - 97 + 26 ; // Alphabet
	else if( Ascii >= 48 && Ascii <= 57 )
		return Ascii - 48 + 52 ; // Number
	else if( Ascii == 95 )
		return 62 ; // Underbar
		
	return 63 ; // Space
}
uint32_t pdbHash_getAdler32( uint8_t *Data )
{
	int Count ;
	uint16_t SumA = 1 , SumB = 0 ;
	
	for( Count = 0 ; Count < 32 ; Count ++ )
	{
		SumA = SumA + Data[ Count ] ;
		SumB = SumB + SumA ;
	}
	
	return SumA + ( SumB << 16 ) ;
}
