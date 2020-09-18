/*
	plib::Std::Memory::Pool
*/
#pragma once
#include "plibStdMemory.h"

struct plibStdMemoryPool
{
	size_t UnitSize , Count , MaxCount ;
	uint8_t *AddressStart , *AddressEnd ;
	uint8_t **AddressStack ;
} ;

void plbStdMemoryPool_initialize( struct plibStdMemoryPool *Pool ) ;

struct plibStdMemoryPool* plibStdMemoryPool_createPool( size_t UnitSize , size_t MaxCount ) ;
bool plibStdMemoryPool_deletePool( struct plibStdMemoryPool **Pool ) ;

uint8_t* plbStdMemoryPool_allocate( struct plibStdMemoryPool *Pool ) ;
void plbStdMemoryPool_deallocate( struct plibStdMemoryPool *Pool , uint8_t **UsedAddress ) ;