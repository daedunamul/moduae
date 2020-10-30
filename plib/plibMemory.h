/*
	plib::Memory
*/
#pragma once
#include "plibCommon.h"
#include <stdlib.h>

enum
{
	plibMemoryErrorAllocation = plibErrorMemory + 0x01 , 
	plibMemoryErrorDeallocation , 
	plibMemoryErrorOutOfCount , 
	plibMemoryErrorDoubleFreeing 
} ;