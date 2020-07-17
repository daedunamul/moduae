/*
	plib::Std::Memory::Pool
*/
#pragma once
#include "plibStdMemory.h"

struct plibStdMemoryPool
{
	size_t UnitSize , UsageCount , MaxCount ;
	uint8_t *Data ;
} ;

struct plibStdMemoryPool* plibStdMemoryPool_createPool( size_t UnitSize , size_t MaxCount ) ;
bool plibStdMemoryPool_deletePool( struct plibStdMemoryPool **Pool ) ;

uint8_t* plbStdMemoryPool_allocate( struct plibStdMemoryPool *Pool ) ;
void plbStdMemoryPool_flush( struct plibStdMemoryPool *Pool ) ;
