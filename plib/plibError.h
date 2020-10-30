/*
	plib::Error
*/
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

enum
{
	// 0000 0000 : Type( 4bit ) Message( 4bit )
	plibErrorNull = 0x00 , 
	
	plibErrorParameter = 0x10 , 
	plibErrorParameterNull = 0x11 , 
	plibErrorParameterViolation = 0x12 , 
	
	plibErrorReference = 0x20 , 
	plibErrorReferenceNull = 0x21 , 
	plibErrorReferenceIndex = 0x22 , 
	plibErrorReferenceViolation = 0x23 , 
	
	plibErrorLib = 0x30 , 
	plibErrorDataHBST = plibErrorLib , 
	plibErrorMemory = plibErrorLib + 0x10 
} ;

typedef uint8_t plibErrorType ;

extern plibErrorType plibError ;

#define plibError_getType(  ) ( plibError & 0xf0 )
#define plibError_getMessage(  ) ( plibError & 0x0f )