/*
	plib::Error
*/
#pragma once
#include "plibCommon.h"

enum 
{
	plibErrorTypeNull = 0 , 
	plibErrorTypeParameter , 
	plibErrorTypeProcess 
} ;

struct plibErrorType
{
	uint8_t Type ;
	void *Address ;
} ;

void plibError_initialize( struct plibErrorType *Error ) ;
void plibError_report( struct plibErrorType *Error , uint8_t Type , void *Address ) ;