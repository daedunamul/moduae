/*
	plib::Error
*/
#pragma once
#include "plibCommon.h"

enum 
{
	plibErrorNull = 0 , 
	plibErrorParameter , 
	plibErrorProcess 
} ;

struct plibError
{
	uint8_t Type ;
	void *Address ;
} ;

void plibError_initialize( struct plibError *Error ) ;
void plibError_report( struct plibError *Error , uint8_t Type , void *Address ) ;