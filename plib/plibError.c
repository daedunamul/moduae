/*
	plib::Error
*/
#include "plibError.h"

void plibError_initialize( struct plibErrorType *Error )
{
	if( Error == plibCommonNullPointer )
		return ;
	
	Error->Type = plibErrorTypeNull ;
	Error->Address = plibCommonNullPointer ;
}
void plibError_report( struct plibErrorType *Error , uint8_t Type , void *Address )
{
	if( Error == plibCommonNullPointer )
		return ;
	
	Error->Type = Type ;
	Error->Address = Address ;
}