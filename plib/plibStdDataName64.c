/*
	plib::Std::Data::Name64
*/
#include "plibStdDataName64.h"

uint8_t plibStdDataName64_translateFromAscii( char Ascii )
{
	if( Ascii >= 65 && Ascii <= 90 )
		return Ascii - 65 ; // Capital Alphabet
	else if( Ascii >= 97 && Ascii <= 122 )
		return Ascii - 97 + 26 ; // Alphabet
	else if( Ascii >= 48 && Ascii <= 57 )
		return Ascii - 48 + 52 ; // Number
	else if( Ascii == 95 )
		return 62 ; // Underbar
		
	return 63 ; // Null
}
