/*
	plib::Error
*/
#include "plibError.h"

void plibError_initialize( struct plibError *Error )
{
	if( Error == plibCommonNullPointer )
		return ;
	
	Error->Type = plibErrorNull ;
	Error->Address = plibCommonNullPointer ;
}
void plibError_report( struct plibError *Error , uint8_t Type , void *Address )
{
	if( Error == plibCommonNullPointer )
		return ;
	
	Error->Type = Type ;
	Error->Address = Address ;
}