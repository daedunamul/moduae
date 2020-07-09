/*
	plib::Std::Format::Name64
*/
#include "plibStdFormatName64.h"

uint8_t plibStdFormatName64_translateFromAscii( char Ascii )
{
	if( Ascii >= 65 && Ascii <= 90 )
		return Ascii - 64 ; // Capital Alphabet
	else if( Ascii >= 97 && Ascii <= 122 )
		return Ascii - 97 + 27 ; // Alphabet
	else if( Ascii >= 48 && Ascii <= 57 )
		return Ascii - 48 + 53 ; // Number
	else if( Ascii == 95 )
		return 63 ; // Underbar
		
	return 0 ; // Null
}
